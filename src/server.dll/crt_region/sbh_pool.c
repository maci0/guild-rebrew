/* sbh_pool.c - GROUP B: allocator pool helpers (game's small-block heap).
 *
 * The original server.dll replaces the CRT's sbheap.c functions with the
 * game's own copies (that is why the binary links LIBCMT but shadows the
 * sbh entry points).  All 14 functions form one contiguous VA run
 * [0x1001d515, 0x1001e6e1) - the game's "sbheap.obj" - and are ported from
 * the MSVC 6.0 CRT source with the game's modifications:
 *
 *   - _crtheap replaced by the game's heap handle _crtheap
 *   - memset -> fcn_10021240, memmove -> fcn_1001b200 (game copies)
 *   - sbh globals relocated to 0x11766430-0x11766444 / 0x10031b78 /
 *     0x10033b98 / 0x100355a4 (defined in sbh_globals.c)
 *
 * V6 sbh = "pool allocator" (allocator mode 3, malloc.c); V5 ("old") sbh =
 * "block allocator" (mode 2).  Struct layouts match winheap.h.
 */
#include <windows.h>

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
typedef char            OldPara[16];

// SIZE 0x8
typedef struct __old_region_map
{
    int                 free_paras_in_page;
    unsigned int        last_failed_alloc;
} OldRegionMap;

// SIZE 0x1000
typedef struct __old_sbh_page
{
    unsigned char *     p_starting_alloc_map;
    unsigned int        free_paras_at_start;
    unsigned char       alloc_map[241];
    unsigned char       reserved[7];
    OldPara             alloc_blocks[240];
} OldSbhPage;

// SIZE 0x2020
typedef struct __old_sbh_region
{
    struct __old_sbh_region * p_next_region;
    struct __old_sbh_region * p_prev_region;
    OldRegionMap *           p_starting_region_map;
    OldRegionMap *           p_first_uncommitted;
    OldSbhPage *             p_pages_begin;
    OldSbhPage *             p_pages_end;
    OldRegionMap             region_map[1025];
} OldSbhRegion;

#define _OLD_PAGESIZE              0x1000
#define _OLD_PARASIZE              0x10
#define _OLD_PARAS_PER_PAGE        240
#define _OLD_PAGES_PER_REGION      1024
#define _OLD_PAGES_PER_COMMITMENT  16
#define _OLD_FREE_PARA             0
#define _OLD_UNCOMMITTED_PAGE      (-1)
#define _OLD_NO_PAGES              ((OldSbhPage *)-1)

/* sbh globals (sbh_globals.c) */
extern int __sbh_sizeHeaderList;              /* __sbh_sizeHeaderList */
extern int __sbh_indGroupDefer;              /* __sbh_indGroupDefer */
extern void * __sbh_pHeaderScan;           /* __sbh_pHeaderScan */
extern void * __sbh_pHeaderDefer;           /* __sbh_pHeaderDefer */
extern int __sbh_cntHeaderList;              /* __sbh_cntHeaderList */
extern void * __sbh_pHeaderList;           /* __sbh_pHeaderList */
extern char g_old_sbh_region_head;              /* static region descriptor head (defined in data_globals.c) */
extern OldSbhRegion * __old_sbh_p_starting_region;   /* __old_sbh_p_starting_region */
extern int __old_sbh_decommitable_pages;              /* __old_sbh_decommitable_pages */
extern void * _crtheap;           /* game heap handle (_crtheap analog) */

/* helpers outside this VA run (other sbh/TU objects) */
extern SbhHeader * __cdecl fcn_1001db72(void);                 /* __sbh_alloc_new_region */
extern int __cdecl fcn_1001dc23(SbhHeader *);                  /* __sbh_alloc_new_group */
extern OldSbhRegion * __cdecl fcn_1001e014(void);              /* __old_sbh_new_region */
extern void __cdecl fcn_1001e1ae(int);                         /* __old_sbh_decommit_pages */
extern void * __cdecl fcn_1001e514(OldSbhPage *, size_t, size_t); /* __old_sbh_alloc_block_from_page */
extern void * __cdecl fcn_10021240(void *, int, unsigned int); /* game memset */
extern void * __cdecl fcn_1001b200(void *, const void *, unsigned int); /* game memmove */

/* the static region descriptor occupies 0x2020 bytes at 0x10031b78
 * (data_globals.c defines the head symbol as a byte anchor) */
#define g_old_heap ((OldSbhRegion *)&g_old_sbh_region_head)

/* ======================================================================
 * 0x1001d515 - __sbh_find_block: locate the header whose region contains
 * the allocation block.  Scans the header list from the start.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001d515 (was FUNCTION; provided by LIBCMT / library_msvc.h)
SbhHeader * __cdecl fcn_1001d515(void * pvAlloc)
{
    SbhHeader * pHeaderLast;
    SbhHeader * pHeader;
    unsigned int offRegion;

    pHeaderLast = (SbhHeader *)__sbh_pHeaderList + __sbh_cntHeaderList;
    pHeader = (SbhHeader *)__sbh_pHeaderList;
    while (pHeader < pHeaderLast)
    {
        offRegion = (unsigned int)pvAlloc - (unsigned int)pHeader->pHeapData;
        if (offRegion < 0x100000)        /* BYTES_PER_REGION */
            return pHeader;
        pHeader++;
    }
    return NULL;
}

/* ======================================================================
 * 0x1001d540 - __sbh_free_block: free a block in the pool allocator.
 * Coalesces with free neighbours, updates the group free lists, and when a
 * whole group becomes empty defers/decommits it (region release when the
 * commit vector returns to its initial value).
 * ==================================================================== */

