/* sbh_pool.c - GROUP B: allocator pool helpers (game's small-block heap).
 *
 * The original server.dll replaces the CRT's sbheap.c functions with the
 * game's own copies (that is why the binary links LIBCMT but shadows the
 * sbh entry points).  All 14 functions form one contiguous VA run
 * [0x1001d515, 0x1001e6e1) - the game's "sbheap.obj" - and are ported from
 * the MSVC 6.0 CRT source with the game's modifications:
 *
 *   - _crtheap replaced by the game's heap handle _crtheap
 *   - memset -> memset, memmove -> memcpy (game copies)
 *   - sbh globals relocated to 0x11766430-0x11766444 / 0x10031b78 /
 *     0x10033b98 / 0x100355a4 (defined in sbh_globals.c)
 *
 * V6 sbh = "pool allocator" (allocator mode 3, malloc.c); V5 ("old") sbh =
 * "block allocator" (mode 2).  Struct layouts match winheap.h.
 */
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* V6 sbh structures (winheap.h tagHeader/tagRegion/tagGroup/tagEntry). */
// SIZE 0xc
typedef struct tagEntry
{
    int                 sizeFront;
    struct tagEntry *   pEntryNext;
    struct tagEntry *   pEntryPrev;
} SbhEntry;

// SIZE 0x4
typedef struct tagEntryEnd
{
    int                 sizeBack;
} SbhEntryEnd;

// SIZE 0x8
typedef struct tagListHead
{
    SbhEntry *          pEntryNext;
    SbhEntry *          pEntryPrev;
} SbhListHead;

// SIZE 0x204
typedef struct tagGroup
{
    int                 cntEntries;
    SbhListHead         listHead[64];
} SbhGroup;

// SIZE 0x41c4
typedef struct tagRegion
{
    int                 indGroupUse;
    char                cntRegionSize[64];
    unsigned int        bitvGroupHi[32];
    unsigned int        bitvGroupLo[32];
    SbhGroup            grpHeadList[32];
} SbhRegion;

// SIZE 0x14
typedef struct tagHeader
{
    unsigned int        bitvEntryHi;
    unsigned int        bitvEntryLo;
    unsigned int        bitvCommit;
    void *              pHeapData;
    SbhRegion *         pRegion;
} SbhHeader;

/* V5 ("old") sbh structures (winheap.h __old_sbh_*). */

#define _OLD_PAGESIZE              0x1000
#define _OLD_PARASIZE              0x10
#define _OLD_PARAS_PER_PAGE        240
#define _OLD_PAGES_PER_REGION      1024
#define _OLD_PAGES_PER_COMMITMENT  16
#define _OLD_FREE_PARA             0
#define _OLD_UNCOMMITTED_PAGE      (-1)
#define _OLD_NO_PAGES              ((OldSbhPage *)-1)

/* sbh globals (sbh_globals.c) */

/* helpers outside this VA run (other sbh/TU objects) */
extern SbhHeader * __cdecl fcn_1001db72(void);                 /* __sbh_alloc_new_region */
extern int __cdecl fcn_1001dc23(SbhHeader *);                  /* __sbh_alloc_new_group */
extern OldSbhRegion * __cdecl fcn_1001e014(void);              /* __old_sbh_new_region */
extern void __cdecl fcn_1001e1ae(int);                         /* __old_sbh_decommit_pages */
extern void * __cdecl fcn_1001e514(OldSbhPage *, size_t, size_t); /* __old_sbh_alloc_block_from_page */
extern void* __cdecl memset(void*, int, unsigned int);
extern void* __cdecl memcpy(void*, const void*, unsigned int);

/* the static region descriptor occupies 0x2020 bytes at 0x10031b78
 * (data_globals.c defines the head symbol as a byte anchor) */
#define g_old_heap ((OldSbhRegion *)&g_old_sbh_region_head)

