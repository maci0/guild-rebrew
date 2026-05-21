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

// STUB: SERVER 0x10016460
// gm_StartEntityQuery

unsigned short* __cdecl gm_StartEntityQuery(int container_id, int arg_count, int first_arg, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (g_item_def_table == 0) {
		return (unsigned short*) 0;
	}

	flag1 = 0;
	flag2 = 0;

	g_query_filter_max_id = 0x7fff;
	g_query_filter_owner = -1;
	g_query_filter_type = (short) 0xffff;
	g_query_filter_state = (char) 0xff;
	g_query_flag3 = 0;
	g_query_flag1 = flag1;
	g_query_flag2 = flag2;
	g_query_active = 1;
	g_query_count = 0;
	g_query_match_count = 0;

	if (arg_count > 0) {
		arg_ptr = &first_arg;

		for (i = arg_count; i > 0; i--) {
			unsigned char ftype;

			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				arg_ptr++;
				g_query_filter_max_id = *(unsigned short*) arg_ptr;
				break;
			case 1:
				g_query_filter_owner = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				g_query_filter_type = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 3:
				g_query_filter_state = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_flag3 = 1;
				break;
			case 5:
				flag2 = 1;
				break;
			case 6:
				flag1 = 1;
				break;
			case 7:
				break;
			}
		}

		g_query_flag1 = flag1;
		g_query_flag2 = flag2;

		if (flag1 == 0) {
			goto check_container;
		}

		if (flag2 != 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\objekte", 0xb66, "query flags conflict", 1);
			return (unsigned short*) 0;
		}

		g_query_cursor = g_query_base;
		return gm_NextEntityQueryMatch();
	}

check_container:
	if (container_id != 0) {
		g_query_cursor = g_query_base;
		return gm_NextEntityQueryMatch();
	}

	return (unsigned short*) 0;
}

/* Allocates an object slot in an entity's inventory.
 * Finds the next free slot and returns its index. */