// FUNCTION: SERVER 0x1001d540 (was FUNCTION; provided by LIBCMT / library_msvc.h)
void __cdecl fcn_1001d540(SbhHeader * pHeader, void * pvAlloc)
{
    SbhRegion * pRegion;
    SbhGroup * pGroup;
    SbhEntry * pHead;
    SbhEntry * pEntry;
    SbhEntry * pNext;
    SbhEntry * pPrev;
    void * pHeapDecommit;
    int sizeEntry;
    int sizeNext;
    int sizePrev;
    unsigned int indGroup;
    unsigned int indEntry;
    unsigned int indNext;
    unsigned int indPrev;
    unsigned int offRegion;

    pRegion = pHeader->pRegion;

    offRegion = (unsigned int)pvAlloc - (unsigned int)pHeader->pHeapData;
    indGroup = offRegion / 0x8000;      /* BYTES_PER_GROUP */
    pGroup = &pRegion->grpHeadList[indGroup];

    pEntry = (SbhEntry *)((char *)pvAlloc - 4);
    sizeEntry = pEntry->sizeFront - 1;

    /* already-free check (size kept with the low bit set while allocated) */
    if ((sizeEntry & 1) != 0)
        return;

    pNext = (SbhEntry *)((char *)pEntry + sizeEntry);
    sizeNext = pNext->sizeFront;

    sizePrev = ((SbhEntryEnd *)((char *)pEntry - 4))->sizeBack;

    /* coalesce with a free next entry */
    if ((sizeNext & 1) == 0)
    {
        indNext = (sizeNext >> 4) - 1;
        if (indNext > 63)
            indNext = 63;

        if (pNext->pEntryNext == pNext->pEntryPrev)
        {
            if (indNext < 32)
            {
                pRegion->bitvGroupHi[indGroup] &= ~(0x80000000L >> indNext);
                if (--pRegion->cntRegionSize[indNext] == 0)
                    pHeader->bitvEntryHi &= ~(0x80000000L >> indNext);
            }
            else
            {
                pRegion->bitvGroupLo[indGroup] &= ~(0x80000000L >> (indNext - 32));
                if (--pRegion->cntRegionSize[indNext] == 0)
                    pHeader->bitvEntryLo &= ~(0x80000000L >> (indNext - 32));
            }
        }

        pNext->pEntryPrev->pEntryNext = pNext->pEntryNext;
        pNext->pEntryNext->pEntryPrev = pNext->pEntryPrev;

        sizeEntry += sizeNext;
    }

    indEntry = (sizeEntry >> 4) - 1;
    if (indEntry > 63)
        indEntry = 63;

    /* coalesce with a free previous entry */
    if ((sizePrev & 1) == 0)
    {
        pPrev = (SbhEntry *)((char *)pEntry - sizePrev);

        indPrev = (sizePrev >> 4) - 1;
        if (indPrev > 63)
            indPrev = 63;

        sizeEntry += sizePrev;
        indEntry = (sizeEntry >> 4) - 1;
        if (indEntry > 63)
            indEntry = 63;

        if (indPrev != indEntry)
        {
            if (pPrev->pEntryNext == pPrev->pEntryPrev)
            {
                if (indPrev < 32)
                {
                    pRegion->bitvGroupHi[indGroup] &= ~(0x80000000L >> indPrev);
                    if (--pRegion->cntRegionSize[indPrev] == 0)
                        pHeader->bitvEntryHi &= ~(0x80000000L >> indPrev);
                }
                else
                {
                    pRegion->bitvGroupLo[indGroup] &= ~(0x80000000L >> (indPrev - 32));
                    if (--pRegion->cntRegionSize[indPrev] == 0)
                        pHeader->bitvEntryLo &= ~(0x80000000L >> (indPrev - 32));
                }
            }

            pPrev->pEntryPrev->pEntryNext = pPrev->pEntryNext;
            pPrev->pEntryNext->pEntryPrev = pPrev->pEntryPrev;
        }

        pEntry = pPrev;
    }

    /* connect the (possibly coalesced) entry to its bucket unless the
     * previous entry was free with an unchanged index (then pEntry was
     * already linked by the prev-coalesce) */
    if (!((sizePrev & 1) == 0 && indPrev == indEntry))
    {
        pHead = (SbhEntry *)((char *)&pGroup->listHead[indEntry] - 4);
        pEntry->pEntryNext = pHead->pEntryNext;
        pEntry->pEntryPrev = pHead;
        pHead->pEntryNext = pEntry;
        pEntry->pEntryNext->pEntryPrev = pEntry;

        if (pEntry->pEntryNext == pEntry->pEntryPrev)
        {
            if (indEntry < 32)
            {
                if (pRegion->cntRegionSize[indEntry]++ == 0)
                    pHeader->bitvEntryHi |= 0x80000000L >> indEntry;
                pRegion->bitvGroupHi[indGroup] |= 0x80000000L >> indEntry;
            }
            else
            {
                if (pRegion->cntRegionSize[indEntry]++ == 0)
                    pHeader->bitvEntryLo |= 0x80000000L >> (indEntry - 32);
                pRegion->bitvGroupLo[indGroup] |= 0x80000000L >> (indEntry - 32);
            }
        }
    }

    /* adjust the size fields front and back */
    pEntry->sizeFront = sizeEntry;
    ((SbhEntryEnd *)((char *)pEntry + sizeEntry - 4))->sizeBack = sizeEntry;

    /* if the group became empty, decommit the previously deferred group */
    if (--pGroup->cntEntries == 0)
    {
        if (__sbh_pHeaderDefer)
        {
            pHeapDecommit = (void *)((char *)((SbhHeader *)__sbh_pHeaderDefer)->pHeapData +
                                    __sbh_indGroupDefer * 0x8000);
            VirtualFree(pHeapDecommit, 0x8000, 0x4000);   /* MEM_DECOMMIT */

            ((SbhHeader *)__sbh_pHeaderDefer)->bitvCommit |=
                0x80000000 >> __sbh_indGroupDefer;

            ((SbhHeader *)__sbh_pHeaderDefer)->pRegion->bitvGroupLo[__sbh_indGroupDefer] = 0;
            if (--((SbhHeader *)__sbh_pHeaderDefer)->pRegion->cntRegionSize[63] == 0)
                ((SbhHeader *)__sbh_pHeaderDefer)->bitvEntryLo &= ~1;

            /* if the commit vector is back to initial, drop the region */
            if (((SbhHeader *)__sbh_pHeaderDefer)->bitvCommit == 0xffffffff)
            {
                VirtualFree(((SbhHeader *)__sbh_pHeaderDefer)->pHeapData, 0, 0x8000);

                HeapFree(_crtheap, 0, ((SbhHeader *)__sbh_pHeaderDefer)->pRegion);

                fcn_1001b200((void *)__sbh_pHeaderDefer,
                             (void *)((SbhHeader *)__sbh_pHeaderDefer + 1),
                             (int)((SbhHeader *)__sbh_pHeaderList + __sbh_cntHeaderList) -
                             (int)((SbhHeader *)__sbh_pHeaderDefer + 1));
                __sbh_cntHeaderList--;

                if (pHeader > (SbhHeader *)__sbh_pHeaderDefer)
                    pHeader--;

                __sbh_pHeaderScan = __sbh_pHeaderList;
            }
        }

        __sbh_pHeaderDefer = pHeader;
        __sbh_indGroupDefer = indGroup;
    }
}

