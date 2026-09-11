/* Types the generated rebrew_globals.h names.  Each was defined inside the TU
 * that first needed it, which works until the globals header is included
 * somewhere else and cannot see them.  Field layouts are unchanged. */

#ifndef REBREW_TYPES_H
#define REBREW_TYPES_H

/* rterr_entry: int num + char* text = 8 bytes. */
struct rterr_entry { int num; char* text; };

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

#endif /* REBREW_TYPES_H */
