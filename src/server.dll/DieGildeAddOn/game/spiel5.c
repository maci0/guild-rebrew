#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

#pragma intrinsic(memcpy, memset)

extern int g_query_limit;
void __cdecl m_FreeTracked(void*);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern unsigned char g_slot_table[];
int __cdecl gm_FreeObjectListRecursive(char**);
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */
void __cdecl gv_Free3Fields(void* param);
extern int g_query_state_a0c[];
extern unsigned char g_byte_table_30861;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocRaum(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl gv_AllocGraveyardField(char* geb);
void __cdecl gv_SpawnEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
extern int g_citizen_count;
extern int g_dynasty_field_2c;
extern int g_dynasty_generation_counter;
extern unsigned char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
extern unsigned int g_entity_slot_table[];
extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */
extern unsigned char g_current_season;
extern float g_const_1_0;
extern float g_const_neg_1_0;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x10017210
// gm_SearchStruct

char* __cdecl gm_SearchStruct(void)
{
	char* entity_cursor;
	char* end;
	entity_cursor = (char*) g_entity_ptr;
	end = entity_cursor + 0xa900;
	while (entity_cursor < end) {
		if (*entity_cursor == 0) {
			break;
		}
		entity_cursor += 0xa9;
	}
	if (entity_cursor < end) {
		return entity_cursor;
	}
	return 0;
}

/* Cleans up a building entity. Frees all contained entities
 * (workers, inventory, production slots) and resets the
 * building to an empty state. */

// FUNCTION: SERVER 0x10017240
// gm_CleanupBuildingEntity

/* g_query_state_a0c: base of entity array, stride 0x21c (0x87 dwords), 768 entries */

int __cdecl gm_CleanupBuildingEntity(unsigned char* building)
{
	int* entity_scan;

	if (building == (unsigned char*) 0) {
		return -1;
	}
	if (*building == 0) {
		return -2;
	}
	switch (*building) {
	case 0x1e:
		if (*(void**) (building + 0x71) != (void*) 0) {
			m_FreeTracked(*(void**) (building + 0x71));
			*(int*) (building + 0x71) = 0;
		}
		*(int*) (building + 0x71) = 0;
		goto cleanup_loop;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_Free3Fields(*(void**) (building + 0x65));
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		m_FreeTracked(*(void**) (building + 0x65));
		break;
	default:
		goto cleanup_loop;
	}
	*(int*) (building + 0x65) = 0;
cleanup_loop:
	entity_scan = &g_query_state_a0c;
	do {
		if ((unsigned char*) entity_scan[1] == building) {
			entity_scan[1] = 0;
		}
		if ((unsigned char*) *entity_scan == building) {
			*entity_scan = 0;
		}
		entity_scan = entity_scan + 0x87;
	} while ((int) entity_scan < 0x1009ae0c);
	if (*(int*) (building + 0x5d) != 0) {
		gm_FreeObjectListRecursive((char**) (building + 0x5d));
	}
	*building = 0;
	return 0;
}

/* Allocates default values for a building entity. Sets up
 * initial worker capacity, production slots, and storage
 * based on building type. */

// FUNCTION: SERVER 0x10017330
// gm_AllocBuildingDefaults

void __cdecl gm_AllocBuildingDefaults(unsigned char* building)
{
	void* query_result;
	int inner_count;
	unsigned short* item_ptr;
	unsigned char* table_ptr;

	table_ptr = &g_byte_table_30861;
	do {
		if (*building == *(table_ptr - 1)) {
			query_result = gm_ff_Objekt(*(int*) (building + 0x5d), 2, 6, 0, 0xff);
			if (query_result != (void*) 0) {
				goto do_inner;
			}
			query_result = gm_AllocObjekt(*(int*) (building + 1), 0xff, 1);
			if (query_result != (void*) 0) {
			do_inner:
				inner_count = 10;
				item_ptr = (unsigned short*) table_ptr;
				do {
					if (*item_ptr != 0 &&
						gm_ff_Objekt(*(int*) ((int) query_result + 0x14), 1, 0, (unsigned int) *item_ptr) ==
							(void*) 0) {
						gm_AllocObjekt(*(int*) ((int) query_result + 2), (unsigned int) *item_ptr, 2);
					}
					item_ptr = item_ptr + 1;
					inner_count = inner_count - 1;
				} while (inner_count != 0);
			}
			else {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0x107f,
					"gm_AllocGebaeude(): Missing potential....",
					1
				);
			}
		}
		table_ptr = table_ptr + 0x15;
	} while ((int) table_ptr < 0x10030b6a);
}