/* ======================================================================
 * 0x1001d869 - __sbh_alloc_block: allocate from the pool allocator.
 * Scans the header list for a free entry bucket that can satisfy the
 * request (rover -> end, then start -> rover), committing a new group or
 * creating a new region when needed.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001d869 (was FUNCTION; provided by LIBCMT / library_msvc.h)
void * __cdecl fcn_1001d869(int intSize)
{
    SbhHeader * pHeaderLast;
    SbhHeader * pHeader;
    SbhRegion * pRegion;
    SbhGroup * pGroup;
    SbhEntry * pEntry;
    SbhEntry * pHead;
    unsigned int bitvEntryLo;
    unsigned int bitvEntryHi;
    unsigned int bitvTest;
    int sizeEntry;
    int indEntry;
    int indGroupUse;
    int sizeNewFree;
    int indNewFree;

    pHeaderLast = (SbhHeader *)__sbh_pHeaderList + __sbh_cntHeaderList;

    /* add 8 bytes entry overhead and round up to next para size */
    sizeEntry = (intSize + 2 * 4 + 15) & ~15;   /* 2 * sizeof(int) */

    /* determine index and mask from entry size:
     * Hi MSB: bit 0 = 1 para ... bit 31 = 32 paras
     * Lo MSB: bit 0 = 33 paras ... bit 31 = 64+ paras */
    indEntry = (sizeEntry >> 4) - 1;
    if (indEntry < 32)
    {
        bitvEntryHi = 0xffffffffu >> indEntry;
        bitvEntryLo = 0xffffffffu;
    }
    else
    {
        bitvEntryHi = 0;
        bitvEntryLo = 0xffffffffu >> (indEntry - 32);
    }

    /* scan header list from rover to end */
    pHeader = (SbhHeader *)__sbh_pHeaderScan;
    while (pHeader < pHeaderLast)
    {
        if ((bitvEntryHi & pHeader->bitvEntryHi) |
            (bitvEntryLo & pHeader->bitvEntryLo))
            break;
        pHeader++;
    }

    /* if no entry, scan from list start up to the rover */
    if (pHeader == pHeaderLast)
    {
        pHeader = (SbhHeader *)__sbh_pHeaderList;
        while (pHeader < (SbhHeader *)__sbh_pHeaderScan)
        {
            if ((bitvEntryHi & pHeader->bitvEntryHi) |
                (bitvEntryLo & pHeader->bitvEntryLo))
                break;
            pHeader++;
        }

        /* no free entry exists, scan for available groups to commit */
        if (pHeader == (SbhHeader *)__sbh_pHeaderScan)
        {
            while (pHeader < pHeaderLast)
            {
                if (pHeader->bitvCommit)
                    break;
                pHeader++;
            }

            if (pHeader == pHeaderLast)
            {
                pHeader = (SbhHeader *)__sbh_pHeaderList;
                while (pHeader < (SbhHeader *)__sbh_pHeaderScan)
                {
                    if (pHeader->bitvCommit)
                        break;
                    pHeader++;
                }

                /* if no available groups, create a new region */
                if (pHeader == (SbhHeader *)__sbh_pHeaderScan)
                    if (!(pHeader = fcn_1001db72()))
                        return NULL;
            }

            /* commit a new group in the region associated with pHeader */
            if ((pHeader->pRegion->indGroupUse = fcn_1001dc23(pHeader)) == -1)
                return NULL;
        }
    }
    __sbh_pHeaderScan = pHeader;

    pRegion = pHeader->pRegion;
    indGroupUse = pRegion->indGroupUse;

    /* determine the group to allocate from */
    if (indGroupUse == -1 ||
        !((bitvEntryHi & pRegion->bitvGroupHi[indGroupUse]) |
          (bitvEntryLo & pRegion->bitvGroupLo[indGroupUse])))
    {
        /* preferred group could not allocate entry, scan all vectors */
        indGroupUse = 0;
        while (!((bitvEntryHi & pRegion->bitvGroupHi[indGroupUse]) |
                 (bitvEntryLo & pRegion->bitvGroupLo[indGroupUse])))
            indGroupUse++;
    }
    pGroup = &pRegion->grpHeadList[indGroupUse];

    /* determine bucket index */
    indEntry = 0;

    if (!(bitvTest = bitvEntryHi & pRegion->bitvGroupHi[indGroupUse]))
    {
        indEntry = 32;
        bitvTest = bitvEntryLo & pRegion->bitvGroupLo[indGroupUse];
    }
    while ((int)bitvTest >= 0)
    {
        bitvTest <<= 1;
        indEntry++;
    }
    pEntry = pGroup->listHead[indEntry].pEntryNext;

    /* compute size and bucket index of the new free entry */
    sizeNewFree = pEntry->sizeFront - sizeEntry;
    indNewFree = (sizeNewFree >> 4) - 1;
    if (indNewFree > 63)
        indNewFree = 63;

    /* only modify entry pointers if bucket index changed */
    if (indNewFree != indEntry)
    {
        /* test entry is sole member of bucket (next == prev) */
        if (pEntry->pEntryNext == pEntry->pEntryPrev)
        {
            /* clear bit in group vector, decrement region count;
             * if region count is now zero, clear bit in region vector */
            if (indEntry < 32)
            {
                pRegion->bitvGroupHi[indGroupUse] &= ~(0x80000000L >> indEntry);
                if (--pRegion->cntRegionSize[indEntry] == 0)
                    pHeader->bitvEntryHi &= ~(0x80000000L >> indEntry);
            }
            else
            {
                pRegion->bitvGroupLo[indGroupUse] &= ~(0x80000000L >> (indEntry - 32));
                if (--pRegion->cntRegionSize[indEntry] == 0)
                    pHeader->bitvEntryLo &= ~(0x80000000L >> (indEntry - 32));
            }
        }

        /* unlink entry from list */
        pEntry->pEntryPrev->pEntryNext = pEntry->pEntryNext;
        pEntry->pEntryNext->pEntryPrev = pEntry->pEntryPrev;

        /* if free entry size is still nonzero, reconnect it */
        if (sizeNewFree != 0)
        {
            /* add entry to the start of the bucket list */
            pHead = (SbhEntry *)((char *)&pGroup->listHead[indNewFree] - 4);
            pEntry->pEntryNext = pHead->pEntryNext;
            pEntry->pEntryPrev = pHead;
            pHead->pEntryNext = pEntry;
            pEntry->pEntryNext->pEntryPrev = pEntry;

            /* test entry is sole member of bucket (next == prev) */
            if (pEntry->pEntryNext == pEntry->pEntryPrev)
            {
                if (indNewFree < 32)
                {
                    if (pRegion->cntRegionSize[indNewFree]++ == 0)
                        pHeader->bitvEntryHi |= 0x80000000L >> indNewFree;
                    pRegion->bitvGroupHi[indGroupUse] |=
                        0x80000000L >> indNewFree;
                }
                else
                {
                    if (pRegion->cntRegionSize[indNewFree]++ == 0)
                        pHeader->bitvEntryLo |= 0x80000000L >> (indNewFree - 32);
                    pRegion->bitvGroupLo[indGroupUse] |=
                        0x80000000L >> (indNewFree - 32);
                }
            }
        }
    }

    /* change size of free entry (front and back) */
    if (sizeNewFree != 0)
    {
        pEntry->sizeFront = sizeNewFree;
        ((SbhEntryEnd *)((char *)pEntry + sizeNewFree - 4))->sizeBack = sizeNewFree;
    }

    /* mark the allocated entry */
    pEntry = (SbhEntry *)((char *)pEntry + sizeNewFree);
    pEntry->sizeFront = sizeEntry + 1;
    ((SbhEntryEnd *)((char *)pEntry + sizeEntry - 4))->sizeBack = sizeEntry + 1;

    /* one more allocation in group - test if group was empty */
    if (pGroup->cntEntries++ == 0)
    {
        /* if allocating into deferred group, cancel deferral */
        if (pHeader == (SbhHeader *)__sbh_pHeaderDefer &&
            indGroupUse == __sbh_indGroupDefer)
            __sbh_pHeaderDefer = NULL;
    }

    pRegion->indGroupUse = indGroupUse;

    return (void *)((char *)pEntry + 4);
}

