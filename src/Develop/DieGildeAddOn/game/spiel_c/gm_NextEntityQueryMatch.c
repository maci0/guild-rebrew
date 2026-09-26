#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

// GLOBAL: SERVER 0x10035450
extern int g_query_limit; /* 0x10035450 */
extern int g_query_filter_max_id; /* 0x10030b94 */
extern int g_query_filter_owner; /* 0x10030b98 */
extern unsigned short g_query_filter_type; /* 0x10030b9c */
// GLOBAL: SERVER 0x101398a0
extern int g_dispatch_table_b[]; /* 0x101398a0 */
// GLOBAL: SERVER 0x1013989c
extern int g_dispatch_table_a[]; /* 0x1013989c */

// FUNCTION: SERVER 0x10016290
// gm_NextEntityQueryMatch
//   RELOC 464/464.
//   The last wall was a two-web callee-save colouring tie-break: the depth
//   value lives across the whole loop, while the limit (loop top), the count
//   (loop bottom), g_item_def_table (state block) and [current+0x14] (tail)
//   coalesce into one web of short ranges. The target gives edi to the long
//   web and esi to the short one; every spelling that kept a named
//   `int stack_depth` local got the reverse, for 439/464 with 19 RR and 5
//   SIB-form differences and the size and block layout already exact.
//   The fix is Finding 12 in docs/msvc6-allocator.md: delete the local and
//   read g_query_match_count directly at all seven sites. The local was
//   already kept in lockstep with the global on every path, so this is
//   semantics-neutral; without it the value is an anonymous CSE'd load born
//   at its first use, which orders the two webs the way the target has them.
//   Partial conversions do not pay: converting only the tail store or only
//   the pop arm stays at 439, and keeping the entry arm on the local falls to
//   191/466. Hoisting the tail `fld` to function scope is neutral (also
//   464/464), so the local body form is kept.
//   Earlier passes, for the levers they establish:
//   (a) Type-compare arms. HIT at 0x10016373 and MISS at 0x10016386 share an
//   11-byte prefix that msvc6 cross-jumps, tail-merging MISS into the nomatch
//   block and losing 15 bytes. Both arms need the full cursor reload with the
//   flag store first; only the flag-first position breaks the merge.
//   (b) Owner check. `if (field != owner) goto lab_nomatch; is_match = 1;`
//   compiles to a `je` past the store; the target has `jne` to the shared
//   nomatch block. The if/else spelling emits the target's polarity.
//   (c) Tail dispatch. The target lays the advance arm (flag1 != 0) first and
//   repeats `test cl,cl; je +2; mov ebx,eax` inside each arm instead of
//   hoisting it above the flag1 test.
//   (d) Loop guard as `while (count < limit)` with the two in-loop exits as
//   `break` merges the three exits into one epilogue and gives the target's
//   shrink-wrapped prologue (`push ebx` alone before the entry null-check).
//   (e) The max_id word load hoisted into a named `cur_id` local before the
//   0x7fff guard gives `xor ecx,ecx; mov cx,[eax]; cmp ecx,edx`; without it
//   the load takes edi. Merging the guard into the inner compare collapses it.
//   (f) filter_type_cache and the gm_GetEntityType result as `unsigned short`
//   tested against 0xffff give the target's 5-byte `cmp bp,0xffff`.
//   (g) g_query_filter_state is `unsigned char` tree-wide. With the global
//   unsigned, the target byte compare at 0x100163b6 needs both `!= 0xff`
//   without the old `(char)` cast and `(unsigned char) tbl[eid]` on the item
//   read; applying only one scores 350/473 or 331/472. The companion
//   gm_ff_Objekt needs the same unsigned declaration (char -> 222/320).
//   The shared `lab_nomatch: is_match = 0;` also fixes a real semantic bug:
//   the target clears cl on both mismatch paths, while an older revision
//   cleared it only in the max_id arm, so with g_query_flag3 set an owner
//   mismatch returned the entity as a match.
//   Probe harness and variants in .scratch/neqm-l4/ (gen1.py, score.py,
//   regs.sh); superseded probe sets in .scratch/neqm2/ and .scratch/neqm3/.


unsigned short __cdecl gm_GetEntityType(short* entity);