/* ======================================================================
 * 0x1001d515 - __sbh_find_block: locate the header whose region contains
 * the allocation block.  Scans the header list from the start.
 * ==================================================================== */

// FUNCTION: GOLDTL 0x427740
// SIZE: 231
int __cdecl fcn_1001dc23(SbhHeader * pHeader)
{
    SbhRegion * pRegion;
    SbhGroup * pGroup;
    SbhEntry * pEntry;
    SbhEntry * pHead;
    SbhEntryEnd * pEntryEnd;
    unsigned int bitvCommit;
    int indCommit;
    int index;
    void * pHeapPage;
    void * pHeapStartPage;
    void * pHeapEndPage;

    pRegion = pHeader->pRegion;

    /* determine next group to use by the first bit set in the commit vector */
    bitvCommit = pHeader->bitvCommit;
    indCommit = 0;
    while ((int)bitvCommit >= 0)
    {
        bitvCommit <<= 1;
        indCommit++;
    }

    /* allocate and initialize a new group */
    pGroup = &pRegion->grpHeadList[indCommit];

    for (index = 0; index < 63; index++)
    {
        pEntry = (SbhEntry *)((char *)&pGroup->listHead[index] - 4);
        pEntry->pEntryNext = pEntry->pEntryPrev = pEntry;
    }

    /* commit heap memory for the new group */
    pHeapStartPage = (void *)((char *)pHeader->pHeapData +
                                       indCommit * 0x8000);
    if ((VirtualAlloc(pHeapStartPage, 0x8000, 0x1000,
                                      4)) == NULL)   /* MEM_COMMIT, PAGE_READWRITE */
        return -1;

    /* initialize heap data with empty page entries */
    pHeapEndPage = (void *)((char *)pHeapStartPage +
                        (8 - 1) * 0x1000);          /* PAGES_PER_GROUP */

    for (pHeapPage = pHeapStartPage; pHeapPage <= pHeapEndPage;
            pHeapPage = (void *)((char *)pHeapPage + 0x1000))
    {
        /* set sentinel values at start and end of the page */
        *(int *)((char *)pHeapPage + 8) = -1;
        *(int *)((char *)pHeapPage + 0x1000 - 4) = -1;

        /* set size and pointer info for one empty entry */
        pEntry = (SbhEntry *)((char *)pHeapPage + 0xc);   /* ENTRY_OFFSET */
        pEntry->sizeFront = 0xff0;                        /* MAX_FREE_ENTRY_SIZE */
        pEntry->pEntryNext = (SbhEntry *)((char *)pEntry + 0x1000);
        pEntry->pEntryPrev = (SbhEntry *)((char *)pEntry - 0x1000);
        pEntryEnd = (SbhEntryEnd *)((char *)pEntry + 0xff0 - 4);
        pEntryEnd->sizeBack = 0xff0;
    }

    /* initialize group entry pointer for the maximum size
     * and set the terminate list entries */
    pHead = (SbhEntry *)((char *)&pGroup->listHead[63] - 4);
    pEntry = pHead->pEntryNext =
                        (SbhEntry *)((char *)pHeapStartPage + 0xc);
    pEntry->pEntryPrev = pHead;

    pEntry = pHead->pEntryPrev =
                        (SbhEntry *)((char *)pHeapEndPage + 0xc);
    pEntry->pEntryNext = pHead;

    pRegion->bitvGroupHi[indCommit] = 0;
    pRegion->bitvGroupLo[indCommit] = 1;
    if (pRegion->cntRegionSize[63]++ == 0)
        pHeader->bitvEntryLo |= 1;

    /* clear bit in the commit vector */
    pHeader->bitvCommit &= ~(0x80000000L >> indCommit);

    return indCommit;
}

/* ======================================================================
 * 0x1001dd1e - __sbh_resize_block: grow or shrink a pool-allocator block
 * in place (allocated entries keep the +1 size marker).
 * ==================================================================== */
