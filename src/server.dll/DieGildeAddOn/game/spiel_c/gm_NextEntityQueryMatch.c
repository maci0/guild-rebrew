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
extern char* g_entity_ptr;
void __cdecl vfs_EntityCleanup(char*);
extern unsigned short* DAT_100a8c34;
extern int DAT_10035450;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* DAT_1014d8c0;
extern int DAT_100a8c30;
extern unsigned char DAT_10035439;
extern int DAT_1003543c;
extern char* DAT_101de450;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern WORD* DAT_10035468;
extern char DAT_10035454;
extern char DAT_1003545d;
extern int DAT_10035458;
extern int DAT_10030b94;
extern int DAT_10030b98;
extern short DAT_10030b9c;
extern char DAT_10030b9e;
extern char DAT_1003545c;
extern char DAT_1003545e;
extern int DAT_100a8c38;
extern int* DAT_101398a0;
extern int* DAT_1013989c;
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

	current = DAT_10035468;
	matched_ent = (unsigned short*) 0x0;
	is_match = 0;

	if (DAT_10035468 == (WORD*) 0x0) {
		return (void*) 0x0;
	}

	if ((DAT_10035454 != '\0') && (DAT_10035454 = '\0', DAT_1003545d != '\0') &&
		(*(int*) ((int) DAT_10035468 + 10) != 0)) {
		*(int*) (&DAT_101398a0 + DAT_100a8c38 * 4) = *(int*) (DAT_10035468 + 10);
		DAT_100a8c38 = DAT_100a8c38 + 1;
	}

	stack_depth = DAT_100a8c38;
	filter_type_cache = DAT_10030b9c;

	if (DAT_10035458 < DAT_10035450) {
		do {
			if (current == (WORD*) 0x0) {
				return matched_ent;
			}
			if (is_match) {
				return matched_ent;
			}
			entry_val = *current;
			candidate_ptr = current;
			scan_ptr = DAT_10035468;

			while (DAT_10035468 = candidate_ptr, entry_val == 0) {
				scan_ptr = (unsigned short*) ((int) DAT_10035468 + 0x43);
				entry_val = *scan_ptr;
				candidate_ptr = scan_ptr;
			}

			if (DAT_1003545e != '\0') {
				is_match = 1;
			}

			if (DAT_10030b94 == 0x7fff) {
				if (DAT_10030b98 != -1) {
					if (*(int*) (DAT_10035468 + 1) != DAT_10030b98) {
						goto LAB_10016382;
					}
					is_match = 1;
				}
				if (filter_type_cache != -1) {
					candidate_ptr = DAT_10035468;
					DAT_10035468 = scan_ptr;
					entity_type_result = gm_GetEntityType(candidate_ptr);
					stack_depth = DAT_100a8c38;
					filter_type_cache = DAT_10030b9c;
					if (entity_type_result != DAT_10030b9c) {
						is_match = 0;
						goto LAB_100163bc;
					}
					is_match = 1;
				}
				if (DAT_10030b9e != -1) {
					is_match = *(char*) (g_game_initialized + (unsigned int) *DAT_10035468 * 0x41) == DAT_10030b9e;
				}
			}
			else {
				if (*DAT_10035468 == DAT_10030b94) {
					is_match = 1;
					goto check_filters;
				}
			LAB_10016382:
				is_match = 0;
			}
		LAB_100163bc:
		check_filters:
			if (DAT_1003545c == '\0') {
				if (is_match) {
					matched_ent = DAT_10035468;
				}
				current = *(unsigned short**) ((int) DAT_10035468 + 0x3f);
				DAT_10035468 = current;
				if (current == (WORD*) 0x0) {
					if ((DAT_1003545d != '\0') && (stack_depth != 0)) {
						current = *(unsigned short**) (&DAT_1013989c + stack_depth * 4);
						stack_depth = stack_depth - 1;
						DAT_10035468 = current;
						DAT_100a8c38 = stack_depth;
						if (*(int*) (current + 10) != 0) {
							*(int*) (&DAT_101398a0 + stack_depth * 4) = *(int*) (current + 10);
							goto LAB_1001643e;
						}
					}
				}
				else if ((*(int*) (current + 10) != 0) && (DAT_1003545d != '\0')) {
					*(int*) (&DAT_101398a0 + stack_depth * 4) = *(int*) (current + 10);
				LAB_1001643e:
					stack_depth = stack_depth + 1;
					DAT_100a8c38 = stack_depth;
				}
			}
			else {
				if (is_match) {
					matched_ent = DAT_10035468;
				}
				current = (unsigned short*) ((int) DAT_10035468 + 0x43);
				DAT_10035458 = DAT_10035458 + 1;
				DAT_10035468 = current;
			}
		} while (DAT_10035458 < DAT_10035450);
	}

	return matched_ent;
}

/* Starts a new entity query with type, filter, and range
 * parameters. Initializes the query state for iteration
 * via gm_NextEntityQueryMatch. Variadic args for filters. */