void* __cdecl gm_NextEntityQueryMatch(void)
{
    unsigned short* current;
    unsigned short* matched_ent;
    unsigned short filter_type_cache;
    unsigned short cur_id;
    char is_match;

    current = g_query_cursor;
    matched_ent = (unsigned short*)0;
    is_match = 0;
    if (current == (unsigned short*)0) {
        return (void*)current;
    }
    if (g_query_active != 0) {
        g_query_active = 0;
        if (g_query_flag2 != 0 && *(int*)((char*)current + 0x14) != 0) {
            g_dispatch_table_b[g_query_match_count] = *(int*)((char*)current + 0x14);
            g_query_match_count++;
            goto have_depth;
        }
    }
have_depth:
    while (g_query_count < g_query_limit) {
        filter_type_cache = g_query_filter_type;
        if (current == (unsigned short*)0) {
            break;
        }
        if (is_match != 0) {
            break;
        }
        while (*current == 0) {
            current = (unsigned short*)((char*)current + 0x43);
            g_query_cursor = current;
        }
        if (g_query_flag3 != 0) {
            is_match = 1;
        }
        if (g_query_filter_max_id != 0x7fff) {
            cur_id = *current;
            if (cur_id != g_query_filter_max_id) {
                goto lab_nomatch;
            }
            is_match = 1;
        }
        if (g_query_filter_owner != -1) {
            if (*(int*)((char*)current + 2) == g_query_filter_owner) {
                is_match = 1;
            } else {
                goto lab_nomatch;
            }
        }
        if (filter_type_cache != 0xffff) {
            unsigned short res;
            res = gm_GetEntityType((short*)current);
            filter_type_cache = g_query_filter_type;
            if (res == filter_type_cache) {
                is_match = 1;
                current = g_query_cursor;
                goto lab_395;
            }
            is_match = 0;
            current = g_query_cursor;
            goto lab_3bc;
        }
lab_395:
        if (g_query_filter_state != 0xff) {
            unsigned int eid;
            char* tbl;
            eid = (unsigned int)*current;
            tbl = g_item_def_table;
            tbl += eid * 0x40;
            is_match = (unsigned char) tbl[eid] == g_query_filter_state;
        }
        goto lab_3bc;
lab_nomatch:
        is_match = 0;
lab_3bc:
        if (g_query_flag1 != 0) {
            if (is_match != 0) {
                matched_ent = current;
            }
            current = (unsigned short*)((char*)current + 0x43);
            g_query_count++;
            g_query_cursor = current;
        } else {
            if (is_match != 0) {
                matched_ent = current;
            }
            current = *(unsigned short**)((char*)current + 0x3f);
            g_query_cursor = current;
            if (current != (unsigned short*)0) {
                int fld;
                fld = *(int*)((char*)current + 0x14);
                if (fld != 0 && g_query_flag2 != 0) {
                    g_dispatch_table_b[g_query_match_count] = fld;
                    goto lab_43e;
                }
            } else {
                if (g_query_flag2 != 0 && g_query_match_count != 0) {
                    current = (unsigned short*)g_dispatch_table_a[g_query_match_count];
                    g_query_match_count--;
                    g_query_cursor = current;
                    if (*(int*)((char*)current + 0x14) != 0) {
                        g_dispatch_table_b[g_query_match_count] = *(int*)((char*)current + 0x14);
lab_43e:
                        g_query_match_count++;
                    }
                }
            }
        }
    }
    return (void*)matched_ent;
}

// GLOBAL: SERVER 0x10035468
unsigned short* g_query_cursor;
extern unsigned char g_query_filter_state;
// GLOBAL: SERVER 0x1003545d
char g_query_flag2;
// GLOBAL: SERVER 0x10035434
int g_citizen_count;
// GLOBAL: SERVER 0x10035439
unsigned char g_current_season;
// GLOBAL: SERVER 0x10035444
int g_dynasty_field_44;
// GLOBAL: SERVER 0x10035448
char g_dynasty_field_48;
// GLOBAL: SERVER 0x10035449
char g_dynasty_field_49;
// GLOBAL: SERVER 0x1003544c
int g_dynasty_field_4c;
// GLOBAL: SERVER 0x10035464
unsigned char* g_query_filter_base;
/* Round-558: same-size majority types that still emit BSS commons.
 * Incomplete [] does not emit; sized arrays broke .text layout. */
// GLOBAL: SERVER 0x1003546c
unsigned short* g_entity_table_end;
// GLOBAL: SERVER 0x10035880
int g_current_year;
// GLOBAL: SERVER 0x10035884
unsigned short g_current_hour;
// GLOBAL: SERVER 0x10035888
int g_clock_copy_mid;
// GLOBAL: SERVER 0x1003588c
short g_clock_copy_tail;
/* 13 other TUs declare this `unsigned char g_slot_table[]` and the metadata
   records a 2-byte object at 0x100358a0; a pointer definition was the only
   outlier (round 925). */
unsigned char g_slot_table[2];
/* Indexed as `char g_entity_state_base[]` by cm_ExCreateCitizen.c and
   gm_Open.c; metadata records a 2-byte object at 0x100358a2 (round 925). */
// GLOBAL: SERVER 0x100358a2
char g_entity_state_base[2];
// GLOBAL: SERVER 0x100358fc
int g_entity_ref_table;
/* Indexed as `unsigned char g_entity_type_bytes[]` by sim.c, spiel62.c and
   gm_Open.c; metadata: 1-byte object at 0x10035a04 (round 925). */
unsigned char g_entity_type_bytes[1];