/* ======================================================================
 * 0x1001db72 - __sbh_alloc_new_region: add a HEADER to the header list,
 * allocate a REGION, reserve the 1MB region address space.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001db72 (was FUNCTION; provided by LIBCMT / library_msvc.h)
SbhHeader * __cdecl fcn_1001db72(void)
{
    SbhHeader * pHeader;

    /* if the list is full, realloc to extend its size */
    if (__sbh_cntHeaderList == __sbh_sizeHeaderList)
    {
        if (!(pHeader = (SbhHeader *)HeapReAlloc(_crtheap, 0, __sbh_pHeaderList,
                            (__sbh_sizeHeaderList + 16) * 20)))   /* sizeof(HEADER) */
            return NULL;

        __sbh_pHeaderList = pHeader;
        __sbh_sizeHeaderList += 16;
    }

    /* point to the new header in the list */
    pHeader = (SbhHeader *)__sbh_pHeaderList + __sbh_cntHeaderList;

    /* allocate a new region associated with the new header */
    if (!(pHeader->pRegion = (SbhRegion *)HeapAlloc(_crtheap, 8,
                                    sizeof(SbhRegion))))  /* HEAP_ZERO_MEMORY */
        return NULL;

    /* reserve address space for heap data in the region */
    if ((pHeader->pHeapData = VirtualAlloc(0, 0x100000,
                                     0x2000, 4)) == NULL)  /* MEM_RESERVE, PAGE_READWRITE */
    {
        HeapFree(_crtheap, 0, pHeader->pRegion);
        return NULL;
    }

    /* initialize alloc and commit group vectors */
    pHeader->bitvEntryHi = 0;
    pHeader->bitvEntryLo = 0;
    pHeader->bitvCommit = 0xffffffff;   /* BITV_COMMIT_INIT */

    /* complete entry by incrementing the list count */
    __sbh_cntHeaderList++;

    /* initialize index of group to try first (none defined yet) */
    pHeader->pRegion->indGroupUse = -1;

    return pHeader;
}

