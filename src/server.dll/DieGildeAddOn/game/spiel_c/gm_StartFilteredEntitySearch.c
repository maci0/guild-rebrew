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
extern int DAT_10035450;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* g_entity_array_ptr;
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
extern WORD* g_query_cursor;
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

extern short DAT_10030b8c;
extern short DAT_10030b8e;
extern char DAT_10030b84;
extern int DAT_10030b88;
extern char DAT_10030b90;
extern char* DAT_10035444;
extern char DAT_10035449;
extern int DAT_1003544c;
extern char DAT_10035448;
extern unsigned char* g_query_filter_base;

// FUNCTION: SERVER 0x100170e0
// gm_StartFilteredEntitySearch

unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...)
{
	int* arg_ptr;
	int i;

	if (g_entity_type_table == 0) {
		return (unsigned short*) 0;
	}

	DAT_10030b8c = 0x7fff;
	DAT_10030b8e = 0x7fff;
	DAT_10030b84 = (char) 0xff;
	DAT_10030b88 = -1;
	DAT_10030b90 = (char) 0xff;
	DAT_10035444 = 0;
	DAT_10035449 = 1;
	DAT_1003544c = 0;
	DAT_10035448 = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;

		for (i = arg_count; i > 0; i--) {
			unsigned char ftype;

			arg_ptr++;
			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				DAT_10030b84 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 1:
				DAT_10030b88 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				strcpy(DAT_10035444, *(char**) (arg_ptr + 1));
				arg_ptr++;
				break;
			case 3:
				DAT_10030b8c = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				DAT_10030b8e = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				DAT_10030b90 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 6:
				DAT_10035448 = 1;
				break;
			default:
				break;
			}
		}
	}

	g_query_filter_base = g_entity_array_ptr;
	return (unsigned short*) FindNextFilteredEntity();
}

/* Searches a structure/record table for a matching entry.
 * Linear search by comparison field. */
