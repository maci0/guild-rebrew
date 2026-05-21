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
extern int g_next_object_id;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocBuildingContents(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl AllocGraveyardField(char*);
int __cdecl SpawnGraveyardEntities(unsigned char*, int);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char*);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char*);

// STUB: SERVER 0x100174d0
// gm_AllocGebaeude

int __cdecl gm_AllocGebaeude(int building_type, int location_id)
{
	char path_buf[0x408];
	int has_producer;
	char* slot;
	int btype;
	char* info_record;
	int counter;
	int i;
	short item;
	unsigned short* qres;

	if (g_entity_type_table == 0) {
		return 0;
	}

	has_producer = 0;
	slot = gm_SearchStruct();
	if (slot == 0) {
		LogMessageInternal((char*) 0x10031004, 0x10cb, (char*) 0x10031454, 1);
		return 0;
	}

	*slot = (char) building_type;
	btype = building_type & 0xff;
	info_record = (char*) (g_entity_type_table + btype + btype * 0x24c);

	counter = g_next_object_id;
	sprintf(path_buf, (char*) 0x10031438, btype, counter);
	LogMessageInternal((char*) 0x10031004, 0x10d8, path_buf, 8);

	*(int*) (slot + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	*(short*) (slot + 0x25) = (short) location_id;
	*(short*) (slot + 0x27) = (short) location_id;
	*(int*) (slot + 0x3d) = 0x64;
	*(int*) (slot + 0x45) = 0x64;
	*(char*) (slot + 0x5c) = 0;

	*(short*) (slot + 0x29) = 0;
	*(int*) (slot + 0x2b) = 0;
	*(char*) (slot + 0x2f) = 0;
	*(int*) (slot + 0x5d) = 0;
	*(int*) (slot + 0x61) = 0;
	*(int*) (slot + 0x30) = 0;
	*(int*) (slot + 0x39) = 0x7d00;
	*(int*) (slot + 0x41) = 2;
	*(int*) (slot + 0x49) = 0x3f800000;
	*(int*) (slot + 0x95) = -1;
	*(int*) (slot + 0x99) = 0;
	*(int*) (slot + 0x9d) = 0;
	*(int*) (slot + 0xa1) = 0;
	*(int*) (slot + 0xa5) = 0;
	*(int*) (slot + 0xa5) = -1;
	*(int*) (slot + 0x99) = *(int*) (slot + 0x99) | 1;

	memset(slot + 0x65, 0, 0x30);

	for (i = 0; i < 0x40; i = i + 1) {
		char category;
		int item_type;

		item = *(short*) (info_record + 0x23 + i * 2);
		if (item == 0) {
			goto done_loop;
		}
		if ((unsigned short) item == 0xffff) {
			continue;
		}

		item_type = (int) (unsigned short) item & 0x7fff;
		category = *(g_item_def_table + item_type * 0x41);

		if (category == 2 || category == 6) {
			has_producer = 1;
		}

		if (((unsigned short) item & 0x8000) != 0) {
			if (category == 2 || category == 6) {
				has_producer = 1;
				gm_AllocBuildingContents(slot, item_type);
			}
			else if (has_producer != 0) {
				gm_AllocObjekt(*(int*) (slot + 1), item_type, 1);
			}
		}
	}
done_loop:

	qres = gm_StartEntityQuery((int) (unsigned short) *(short*) (slot + 0x5d), 1, 4, 2);
	while (qres != 0) {
		if (*qres != 0xfd) {
			*(short*) (slot + 0x29) = (short) *qres;
			break;
		}
		qres = (unsigned short*) gm_NextEntityQueryMatch();
	}

	qres = gm_SetupEntityQuery((unsigned char*) slot);
	if (qres != 0) {
		*(short*) (slot + 0x29) = (short) *qres;
	}

	if (gm_CheckEntityType((unsigned char*) slot) != 0) {
		*(int*) (slot + 0x30) = 0x1388;
	}

	{
		int dispatch_in = btype - 4;
		if ((unsigned int) dispatch_in <= 0x49) {
			static const unsigned char btype_dispatch_map[0x4a] = {
				0x00, 0x00, 0x00, 0x00, 0x0a, 0x0a, 0x0a, 0x01, 0x01, 0x01,
				0x02, 0x02, 0x02, 0x0a, 0x0a, 0x03, 0x03, 0x0a, 0x0a, 0x0a,
				0x04, 0x05, 0x05, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
				0x0a, 0x0a, 0x0a, 0x0a, 0x06, 0x06, 0x06, 0x0a, 0x0a, 0x0a,
				0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
				0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
				0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x07, 0x08,
				0x08, 0x09, 0x09, 0x09
			};
			switch (btype_dispatch_map[dispatch_in]) {
			case 0: {
				int loc_idx;
				*(int*) (slot + 0x69) = *(int*) 0x10035880;
				*(int*) (slot + 0x6d) = *(int*) 0x10035884;
				*(int*) (slot + 0x71) = *(int*) 0x10035888;
				*(short*) (slot + 0x75) = *(short*) 0x1003588c;
				loc_idx = location_id & 0xffff;
				if (loc_idx != 0xffff) {
					*(int*) (slot + 0x65) = *(int*) (0x100358a4 + loc_idx * 0x21c);
				}
				break;
			}
			case 1:
				*(int*) (slot + 0x65) = -1;
				break;
			case 2:
				*(int*) (slot + 0x65) = 0xa;
				*(int*) (slot + 0x69) = 3;
				*(int*) (slot + 0x6d) = 5;
				break;
			case 3: {
				char* obj = gm_AllocObjekt(*(int*) (slot + 1), 0x1b5, 1);
				if (obj != 0) {
					*(char*) (obj + 0x22) = 0;
					*(char*) (obj + 0x1c) = (char) -1;
					*(char*) (obj + 0x1d) = (char) -1;
					*(int*) (obj + 0x1e) = -1;
				}
				break;
			}
			case 4: {
				int* buf;
				int off;
				buf = (int*) m_AllocTracked(0x600, (char*) 0x10031428);
				*(int*) (slot + 0x71) = (int) buf;
				off = 0x18;
				while (off < 0x600) {
					*(char*) ((char*) *(int*) (slot + 0x71) + off - 0xb) = (char) 0xff;
					*(int*) ((char*) *(int*) (slot + 0x71) + off - 4) = 0;
					off = off + 0x18;
				}
				*(int*) (slot + 0x30) = 0x64;
				*(int*) (slot + 0x49) = 0x3f4ccccd;
				break;
			}
			case 5:
				*(int*) (slot + 0x30) = 0x64;
				*(int*) (slot + 0x49) = 0x3f4ccccd;
				break;
			case 6:
				*(int*) (slot + 0x65) = 0;
				*(short*) (slot + 0x69) = 0;
				*(short*) (slot + 0x6b) = 0;
				*(int*) (slot + 0x6d) = 0;
				break;
			case 7:
				*(int*) (slot + 0x30) = 0x13880;
				break;
			case 8: {
				int* gv;
				*(int*) (slot + 0x65) = AllocGraveyardField(slot);
				SpawnGraveyardEntities((unsigned char*) slot, 3);
				(void) gv;
				break;
			}
			case 9: {
				int* p = (int*) m_AllocTracked(0x3c, (char*) 0x1002d504);
				*(int*) (slot + 0x65) = (int) p;
				*p = -1;
				break;
			}
			default:
				break;
			}
		}
	}

	if (*slot == 0x26) {
		*(short*) (slot + 0x29) = 0x10e;
	}
	gm_SetBuildingWorkerLimits((unsigned char*) slot);
	gm_GetBuildingTypeCategory((int) (unsigned char) *slot);
	gm_AllocBuildingDefaults((unsigned char*) slot);

	return (int) slot;
}