/* ======================================================================
 * 0x1001dc23 - __sbh_alloc_new_group: initialize a GROUP within the HEADER
 * region (commit + fill the group's page entries) and return its index.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001dc23 (was FUNCTION; provided by LIBCMT / library_msvc.h)
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

// FUNCTION: SERVER 0x1001dd1e (was FUNCTION; provided by LIBCMT / library_msvc.h)
int __cdecl fcn_1001dd1e(SbhHeader * pHeader, void * pvAlloc, int intNew)
{
    SbhRegion * pRegion;
    SbhGroup * pGroup;
    SbhEntry * pHead;
    SbhEntry * pEntry;
    SbhEntry * pNext;
    int sizeEntry;
    int sizeNext;
    int sizeNew;
    unsigned int indGroup;
    unsigned int indEntry;
    unsigned int indNext;
    unsigned int offRegion;

    /* add 8 bytes entry overhead and round up to next para size */
    sizeNew = (intNew + 2 * 4 + 15) & ~15;      /* 2 * sizeof(int) */

    pRegion = pHeader->pRegion;

    offRegion = (unsigned int)pvAlloc - (unsigned int)pHeader->pHeapData;
    indGroup = offRegion / 0x8000;
    pGroup = &pRegion->grpHeadList[indGroup];

    pEntry = (SbhEntry *)((char *)pvAlloc - 4);
    sizeEntry = pEntry->sizeFront - 1;

    pNext = (SbhEntry *)((char *)pEntry + sizeEntry);
    sizeNext = pNext->sizeFront;

    /* if the new size is larger than the current one */
    if (sizeNew > sizeEntry)
    {
        /* if next entry not free, or not large enough, fail */
        if ((sizeNext & 1) || (sizeNew > sizeEntry + sizeNext))
            return 0;                       /* FALSE */

        /* disconnect the next entry */
        indNext = (sizeNext >> 4) - 1;
        if (indNext > 63)
            indNext = 63;

        if (pNext->pEntryNext == pNext->pEntryPrev)
        {
            if (indNext < 32)
            {
                pRegion->bitvGroupHi[indGroup] &= ~(0x80000000L >> indNext);
                if (--pRegion->cntRegionSize[indNext] == 0)
                    pHeader->bitvEntryHi &= ~(0x80000000L >> indNext);
            }
            else
            {
                pRegion->bitvGroupLo[indGroup] &= ~(0x80000000L >> (indNext - 32));
                if (--pRegion->cntRegionSize[indNext] == 0)
                    pHeader->bitvEntryLo &= ~(0x80000000L >> (indNext - 32));
            }
        }

        pNext->pEntryPrev->pEntryNext = pNext->pEntryNext;
        pNext->pEntryNext->pEntryPrev = pNext->pEntryPrev;

        /* compute the new size of the next entry, test if nonzero */
        if ((sizeNext = sizeEntry + sizeNext - sizeNew) > 0)
        {
            /* compute the start of the next entry and connect it */
            pNext = (SbhEntry *)((char *)pEntry + sizeNew);

            indNext = (sizeNext >> 4) - 1;
            if (indNext > 63)
                indNext = 63;

            /* add the next entry to the start of the bucket list */
            pHead = (SbhEntry *)((char *)&pGroup->listHead[indNext] - 4);
            pNext->pEntryNext = pHead->pEntryNext;
            pNext->pEntryPrev = pHead;
            pHead->pEntryNext = pNext;
            pNext->pEntryNext->pEntryPrev = pNext;

            if (pNext->pEntryNext == pNext->pEntryPrev)
            {
                if (indNext < 32)
                {
                    if (pRegion->cntRegionSize[indNext]++ == 0)
                        pHeader->bitvEntryHi |= 0x80000000L >> indNext;
                    pRegion->bitvGroupHi[indGroup] |= 0x80000000L >> indNext;
                }
                else
                {
                    if (pRegion->cntRegionSize[indNext]++ == 0)
                        pHeader->bitvEntryLo |= 0x80000000L >> (indNext - 32);
                    pRegion->bitvGroupLo[indGroup] |=
                        0x80000000L >> (indNext - 32);
                }
            }

            /* adjust size fields of the next entry */
            pNext->sizeFront = sizeNext;
            ((SbhEntryEnd *)((char *)pNext + sizeNext - 4))->sizeBack = sizeNext;
        }

        /* adjust pEntry to its new size (plus one since allocated) */
        pEntry->sizeFront = sizeNew + 1;
        ((SbhEntryEnd *)((char *)pEntry + sizeNew - 4))->sizeBack = sizeNew + 1;
    }

    /* not larger, test if smaller */
    else if (sizeNew < sizeEntry)
    {
        /* adjust pEntry to the new smaller size */
        pEntry->sizeFront = sizeNew + 1;
        ((SbhEntryEnd *)((char *)pEntry + sizeNew - 4))->sizeBack = sizeNew + 1;

        /* set pEntry and sizeEntry to the leftover space */
        pEntry = (SbhEntry *)((char *)pEntry + sizeNew);
        sizeEntry -= sizeNew;

        indEntry = (sizeEntry >> 4) - 1;
        if (indEntry > 63)
            indEntry = 63;

        /* test if the next entry is free */
        if ((sizeNext & 1) == 0)
        {
            /* if so, disconnect it */
            indNext = (sizeNext >> 4) - 1;
            if (indNext > 63)
                indNext = 63;

            if (pNext->pEntryNext == pNext->pEntryPrev)
            {
                if (indNext < 32)
                {
                    pRegion->bitvGroupHi[indGroup] &= ~(0x80000000L >> indNext);
                    if (--pRegion->cntRegionSize[indNext] == 0)
                        pHeader->bitvEntryHi &= ~(0x80000000L >> indNext);
                }
                else
                {
                    pRegion->bitvGroupLo[indGroup] &= ~(0x80000000L >> (indNext - 32));
                    if (--pRegion->cntRegionSize[indNext] == 0)
                        pHeader->bitvEntryLo &= ~(0x80000000L >> (indNext - 32));
                }
            }

            pNext->pEntryPrev->pEntryNext = pNext->pEntryNext;
            pNext->pEntryNext->pEntryPrev = pNext->pEntryPrev;

            /* add the next entry size to the present */
            sizeEntry += sizeNext;
            indEntry = (sizeEntry >> 4) - 1;
            if (indEntry > 63)
                indEntry = 63;
        }

        /* connect the leftover space with any free next entry */
        pHead = (SbhEntry *)((char *)&pGroup->listHead[indEntry] - 4);
        pEntry->pEntryNext = pHead->pEntryNext;
        pEntry->pEntryPrev = pHead;
        pHead->pEntryNext = pEntry;
        pEntry->pEntryNext->pEntryPrev = pEntry;

        if (pEntry->pEntryNext == pEntry->pEntryPrev)
        {
            if (indEntry < 32)
            {
                if (pRegion->cntRegionSize[indEntry]++ == 0)
                    pHeader->bitvEntryHi |= 0x80000000L >> indEntry;
                pRegion->bitvGroupHi[indGroup] |= 0x80000000L >> indEntry;
            }
            else
            {
                if (pRegion->cntRegionSize[indEntry]++ == 0)
                    pHeader->bitvEntryLo |= 0x80000000L >> (indEntry - 32);
                pRegion->bitvGroupLo[indGroup] |= 0x80000000L >> (indEntry - 32);
            }
        }

        /* adjust size fields of the entry */
        pEntry->sizeFront = sizeEntry;
        ((SbhEntryEnd *)((char *)pEntry + sizeEntry - 4))->sizeBack = sizeEntry;
    }

    return 1;                           /* TRUE */
}

/* ======================================================================
 * 0x1001e014 - __old_sbh_new_region: create a new V5 region descriptor
 * (or reuse the static one), reserve/commit its address range, initialize
 * the region_map[] and the first committed pages.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e014 (was FUNCTION; provided by LIBCMT / library_msvc.h)
OldSbhRegion * __cdecl fcn_1001e014(void)
{
    OldSbhRegion * pregnew;
    OldSbhPage * ppage;
    int i;

    /* get a region descriptor; reuse the static one if it is available */
    if (g_old_heap->p_pages_begin == _OLD_NO_PAGES)
        pregnew = g_old_heap;
    else
    {
        if ((pregnew = (OldSbhRegion *)HeapAlloc(_crtheap, 0,
                                    sizeof(OldSbhRegion))) == NULL)
            return NULL;
    }

    /* reserve a new contiguous address range (a region) */
    if ((ppage = (OldSbhPage *)VirtualAlloc(NULL,
                                0x1000 * 1024,          /* _OLD_PAGES_PER_REGION */
                                0x2000, 4)) != NULL)    /* MEM_RESERVE, PAGE_READWRITE */
    {
        /* commit the first _OLD_PAGES_PER_COMMITMENT pages */
        if (VirtualAlloc(ppage, 0x1000 * 16, 0x1000, 4) != NULL)
        {
            /* insert *pregnew into the linked list of regions
             * (just before the static descriptor) */
            if (pregnew == g_old_heap)
            {
                if (g_old_heap->p_next_region == NULL)
                    g_old_heap->p_next_region = g_old_heap;
                if (g_old_heap->p_prev_region == NULL)
                    g_old_heap->p_prev_region = g_old_heap;
            }
            else
            {
                pregnew->p_next_region = g_old_heap;
                pregnew->p_prev_region = g_old_heap->p_prev_region;
                g_old_heap->p_prev_region = pregnew;
                pregnew->p_prev_region->p_next_region = pregnew;
            }

            /* fill in the rest of *pregnew */
            pregnew->p_pages_begin = ppage;
            pregnew->p_pages_end = ppage + 1024;
            pregnew->p_starting_region_map = &(pregnew->region_map[0]);
            pregnew->p_first_uncommitted =
                &(pregnew->region_map[16]);

            /* initialize pregnew->region_map[] */
            for (i = 0; i < 1024; i++)
            {
                if (i < 16)
                    pregnew->region_map[i].free_paras_in_page = 240;
                else
                    pregnew->region_map[i].free_paras_in_page = -1;

                pregnew->region_map[i].last_failed_alloc = 241;
            }

            /* initialize the pages */
            fcn_10021240(ppage, 0, 0x1000 * 16);
            while (ppage < pregnew->p_pages_begin + 16)
            {
                ppage->p_starting_alloc_map = &(ppage->alloc_map[0]);
                ppage->free_paras_at_start = 240;
                (ppage++)->alloc_map[240] = (unsigned char)-1;
            }

            return pregnew;
        }
        else
        {
            /* could not commit the pages, release the address space */
            VirtualFree(ppage, 0, 0x8000);      /* MEM_RELEASE */
        }
    }

    /* unable to create the new region; free the descriptor if necessary */
    if (pregnew != g_old_heap)
        HeapFree(_crtheap, 0, pregnew);

    return NULL;
}

