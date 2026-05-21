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

extern int g_1014d8c0;
extern int g_100a8c34;
extern int g_100a8cf8;
extern int g_1009b764;
extern int g_1002dde0;

// FUNCTION: SERVER 0x10015950
// gm_Open

int __cdecl gm_Open(int map_id)
{
	unsigned int* src_player_ptr;
	unsigned int* dst_player_ptr;
	unsigned int player_field;
	FILE* file_handle;
	int next_offset;
	unsigned short slot_entry;
	char item_category;
	int producible_count;
	unsigned short* slot_ptr;
	int slot_counter;
	unsigned char path_buf[512];
	int table_offset;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "gm_Open(): enter", 1);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "gm_Open(): Spieler initialisieren", 1);
	src_player_ptr = (unsigned int*) &g_100a8cf8;
	dst_player_ptr = (unsigned int*) &g_1009b764;
	do {
		dst_player_ptr[-1] = src_player_ptr[-0x14];
		player_field = *src_player_ptr;
		dst_player_ptr[0] = 1000;
		dst_player_ptr[1] = player_field;
		dst_player_ptr[2] = 1000;
		memcpy((void*) &dst_player_ptr[3], (void*) &g_1002dde0, 0x2a80);
		src_player_ptr = src_player_ptr + 0xbd;
		dst_player_ptr = dst_player_ptr + 0xaa4;
	} while ((unsigned int) src_player_ptr < 0x100a9bbc);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "gm_Open(): Gebaeude-Daten", 1);
	g_entity_type_table = (int) m_AllocTracked(0xca78, (const char*) 0x100311d8);
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_1014d8c0 = (int) m_AllocTracked(0xa900, (const char*) 0x100311a0);
	memset((void*) g_1014d8c0, 0, 0xa900);
	if (g_1014d8c0 == 0) {
		return -2;
	}
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031194);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, (char*) 0x10031154, 1);
		return -3;
	}
	fread((void*) g_entity_type_table, 0x24d, 0x58, file_handle);
	fflush(file_handle);
	g_item_def_table = (int) m_AllocTracked(0xb9dc, (const char*) 0x10031140);
	if (g_item_def_table == 0) {
		return -4;
	}
	g_100a8c34 = (int) m_AllocTracked(0x14f218, (const char*) 0x1003112c);
	if (g_100a8c34 == 0) {
		return -5;
	}
	memset((void*) g_100a8c34, 0, 0x14f218);
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031120);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	fread((void*) g_item_def_table, 0x41, 0x2dc, file_handle);
	fflush(file_handle);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "gm_Open(): gm_InitObjektHersteller", 1);
	gm_InitObjektHersteller();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "gm_Open(): gm_KillAllSpieler", 1);
	gm_InitEntitySlots();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"gm_Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	table_offset = 0;
	do {
		producible_count = 0;
		slot_counter = 0x40;
		slot_ptr = (unsigned short*) (table_offset + 0x23 + g_entity_type_table);
		do {
			slot_entry = *slot_ptr;
			if (slot_entry != 0xffff) {
				item_category = *(char*) (g_item_def_table + (slot_entry & 0x7fff) * 0x41);
				if (((item_category == '\x02') || (item_category == '\x06')) && ((slot_entry & 0x7fff) != 0xfd) &&
					((slot_entry & 0x8000) != 0)) {
					producible_count = producible_count + 1;
				}
			}
			slot_ptr = slot_ptr + 1;
			slot_counter = slot_counter + -1;
		} while (slot_counter != 0);
		next_offset = table_offset + 0x24d;
		*(char*) (table_offset + 0x21 + g_entity_type_table) =
			*(char*) (table_offset + 0x21 + g_entity_type_table) + producible_count;
		table_offset = next_offset;
	} while (next_offset < 0xca78);
	_getpid();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "gm_Open(): exit", 1);
	return 0;
}

/* Resets all entities to initial state. Walks the entity
 * tables and clears all active entities without deallocation. */