/* Sets worker limits for a building based on its type and
 * upgrade level. Reads from the building type table. */

// FUNCTION: SERVER 0x10017400
// gm_SetBuildingWorkerLimits

void __cdecl gm_SetBuildingWorkerLimits(unsigned char* building)
{
	unsigned char* entry;
	unsigned char* query_result;
	int type;

	type = building[0];
	entry = (unsigned char*) (g_entity_type_table + type + type * 588);
	query_result = (unsigned char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 0, 0x2a, 6);
	if (query_result != 0) {
		if (entry[0x23d] == 0 && entry[0x23e] == 0 && entry[0x23f] != 0) {
			query_result[0x1c] = entry[0x23f];
		} else {
			query_result[0x1c] = (unsigned char) (entry[0x23d] < 2 ? 2 : entry[0x23d]);
			query_result[0x1d] = (unsigned char) (entry[0x23e] < 2 ? 2 : entry[0x23e]);
		}
	}
	query_result = (unsigned char*) gm_ff_Objekt(*(int*) (building + 0x5d), 2, 0, 0x116, 6);
	if (query_result != 0) {
		if (entry[0x23d] == 0 && entry[0x23e] == 0 && entry[0x23f] != 0) {
			query_result[0x1c] = entry[0x23f];
		}
	}
}

/* Allocates a new building (Gebaeude) entity. Creates the
 * building struct, sets type, initializes production and
 * storage, and links to the town. */

// DATA: SERVER 0x10035884
// DATA: SERVER 0x10035888
// DATA: SERVER 0x1003588c

