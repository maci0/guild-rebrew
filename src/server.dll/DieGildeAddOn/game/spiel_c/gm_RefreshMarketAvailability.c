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

// STUB: SERVER 0x10015f70
// gm_RefreshMarketAvailability

void __cdecl gm_RefreshMarketAvailability(int season)
{
	int base;
	int resource_types[8];

	resource_types[0] = 0x92;
	resource_types[1] = 0x93;
	resource_types[2] = 0x94;
	resource_types[3] = 0x95;
	resource_types[4] = 0x96;
	resource_types[5] = 0x97;
	resource_types[6] = 0x2db;
	resource_types[7] = 0;

	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 10);
	if (g_active_player_count == 0) {
		LogMessageInternal((char*) 0x10031004, 0x7cf, (char*) 0x1003122c, 1);
		return;
	}

	{
		int ecx;
		int eax;
		ecx = season;
		eax = ecx;
		eax = eax << 4;
		eax = eax + ecx;
		eax = eax + eax * 4;
		base = ecx + eax * 8;
		base = base << 4;
		base = base + 0x1009b770;
	}

	if (season != g_current_season) {
		return;
	}

	/* Clear offset 4 of each of 0x55 slots (stride 0x80) */
	{
		int ptr;
		int cnt;
		ptr = base + 4;
		cnt = 0x55;
		do {
			*(int*) ptr = 0;
			ptr += 0x80;
			cnt--;
		} while (cnt != 0);
	}

	/* First major loop: iterate filtered entities */
	{
		int entity_ptr;
		entity_ptr = (int) gm_StartFilteredEntitySearch(1, 6);
		if (entity_ptr != 0) {
			do {
				int byteVal;
				int edi;
				int ecx2;
				byteVal = *(unsigned char*) entity_ptr;
				edi = g_entity_type_table;
				edi += byteVal;
				ecx2 = byteVal + byteVal * 2;
				ecx2 = ecx2 << 4;
				ecx2 = ecx2 + byteVal;
				ecx2 = ecx2 + ecx2 * 2;
				if (*(char*) (edi + ecx2 * 4) != '\n') {
					int query_result;
					query_result = (int) gm_StartEntityQuery(*(int*) (entity_ptr + 0x5d), 1, 0, 0xff);
					season = 0;
					if (query_result != 0) {
						int pSlot;
						pSlot = base;
						while (season < 0x55) {
							if (*(short*) pSlot != 0) {
								int inner_query;
								inner_query = (int)
									gm_StartEntityQuery(*(int*) (query_result + 0x14), 1, 0, *(short*) pSlot & 0xffff);
								if (inner_query != 0) {
									int rowId;
									int edx2;
									int pOuter;
									int pInner;
									int outerCount;
									int pInnerCount;
									*(int*) (pSlot + 4) = 1;
									rowId = *(short*) pSlot & 0xffff;
									edx2 = *(int*) g_item_def_table;
									edx2 = edx2 + (rowId << 6);
									edx2 = edx2 + rowId;
									pOuter = base;
									outerCount = 0x55;
									do {
										pInner = edx2 + 0x2e;
										pInnerCount = 4;
										do {
											if (*(short*) pOuter == *(short*) pInner) {
												*(int*) (pOuter + 4) = 1;
											}
											pInner += 2;
											pInnerCount--;
										} while (pInnerCount != 0);
										pOuter += 0x80;
										outerCount--;
									} while (outerCount != 0);
								}
							}
							season++;
							pSlot += 0x80;
						}
					}
				}
				entity_ptr = (int) FindNextFilteredEntity();
			} while (entity_ptr != 0);
		}
	}

	/* Second major loop: 0x55 iterations over base array */
	{
		int query_result;
		int esi;
		query_result = 0x55;
		esi = base;
		do {
			int inner_query;
			int outer_query;
			int edi;
			inner_query = g_active_player_count;
			{
				int ax;
				ax = *(short*) (esi + 0x3c) & 0xffff;
				outer_query = (int) gm_StartEntityQuery(*(int*) (inner_query + 0x5d), 1, 0, ax);
				if (outer_query != 0) {
					edi = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 0, 0xff);
					if (*(int*) (esi + 4) != 0) {
						int edx;
						int cx;
						edx = *(int*) (edi + 0x14);
						cx = *(short*) esi & 0xffff;
						inner_query = (int) gm_StartEntityQuery(edx, 1, 0, cx);
						if (inner_query == 0) {
							gm_AllocObjekt(*(int*) (edi + 2), *(short*) esi & 0xffff, 1);
						}
					}
				}
			}
			esi += 0x80;
			query_result--;
		} while (query_result != 0);
	}

	/* Third loop: iterate over resource_types array */
	{
		int resource_id;
		int* pArr;
		resource_id = 0x92;
		pArr = &resource_types[0];
		do {
			int inner_query;
			int outer_query;
			int count_query;
			int uCount;
			uCount = 0;
			outer_query = (int) gm_StartEntityQuery(*(int*) (g_active_player_count + 0x5d), 1, 0, resource_id);
			if (outer_query != 0) {
				inner_query = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 0, 0xff);
				if (inner_query != 0) {
					count_query = (int) gm_StartEntityQuery(*(int*) (inner_query + 0x14), 1, 5);
					while (count_query != 0) {
						uCount++;
						count_query = (int) gm_NextEntityQueryMatch();
					}
					count_query = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 4, 0x11);
					if (count_query != 0) {
						if ((*(unsigned char*) (count_query + 0x1c) & 0xff) != uCount) {
							*(unsigned char*) (count_query + 0x1c) = (unsigned char) uCount;
						}
					}
				}
			}
			pArr = pArr + 1;
			resource_id = *pArr;
		} while (resource_id != 0);
	}
}

/* Finds a slot by ID in the entity slot table. Returns
 * the slot pointer or NULL if not found. */
