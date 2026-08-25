/* sbh_globals.c - GROUP B: small-block-heap (sbh) data globals used by the
 * allocator pool helpers in sbh_pool.c.
 *
 * The game replaced the CRT's small-block heap with its own copy (sbheap.c
 * family).  The V6 sbh ("pool allocator", allocator mode 3) keeps its
 * header list at 0x11766430-0x11766444; the V5 "old" sbh ("block
 * allocator", mode 2) keeps its region descriptor list at 0x10031b78.
 *
 * Each // DATA: marker pins the symbol to its original VA (rebrew DATA
 * mechanism).  rebrew postlink converges the linked layout onto the
 * reference (copies the reference's .data raw bytes and rewrites .text data
 * operands to reference values), so these definitions only need to make the
 * link resolve and to carry the right VA/size metadata.
 */
#include <stddef.h>

/* V6 sbh structures (winheap.h tagHeader/tagRegion/tagGroup/tagEntry). */
typedef struct tagEntry
{
    int                 sizeFront;      /* +0x00 */
    struct tagEntry *   pEntryNext;     /* +0x04 */
    struct tagEntry *   pEntryPrev;     /* +0x08 */
} SbhEntry;

typedef struct tagListHead
{
    SbhEntry *          pEntryNext;     /* +0x00 */
    SbhEntry *          pEntryPrev;     /* +0x04 */
} SbhListHead;

typedef struct tagGroup
{
    int                 cntEntries;     /* +0x00 */
    SbhListHead         listHead[64];   /* +0x04 */
} SbhGroup;

typedef struct tagRegion
{
    int                 indGroupUse;    /* +0x00 */
    char                cntRegionSize[64];  /* +0x04 */
    unsigned int        bitvGroupHi[32];    /* +0x44 */
    unsigned int        bitvGroupLo[32];    /* +0xc4 */
    SbhGroup            grpHeadList[32];    /* +0x144 */
} SbhRegion;

typedef struct tagHeader
{
    unsigned int        bitvEntryHi;    /* +0x00 */
    unsigned int        bitvEntryLo;    /* +0x04 */
    unsigned int        bitvCommit;     /* +0x08 */
    void *              pHeapData;      /* +0x0c */
    SbhRegion *         pRegion;        /* +0x10 */
} SbhHeader;

/* V5 ("old") sbh structures (winheap.h __old_sbh_*). */
typedef char            OldPara[16];

typedef struct __old_region_map
{
    int                 free_paras_in_page;   /* +0x00 */
    unsigned int        last_failed_alloc;    /* +0x04 */
} OldRegionMap;

typedef struct __old_sbh_page
{
    unsigned char *     p_starting_alloc_map; /* +0x00 */
    unsigned int        free_paras_at_start;  /* +0x04 */
    unsigned char       alloc_map[241];       /* +0x08 */
    unsigned char       reserved[7];          /* +0xf9 */
    OldPara             alloc_blocks[240];    /* +0x100 */
} OldSbhPage;

typedef struct __old_sbh_region
{
    struct __old_sbh_region * p_next_region;       /* +0x00 */
    struct __old_sbh_region * p_prev_region;       /* +0x04 */
    OldRegionMap *           p_starting_region_map;/* +0x08 */
    OldRegionMap *           p_first_uncommitted;  /* +0x0c */
    OldSbhPage *             p_pages_begin;        /* +0x10 */
    OldSbhPage *             p_pages_end;          /* +0x14 */
    OldRegionMap             region_map[1025];     /* +0x18 */
} OldSbhRegion;

/* V6 sbh globals that are not covered by data_globals.c.  The header-list
 * count/array/cursor (0x11766440/44/38), the deferred-group pointer
 * (0x1176643c's pair member 0x11766434 is here) and the old-sbh static
 * region head (0x10031b78) are defined in data_globals.c. */
// DATA: SERVER 0x11766430
int g_11766430 = 0;                 /* __sbh_sizeHeaderList - allocated size of header list */
// DATA: SERVER 0x11766434
int g_11766434 = 0;                 /* __sbh_indGroupDefer - deferred group index */
// DATA: SERVER 0x1176643c
void * g_1176643c = NULL;           /* __sbh_pHeaderDefer - deferred group header */

// DATA: SERVER 0x10033b98
OldSbhRegion * g_10033b98 = NULL;   /* __old_sbh_p_starting_region */