#if 0 /* split to spiel_c/gm_AllocGebaeude.c */
char* __cdecl gm_AllocGebaeude(int building_type, int location_id)
{
	char buf[0x400];
	char* pDest;
	unsigned int gebType;
	int base;
	int has_producer;
	char* geb;
	int temp_result;
	short owner_id;

	if (g_entity_type_table == 0) {
		return 0;
	}
	has_producer = 0;
	geb = gm_SearchStruct();
	if (geb == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x10cb,
			"gm_AllocGebaeude(): geb overflow HELP !!!!!!",
			1
		);
		return 0;
	}
	gebType = building_type & 0xff;
	*geb = (char) building_type;
	base = temp_result + gebType * 0x24d;

	sprintf(buf, "----->GebID= %i GebProt= %i", g_next_object_id, gebType);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10d8, buf, 8);

	*(int*) (geb + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	owner_id = (short) location_id;
	*(short*) (geb + 0x25) = owner_id;
	*(short*) (geb + 0x27) = owner_id;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	{
		int* state_ptr = (int*) (geb + 0x99);
		*(short*) (geb + 0x29) = 0;
		*(int*) (geb + 0x2b) = 0;
		geb[0x2f] = 0;
		*(int*) (geb + 0x5d) = 0;
		*(int*) (geb + 0x61) = 0;
		*(int*) (geb + 0x30) = 0;
		*(int*) (geb + 0x39) = 0x7d00;
		*(int*) (geb + 0x41) = 2;
		*(int*) (geb + 0x49) = 0x3f800000;
		*(int*) (geb + 0x95) = -1;
		*state_ptr = 0;
		*(int*) (geb + 0x9d) = 0;
		*(int*) (geb + 0xa1) = 0;
		*(int*) (geb + 0xa5) = -1;
		*state_ptr = *state_ptr | 1;
	}
	pDest = geb + 0x65;
	memset(pDest, 0, 0x30);
	{
		unsigned short* comp_iter = (unsigned short*) (base + 0x23);
		for (building_type = 0; building_type < 0x40; building_type++) {
			unsigned short comp_entry = *comp_iter;
			if (comp_entry == 0) {
				break;
			}
			if (comp_entry != 0xffff) {
				unsigned int item_index = comp_entry & 0x7fff;
				char item_class = *(char*) (g_item_def_table + item_index * 0x41);
				if (item_class == '\x02' || item_class == '\x06') {
					has_producer = 1;
				}
				if ((comp_entry & 0x8000) != 0) {
					if (item_class == '\x02' || item_class == '\x06') {
						has_producer = 1;
						gm_AllocRaum(geb, item_index);
					}
					else if (has_producer == 0) {
						gm_AllocObjekt(*(int*) (geb + 1), item_index, 1);
					}
				}
			}
			comp_iter = comp_iter + 1;
		}
	}
	{
		short* product_iter = (short*) gm_ff_Objekt(*(int*) (geb + 0x5d), 1, 4, 2);
		while (product_iter != 0) {
			if (*product_iter != 0xfd) {
				*(short*) (geb + 0x29) = *product_iter;
				break;
			}
			product_iter = gm_NextEntityQueryMatch();
		}
	}
	{
		unsigned short* setup_result = gm_SetupEntityQuery(geb);
		if (setup_result != 0) {
			*(short*) (geb + 0x29) = *(short*) setup_result;
		}
	}
	temp_result = gm_CheckEntityType(geb);
	if (temp_result != 0) {
		*(int*) (geb + 0x30) = 0x1388;
	}
	if (gebType - 4 < 0x4a) {
		switch (gebType) {
		case 4:
		case 5:
		case 6:
		case 7:
			*(int*) (geb + 0x69) = g_current_year;
			*(int*) (geb + 0x6d) = g_current_hour;
			*(int*) (geb + 0x71) = g_clock_copy_mid;
			*(short*) (geb + 0x75) = g_clock_copy_tail;
			if (owner_id != -1) {
				*(int*) (geb + 0x65) = *(int*) ((unsigned short) location_id * 0x21c + 0x100358a4);
				break;
			}
			/* fall through */
		case 11:
		case 12:
		case 13:
			*(int*) (geb + 0x65) = -1;
			break;
		case 14:
		case 15:
		case 16:
			*(int*) (geb + 0x65) = 10;
			*(int*) (geb + 0x69) = 3;
			*(int*) (geb + 0x6d) = 5;
			break;
		case 20:
		case 21:
		case 22:
			temp_result = (int) gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
			if (temp_result != 0) {
				*(char*) (temp_result + 0x22) = 0;
				*(char*) (temp_result + 0x1c) = (char) 0xff;
				*(char*) (temp_result + 0x1d) = (char) 0xff;
				*(int*) (temp_result + 0x1e) = -1;
			}
			break;
		case 30: {
			unsigned int plant_map;
			plant_map = (unsigned int) m_AllocTracked(0x600, "f3_gm:PlantMap");
			*(unsigned int*) (geb + 0x71) = plant_map;
			temp_result = 0;
			do {
				temp_result = temp_result + 0x18;
				*(char*) (temp_result + 0xd + *(int*) (geb + 0x71)) = (char) 0xff;
				*(int*) (temp_result + 0x14 + *(int*) (geb + 0x71)) = 0;
			} while (temp_result < 0x600);
		}
			/* fall through */
		case 31:
		case 32:
			*(int*) (geb + 0x30) = 100;
			*(int*) (geb + 0x49) = 0x3f4ccccd;
			break;
		case 53:
		case 54:
		case 55:
			*(int*) (geb + 0x65) = 0;
			*(short*) (geb + 0x69) = 0;
			*(short*) (geb + 0x6b) = 0;
			*(int*) (geb + 0x6d) = 0;
			break;
		case 71:
			*(int*) (geb + 0x30) = 0x13880;
			break;
		case 72:
		case 73:
		case 74:
			temp_result = gv_AllocGraveyardField(geb);
			*(int*) (geb + 0x65) = temp_result;
			gv_SpawnEntities(geb, 3);
			break;
		case 75:
		case 76:
		case 77: {
			int* ahm_block = (int*) m_AllocTracked(0x3c, "AHM_INFO");
			*(int*) (geb + 0x65) = (int) ahm_block;
			*ahm_block = -1;
			break;
		}
		default:
			break;
		}
	}
	if (*geb == 0x26) {
		*(short*) (geb + 0x29) = 0x10e;
	}
	gm_SetBuildingWorkerLimits(geb);
	gm_GetBuildingTypeCategory(*(unsigned char*) geb);
	gm_AllocBuildingDefaults(geb);
	return geb;
}
#endif

/* Sets up an entity query with specific parameters. Configures
 * the query state machine for iterating filtered results. */