/* ======================================================================
 * 0x1001e158 - __old_sbh_release_region: release the address space of a
 * V5 region, unlink its descriptor (the static one is only marked free).
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e158 (was FUNCTION; provided by LIBCMT / library_msvc.h)
void __cdecl fcn_1001e158(OldSbhRegion * preg)
{
    /* release the passed region */
    VirtualFree(preg->p_pages_begin, 0, 0x8000);

    /* update __old_sbh_p_starting_region, if necessary */
    if (__old_sbh_p_starting_region == preg)
        __old_sbh_p_starting_region = preg->p_prev_region;

    if (preg != g_old_heap)
    {
        /* update the linked list of region descriptors */
        preg->p_prev_region->p_next_region = preg->p_next_region;
        preg->p_next_region->p_prev_region = preg->p_prev_region;

        /* free the region descriptor */
        HeapFree(_crtheap, 0, preg);
    }
    else
    {
        /* mark the static descriptor as not associated with any region
         * (so it can be reused); only supported for this descriptor */
        g_old_heap->p_pages_begin = _OLD_NO_PAGES;
    }
}

/* ======================================================================
 * 0x1001e1ae - __old_sbh_decommit_pages: decommit 'count' fully free
 * pages in reverse order across regions; release a region once all of its
 * pages are uncommitted.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e1ae (was FUNCTION; provided by LIBCMT / library_msvc.h)
void __cdecl fcn_1001e1ae(int count)
{
    OldSbhRegion * preg1;
    OldSbhRegion * preg2;
    OldRegionMap * pregmap;
    int page_decommitted_flag;
    int i;

    /* scan the regions in reverse order looking for pages to decommit */
    preg1 = g_old_heap->p_prev_region;
    do
    {
        if (preg1->p_pages_begin != _OLD_NO_PAGES)
        {
            /* scan the pages in *preg1 in reverse order */
            for (i = 1023, page_decommitted_flag = 0,
                    pregmap = &(preg1->region_map[i]);
                 i >= 0; i--, pregmap--)
            {
                /* check if the pool page is unused and, if so, decommit it */
                if (pregmap->free_paras_in_page == 240)
                {
                    if (VirtualFree((preg1->p_pages_begin) + i, 0x1000,
                                    0x4000))       /* MEM_DECOMMIT */
                    {
                        /* mark the page as uncommitted, update the global
                         * decommitable-page count and the region's
                         * first_uncommitted pointer */
                        pregmap->free_paras_in_page = -1;

                        __old_sbh_decommitable_pages--;

                        if ((preg1->p_first_uncommitted == NULL) ||
                            (preg1->p_first_uncommitted > pregmap))
                            preg1->p_first_uncommitted = pregmap;

                        page_decommitted_flag++;
                        if (--count == 0)
                            break;
                    }
                }
            }

            /* save the region pointer, move to the previous region */
            preg2 = preg1;
            preg1 = preg1->p_prev_region;

            /* if all pages in the region are now uncommitted, release it */
            if (page_decommitted_flag &&
                (preg2->region_map[0].free_paras_in_page == -1))
            {
                for (i = 1, pregmap = &(preg2->region_map[1]);
                     (i < 1024) &&
                       (pregmap->free_paras_in_page == -1);
                     i++, pregmap++);

                if (i == 1024)
                    fcn_1001e158(preg2);
            }
        }
    }
    while ((preg1 != g_old_heap->p_prev_region) && (count > 0));
}

/* ======================================================================
 * 0x1001e270 - __old_sbh_find_block: locate a block in the V5 sbh.
 * Returns the alloc_map[] entry for the block, plus the region and page
 * descriptors through the output parameters.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e270 (was FUNCTION; provided by LIBCMT / library_msvc.h)
unsigned char * __cdecl fcn_1001e270(void * pblck, OldSbhRegion ** ppreg, OldSbhPage ** pppage)
{
    OldSbhRegion * preg;
    OldSbhPage * ppage;

    preg = g_old_heap;
    do
    {
        /* does the block lie within this region? */
        if ((pblck > (void *)preg->p_pages_begin) &&
            (pblck < (void *)preg->p_pages_end))
        {
            /* pblck lies within the region; carry out a couple of
             * important validity checks */
            if ((((unsigned)pblck & 0xf) == 0) &&
                (((unsigned)pblck & 0xfff) >= 0x100))
            {
                /* copy the region and page pointers back */
                *ppreg = preg;
                *pppage = ppage = (OldSbhPage *)((unsigned)pblck & ~0xfff);

                /* return the alloc_map[] entry of the block */
                return &(ppage->alloc_map[0]) +
                       ((OldPara *)pblck - &(ppage->alloc_blocks[0]));
            }

            return NULL;
        }
    }
    while ((preg = preg->p_next_region) != g_old_heap);

    return NULL;
}

/* ======================================================================
 * 0x1001e2c7 - __old_sbh_free_block: free a V5 block (region_map update +
 * alloc_map[] clear) and trigger page decommitment when a page empties.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e2c7 (was FUNCTION; provided by LIBCMT / library_msvc.h)
void __cdecl fcn_1001e2c7(OldSbhRegion * preg, OldSbhPage * ppage, unsigned char * pmap)
{
    OldRegionMap * pregmap;

    pregmap = &(preg->region_map[0]) + (ppage - preg->p_pages_begin);

    /* update the region_map[] entry */
    pregmap->free_paras_in_page += (int)*pmap;

    /* mark the alloc_map[] entry as free */
    *pmap = _OLD_FREE_PARA;

    /* clear the last_failed_alloc[] entry for the page */
    pregmap->last_failed_alloc = 241;       /* _OLD_NO_FAILED_ALLOC */

    /* if the page is completely free, count it toward decommitment */
    if (pregmap->free_paras_in_page == 240)
        if (++__old_sbh_decommitable_pages == 32)             /* 2 * _OLD_PAGES_PER_COMMITMENT */
            fcn_1001e1ae(16);
}

