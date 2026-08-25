#include <windows.h>

extern char g_query_active; /* 0x10035454 */
extern int g_query_count; /* 0x10035458 */
extern char g_query_flag1; /* 0x1003545c */
extern char g_query_flag2; /* 0x1003545d */
extern char g_query_flag3; /* 0x1003545e */
extern unsigned short* g_query_cursor; /* 0x10035468 */
extern char* g_item_def_table; /* 0x101de450 */
extern int g_query_limit; /* 0x10035450 */
extern int g_query_filter_max_id; /* 0x10030b94 */
extern int g_query_filter_owner; /* 0x10030b98 */
extern short g_query_filter_type; /* 0x10030b9c */
extern char g_query_filter_state; /* 0x10030b9e */
extern int g_query_match_count; /* 0x100a8c38 */
extern int g_dispatch_table_b[]; /* 0x101398a0 */
extern int g_dispatch_table_a[]; /* 0x1013989c */

// FUNCTION: SERVER 0x10016290
// gm_NextEntityQueryMatch
//   combos, 8+ C shapes). Original: split prologue (only `push ebx` before the
//   entry null-check, ebp/esi/edi pushed after), `stack_depth` in edi (ours esi),
//   no loop rotation (null-check at loop top; ours rotates it to the bottom),
//   shared `mov eax, ebx` epilogue (ours folds the count>=limit exit to
//   `xor eax,eax`). All are allocator/scheduler behaviors no available
//   compiler build reproduces. ~60 bytes of structural diff remain.

unsigned short __cdecl gm_GetEntityType(short* entity);

void* __cdecl gm_NextEntityQueryMatch(void)
{
    unsigned short* current;
    unsigned short* matched_ent;
    short filter_type_cache;
    int stack_depth;
    char is_match;

    current = g_query_cursor;
    matched_ent = (unsigned short*)0;
    is_match = 0;
    if (current == (unsigned short*)0) {
        return (void*)matched_ent;
    }
    if (g_query_active != 0) {
        g_query_active = 0;
        if (g_query_flag2 != 0 && *(int*)((char*)current + 0x14) != 0) {
            g_dispatch_table_b[g_query_match_count] = *(int*)((char*)current + 0x14);
            g_query_match_count++;
        }
    }
    stack_depth = g_query_match_count;
    filter_type_cache = g_query_filter_type;
    if (g_query_count >= g_query_limit) {
        return (void*)matched_ent;
    }
    do {
        if (current == (unsigned short*)0) {
            return (void*)matched_ent;
        }
        if (is_match != 0) {
            return (void*)matched_ent;
        }
        while (*current == 0) {
            current = (unsigned short*)((char*)current + 0x43);
            g_query_cursor = current;
        }
        if (g_query_flag3 != 0) {
            is_match = 1;
        }
        if (g_query_filter_max_id != 0x7fff) {
            is_match = 0;
            if (*current != g_query_filter_max_id) {
                goto lab_3bc;
            }
            is_match = 1;
        }
        if (g_query_filter_owner != -1) {
            if (*(int*)((char*)current + 2) != g_query_filter_owner) {
                goto lab_3bc;
            }
            is_match = 1;
        }
        if (filter_type_cache != -1) {
            short res;
            res = gm_GetEntityType((short*)current);
            filter_type_cache = g_query_filter_type;
            stack_depth = g_query_match_count;
            if (res != filter_type_cache) {
                current = g_query_cursor;
                stack_depth = g_query_match_count;
                is_match = 0;
                goto lab_3bc;
            }
            current = g_query_cursor;
            stack_depth = g_query_match_count;
            is_match = 1;
        }
lab_395:
        if (g_query_filter_state != (char)0xff) {
            unsigned short eid;
            char* tbl;
            eid = *current;
            tbl = g_item_def_table;
            is_match = *(char*)(tbl + (unsigned int)eid * 0x41) == g_query_filter_state;
        }
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
            if (current == (unsigned short*)0) {
                if (g_query_flag2 != 0 && stack_depth != 0) {
                    current = (unsigned short*)g_dispatch_table_a[stack_depth];
                    stack_depth--;
                    g_query_cursor = current;
                    g_query_match_count = stack_depth;
                    if (*(int*)((char*)current + 0x14) != 0) {
                        g_dispatch_table_b[stack_depth] = *(int*)((char*)current + 0x14);
                        goto lab_43e;
                    }
                }
            } else {
                if (*(int*)((char*)current + 0x14) != 0 && g_query_flag2 != 0) {
                    g_dispatch_table_b[stack_depth] = *(int*)((char*)current + 0x14);
lab_43e:
                    stack_depth++;
                    g_query_match_count = stack_depth;
                }
            }
        }
    } while (g_query_count < g_query_limit);
    return (void*)matched_ent;
}

unsigned short* g_query_cursor;
int g_query_filter_owner = 0xffffffff;
char g_query_filter_state = 255;
char g_query_flag2;
extern int g_query_match_count;
extern unsigned char g_entity_base;
extern int g_some_limit;
int g_citizen_count;
unsigned char g_current_season;
int g_dynasty_field_44;
int g_dynasty_field_48;
char g_dynasty_field_49;
int g_dynasty_field_4c;
extern char g_query_flag1;
extern char g_query_flag3;
unsigned char* g_query_filter_base;
int g_entity_table_end;
int g_current_year;
int g_default_value_b;
int g_default_value_c;
short g_default_value_d;
char* g_slot_table;
char g_entity_state_base;
int g_entity_ref_table;
char g_entity_type_bytes;

