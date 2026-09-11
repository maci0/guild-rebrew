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
#include "rebrew_types.h"

/* V6 sbh structures (winheap.h tagHeader/tagRegion/tagGroup/tagEntry). */
// SIZE 0xc
typedef struct tagEntry
{
    int                 sizeFront;      /* +0x00 */
    struct tagEntry *   pEntryNext;     /* +0x04 */
    struct tagEntry *   pEntryPrev;     /* +0x08 */
} SbhEntry;

// SIZE 0x8
typedef struct tagListHead
{
    SbhEntry *          pEntryNext;     /* +0x00 */
    SbhEntry *          pEntryPrev;     /* +0x04 */
} SbhListHead;

// SIZE 0x204
typedef struct tagGroup
{
    int                 cntEntries;     /* +0x00 */
    SbhListHead         listHead[64];   /* +0x04 */
} SbhGroup;

// SIZE 0x41c4
typedef struct tagRegion
{
    int                 indGroupUse;    /* +0x00 */
    char                cntRegionSize[64];  /* +0x04 */
    unsigned int        bitvGroupHi[32];    /* +0x44 */
    unsigned int        bitvGroupLo[32];    /* +0xc4 */
    SbhGroup            grpHeadList[32];    /* +0x144 */
} SbhRegion;

// SIZE 0x14
typedef struct tagHeader
{
    unsigned int        bitvEntryHi;    /* +0x00 */
    unsigned int        bitvEntryLo;    /* +0x04 */
    unsigned int        bitvCommit;     /* +0x08 */
    void *              pHeapData;      /* +0x0c */
    SbhRegion *         pRegion;        /* +0x10 */
} SbhHeader;

/* V5 ("old") sbh structures (winheap.h __old_sbh_*). */

/* V6 sbh globals that are not covered by data_globals.c.  The header-list
 * count/array/cursor (0x11766440/44/38), the deferred-group pointer
 * (0x1176643c's pair member 0x11766434 is here) and the old-sbh static
 * region head (0x10031b78) are defined in data_globals.c. */
// DATA: SERVER 0x11766430
int __sbh_sizeHeaderList;                 /* __sbh_sizeHeaderList - allocated size of header list */
// DATA: SERVER 0x11766434
int __sbh_indGroupDefer;                 /* __sbh_indGroupDefer - deferred group index */
// DATA: SERVER 0x1176643c
void * __sbh_pHeaderDefer;           /* __sbh_pHeaderDefer - deferred group header */

// DATA: SERVER 0x10033b98
OldSbhRegion * __old_sbh_p_starting_region;   /* __old_sbh_p_starting_region */