/* ======================================================================
 * 0x1001e30c - __old_sbh_alloc_block: allocate from the V5 sbh
 * (para_req = size in 16-byte paragraphs).  First pass tries already
 * committed pages, second pass commits new pages in an existing region,
 * last resort creates a new region.
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e30c (was FUNCTION; provided by LIBCMT / library_msvc.h)
void * __cdecl __old_sbh_alloc_block(size_t para_req)
{
    OldSbhRegion * preg;
    OldSbhPage * ppage;
    OldSbhPage * ppage2;
    OldRegionMap * pregmap;
    OldRegionMap * pregmap2;
    void * retp;
    int i, j;

    /* first pass: try to satisfy the request from committed pages */
    preg = __old_sbh_p_starting_region;

    do
    {
        if (preg->p_pages_begin != _OLD_NO_PAGES)
        {
            /* search from *p_starting_region_map to the end of the array */
            for (pregmap = preg->p_starting_region_map,
                    pregmap2 = &(preg->region_map[1024]),
                    ppage = preg->p_pages_begin +
                            (int)(pregmap - &(preg->region_map[0]));
                 pregmap < pregmap2;
                 pregmap++, ppage++)
            {
                /* if the page has at least para_req free paragraphs */
                if ((pregmap->free_paras_in_page >= (int)para_req) &&
                    (pregmap->last_failed_alloc > para_req))
                {
                    if ((retp = fcn_1001e514(ppage,
                                    pregmap->free_paras_in_page,
                                    para_req)) != NULL)
                    {
                        /* success: update the rover, free count and map */
                        __old_sbh_p_starting_region = preg;
                        pregmap->free_paras_in_page -= para_req;
                        preg->p_starting_region_map = pregmap;
                        return retp;
                    }
                    else
                    {
                        /* remember the failed request size */
                        pregmap->last_failed_alloc = para_req;
                    }
                }
            }

            /* if necessary, search from page 0 to the search start */
            for (pregmap = &(preg->region_map[0]),
                    pregmap2 = preg->p_starting_region_map,
                    ppage = preg->p_pages_begin;
                 pregmap < pregmap2;
                 pregmap++, ppage++)
            {
                if ((pregmap->free_paras_in_page >= (int)para_req) &&
                    (pregmap->last_failed_alloc > para_req))
                {
                    if ((retp = fcn_1001e514(ppage,
                                    pregmap->free_paras_in_page,
                                    para_req)) != NULL)
                    {
                        __old_sbh_p_starting_region = preg;
                        pregmap->free_paras_in_page -= para_req;
                        preg->p_starting_region_map = pregmap;
                        return retp;
                    }
                    else
                    {
                        pregmap->last_failed_alloc = para_req;
                    }
                }
            }
        }
    }
    while ((preg = preg->p_next_region) != __old_sbh_p_starting_region);

    /* second pass: look for an uncommitted page, starting at the
     * static descriptor rather than the rover */
    preg = g_old_heap;

    do
    {
        if ((preg->p_pages_begin != _OLD_NO_PAGES) &&
            (preg->p_first_uncommitted != NULL))
        {
            pregmap = preg->p_first_uncommitted;

            ppage = preg->p_pages_begin +
                    (pregmap - &(preg->region_map[0]));

            /* determine how many adjacent pages, up to 16, are
             * uncommitted (and can now be committed) */
            for (i = 0, pregmap2 = pregmap;
                 (pregmap2->free_paras_in_page == _OLD_UNCOMMITTED_PAGE) &&
                    (i < 16);
                 pregmap2++, i++);

            /* commit the pages */
            if (VirtualAlloc((void *)ppage,
                             i * 0x1000,
                             0x1000,
                             4) == ppage)    /* MEM_COMMIT, PAGE_READWRITE */
            {
                /* initialize the committed pages */
                fcn_10021240(ppage, i * 0x1000, 0);

                for (j = 0, ppage2 = ppage, pregmap2 = pregmap;
                     j < i;
                     j++, ppage2++, pregmap2++)
                {
                    /* initialize fields in the page header */
                    ppage2->p_starting_alloc_map = &(ppage2->alloc_map[0]);
                    ppage2->free_paras_at_start = 240;
                    ppage2->alloc_map[240] = (unsigned char)-1;

                    /* initialize the region_map[] entry for the page */
                    pregmap2->free_paras_in_page = 240;
                    pregmap2->last_failed_alloc = 241;
                }

                /* update the starting-region rover */
                __old_sbh_p_starting_region = preg;

                /* update p_first_uncommitted for the region */
                while ((pregmap2 < &(preg->region_map[1024])) &&
                       (pregmap2->free_paras_in_page != _OLD_UNCOMMITTED_PAGE))
                    pregmap2++;

                preg->p_first_uncommitted = (pregmap2 <
                    &(preg->region_map[1024])) ? pregmap2 : NULL;

                /* fulfill the request using the first new page */
                ppage->alloc_map[0] = (unsigned char)para_req;

                preg->p_starting_region_map = pregmap;
                pregmap->free_paras_in_page -= para_req;

                ppage->p_starting_alloc_map = &(ppage->alloc_map[para_req]);
                ppage->free_paras_at_start -= para_req;

                return (void *)&(ppage->alloc_blocks[0]);
            }
            else
            {
                /* commit failed; fall back to the Win32 heap manager */
                return NULL;
            }
        }
    }
    while ((preg = preg->p_next_region) != g_old_heap);

    /* everything failed so far; try to create a new region */
    if ((preg = fcn_1001e014()) != NULL)
    {
        /* the first few pages (16) have been committed; satisfy the
         * request out of the first page of the new region */
        ppage = preg->p_pages_begin;
        ppage->alloc_map[0] = (unsigned char)para_req;

        __old_sbh_p_starting_region = preg;
        ppage->p_starting_alloc_map = &(ppage->alloc_map[para_req]);
        ppage->free_paras_at_start = 240 - para_req;
        (preg->region_map[0]).free_paras_in_page -= (unsigned char)para_req;
        return (void *)&(ppage->alloc_blocks[0]);
    }

    return NULL;
}

