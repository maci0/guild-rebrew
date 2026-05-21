#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl __ftol(void);

typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
;
void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl _getpid(void);
void __cdecl vfs_EntityCleanup(char*);
extern unsigned short* g_query_base;
extern int g_query_limit;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* g_entity_ptr;
extern int g_entity_type_table;
extern unsigned char g_current_season;
extern int g_active_player_count;
extern char* g_item_def_table;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern unsigned short* g_query_cursor;
extern char g_query_active;
extern char g_query_flag2;
extern int g_query_count;
extern int g_query_filter_max_id;
extern int g_query_filter_owner;
extern short g_query_filter_type;
extern char g_query_filter_state;
extern char g_query_flag1;
extern char g_query_flag3;
extern int g_query_match_count;
extern int* g_dispatch_table_b;
extern int* g_dispatch_table_a;
extern char* g_array_base;

// STUB: SERVER 0x10016290
// gm_NextEntityQueryMatch

unsigned short __cdecl gm_GetEntityType(short* entity);

void* __cdecl gm_NextEntityQueryMatch(void)
{
	WORD* candidate_ptr;
	short entity_type_result;
	unsigned short* scan_ptr;
	unsigned short* current;
	unsigned short* matched_ent;
	short filter_type_cache;
	int stack_depth;
	int is_match;
	WORD entry_val;

	current = g_query_cursor;
	matched_ent = (unsigned short*) 0x0;
	is_match = 0;

	if (g_query_cursor == (WORD*) 0x0) {
		return (void*) 0x0;
	}

	if ((g_query_active != '\0') && (g_query_active = '\0', g_query_flag2 != '\0') &&
		(*(int*) ((int) g_query_cursor + 10) != 0)) {
		*(int*) (&g_dispatch_table_b + g_query_match_count * 4) = *(int*) (g_query_cursor + 10);
		g_query_match_count = g_query_match_count + 1;
	}

	stack_depth = g_query_match_count;
	filter_type_cache = g_query_filter_type;

	if (g_query_count < g_query_limit) {
		do {
			if (current == (WORD*) 0x0) {
				return matched_ent;
			}
			if (is_match) {
				return matched_ent;
			}
			entry_val = *current;
			candidate_ptr = current;
			scan_ptr = g_query_cursor;

			while (g_query_cursor = candidate_ptr, entry_val == 0) {
				scan_ptr = (unsigned short*) ((int) g_query_cursor + 0x43);
				entry_val = *scan_ptr;
				candidate_ptr = scan_ptr;
			}

			if (g_query_flag3 != '\0') {
				is_match = 1;
			}

			if (g_query_filter_max_id == 0x7fff) {
				if (g_query_filter_owner != -1) {
					if (*(int*) (g_query_cursor + 1) != g_query_filter_owner) {
						goto LAB_10016382;
					}
					is_match = 1;
				}
				if (filter_type_cache != -1) {
					candidate_ptr = g_query_cursor;
					g_query_cursor = scan_ptr;
					entity_type_result = gm_GetEntityType(candidate_ptr);
					stack_depth = g_query_match_count;
					filter_type_cache = g_query_filter_type;
					if (entity_type_result != g_query_filter_type) {
						is_match = 0;
						goto LAB_100163bc;
					}
					is_match = 1;
				}
				if (g_query_filter_state != -1) {
					is_match = *(char*) (g_game_initialized + (unsigned int) *g_query_cursor * 0x41) == g_query_filter_state;
				}
			}
			else {
				if (*g_query_cursor == g_query_filter_max_id) {
					is_match = 1;
					goto check_filters;
				}
			LAB_10016382:
				is_match = 0;
			}
		LAB_100163bc:
		check_filters:
			if (g_query_flag1 == '\0') {
				if (is_match) {
					matched_ent = g_query_cursor;
				}
				current = *(unsigned short**) ((int) g_query_cursor + 0x3f);
				g_query_cursor = current;
				if (current == (WORD*) 0x0) {
					if ((g_query_flag2 != '\0') && (stack_depth != 0)) {
						current = *(unsigned short**) (&g_dispatch_table_a + stack_depth * 4);
						stack_depth = stack_depth - 1;
						g_query_cursor = current;
						g_query_match_count = stack_depth;
						if (*(int*) (current + 10) != 0) {
							*(int*) (&g_dispatch_table_b + stack_depth * 4) = *(int*) (current + 10);
							goto LAB_1001643e;
						}
					}
				}
				else if ((*(int*) (current + 10) != 0) && (g_query_flag2 != '\0')) {
					*(int*) (&g_dispatch_table_b + stack_depth * 4) = *(int*) (current + 10);
				LAB_1001643e:
					stack_depth = stack_depth + 1;
					g_query_match_count = stack_depth;
				}
			}
			else {
				if (is_match) {
					matched_ent = g_query_cursor;
				}
				current = (unsigned short*) ((int) g_query_cursor + 0x43);
				g_query_count = g_query_count + 1;
				g_query_cursor = current;
			}
		} while (g_query_count < g_query_limit);
	}

	return matched_ent;
}

/* Starts a new entity query with type, filter, and range
 * parameters. Initializes the query state for iteration
 * via gm_NextEntityQueryMatch. Variadic args for filters. */