/* ======================================================================
 * 0x1001e514 - __old_sbh_alloc_block_from_page: satisfy the request from
 * a specific V5 page (start at p_starting_alloc_map, then wrap to 0).
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e514 (was FUNCTION; provided by LIBCMT / library_msvc.h)
void * __cdecl fcn_1001e514(OldSbhPage * ppage, size_t free_para_count, size_t para_req)
{
    unsigned char * pmap1;
    unsigned char * pmap2;
    unsigned char * pstartmap;
    unsigned char * pendmap;
    size_t contiguous_free;

    pmap1 = pstartmap = ppage->p_starting_alloc_map;
    pendmap = &(ppage->alloc_map[240]);

    /* check if there are enough free paragraphs at p_starting_alloc_map
     * to satisfy the pending allocation request */
    if (ppage->free_paras_at_start >= para_req)
    {
        /* success right off: mark the alloc_map entry with the size */
        *pmap1 = (unsigned char)para_req;

        /* update the p_starting_alloc_map and free_paras_at_start fields */
        if ((pmap1 + para_req) < pendmap)
        {
            ppage->p_starting_alloc_map += para_req;
            ppage->free_paras_at_start -= para_req;
        }
        else
        {
            ppage->p_starting_alloc_map = &(ppage->alloc_map[0]);
            ppage->free_paras_at_start = 0;
        }

        /* derive and return a pointer to the newly allocated paragraphs */
        return (void *)&(ppage->alloc_blocks[pmap1 - &(ppage->alloc_map[0])]);
    }

    /* see if the search loop can be started just beyond the paragraphs
     * examined above */
    if (*(pmap1 + ppage->free_paras_at_start) != _OLD_FREE_PARA)
        pmap1 += ppage->free_paras_at_start;

    while (pmap1 + para_req < pendmap)
    {
        if (*pmap1 == _OLD_FREE_PARA)
        {
            /* pmap1 refers to a free paragraph; determine if there are
             * enough contiguous free paragraphs to satisfy the request */
            for (pmap2 = pmap1 + 1, contiguous_free = 1;
                 *pmap2 == _OLD_FREE_PARA;
                 pmap2++, contiguous_free++);

            if (contiguous_free < para_req)
            {
                /* not enough contiguous free paragraphs; do a little
                 * bookkeeping before going on to the next iteration */
                if (pmap1 == pstartmap)
                {
                    /* make sure free_paras_at_start is up to date */
                    ppage->free_paras_at_start = contiguous_free;
                }
                else
                {
                    /* these free paragraphs will not be revisited */
                    if ((free_para_count -= contiguous_free) < para_req)
                        return NULL;
                }

                /* update pmap1 for the next iteration of the loop */
                pmap1 = pmap2;
            }
            else
            {
                /* success: update the page fields */
                if ((pmap1 + para_req) < pendmap)
                {
                    ppage->p_starting_alloc_map = pmap1 + para_req;
                    ppage->free_paras_at_start = contiguous_free - para_req;
                }
                else
                {
                    ppage->p_starting_alloc_map = &(ppage->alloc_map[0]);
                    ppage->free_paras_at_start = 0;
                }

                /* mark the alloc_map entry with the size of the request */
                *pmap1 = (unsigned char)para_req;

                return (void *)&(ppage->alloc_blocks[pmap1 -
                    &(ppage->alloc_map[0])]);
            }
        }
        else
        {
            /* pmap1 points to the start of an allocated block; skip it */
            pmap1 = pmap1 + *pmap1;
        }
    }

    /* now start at index 0 and walk towards, but not past, the
     * starting index, looking for a string of free paragraphs */
    pmap1 = &(ppage->alloc_map[0]);

    while ((pmap1 < pstartmap) && (pmap1 + para_req < pendmap))
    {
        if (*pmap1 == _OLD_FREE_PARA)
        {
            for (pmap2 = pmap1 + 1, contiguous_free = 1;
                 *pmap2 == _OLD_FREE_PARA;
                 pmap2++, contiguous_free++);

            if (contiguous_free < para_req)
            {
                /* update the count of unvisited free paragraphs */
                if ((free_para_count -= contiguous_free) < para_req)
                    return NULL;

                pmap1 = pmap2;
            }
            else
            {
                if ((pmap1 + para_req) < pendmap)
                {
                    ppage->p_starting_alloc_map = pmap1 + para_req;
                    ppage->free_paras_at_start = contiguous_free - para_req;
                }
                else
                {
                    ppage->p_starting_alloc_map = &(ppage->alloc_map[0]);
                    ppage->free_paras_at_start = 0;
                }

                *pmap1 = (unsigned char)para_req;

                return (void *)&(ppage->alloc_blocks[pmap1 -
                    &(ppage->alloc_map[0])]);
            }
        }
        else
        {
            pmap1 = pmap1 + *pmap1;
        }
    }

    return NULL;
}

/* ======================================================================
 * 0x1001e638 - __old_sbh_resize_block: grow or shrink a V5 block in
 * place (pmap = alloc_map[] entry, sizes in 16-byte paragraphs).
 * ==================================================================== */

// FUNCTION: SERVER 0x1001e638 (was FUNCTION; provided by LIBCMT / library_msvc.h)
int __cdecl fcn_1001e638(OldSbhRegion * preg, OldSbhPage * ppage, unsigned char * pmap, size_t new_para_sz)
{
    unsigned char * pmap2;
    unsigned char * pmap3;
    OldRegionMap * pregmap;
    size_t old_para_sz;
    size_t free_para_count;
    int retval = 0;

    pregmap = &(preg->region_map[ppage - preg->p_pages_begin]);

    if ((old_para_sz = *pmap) > new_para_sz)
    {
        /* the allocation block is to be shrunk */
        *pmap = (unsigned char)new_para_sz;

        pregmap->free_paras_in_page += old_para_sz - new_para_sz;

        pregmap->last_failed_alloc = 241;

        retval++;
    }
    else if (old_para_sz < new_para_sz)
    {
        /* the allocation block is to be grown (if possible) */
        if (&(ppage->alloc_map[240]) >= (pmap + new_para_sz))
        {
            /* determine if there are sufficient free paragraphs to
             * expand the block to the desired new size */
            for (pmap2 = pmap + old_para_sz,
                    pmap3 = pmap + new_para_sz;
                 (pmap2 < pmap3) && (*pmap2 == _OLD_FREE_PARA);
                 pmap2++);

            if (pmap2 == pmap3)
            {
                /* success, mark the resized allocation */
                *pmap = (unsigned char)new_para_sz;

                /* check whether the p_starting_alloc_map and
                 * free_paras_at_start fields need to be updated */
                if ((pmap <= ppage->p_starting_alloc_map) &&
                    (pmap3 > ppage->p_starting_alloc_map))
                {
                    if (pmap3 < &(ppage->alloc_map[240]))
                    {
                        ppage->p_starting_alloc_map = pmap3;
                        /* determine how many contiguous free paragraphs
                         * there are starting at *pmap3 */
                        for (free_para_count = 0;
                             *pmap3 == _OLD_FREE_PARA;
                             free_para_count++, pmap3++);
                        ppage->free_paras_at_start = free_para_count;
                    }
                    else
                    {
                        ppage->p_starting_alloc_map = &(ppage->alloc_map[0]);
                        ppage->free_paras_at_start = 0;
                    }
                }

                /* update the region_map[] entry */
                pregmap->free_paras_in_page += (old_para_sz - new_para_sz);

                retval++;
            }
        }
    }

    return retval;
}
