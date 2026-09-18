#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"

#pragma intrinsic(memcpy, memset)

extern int g_query_limit;
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
extern unsigned char g_slot_table[];
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);

int __cdecl gm_GetBuildingTypeCategory(int);
extern int g_citizen_count;
int __cdecl gm_GetBuildingTypeCategory(int btype);
extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */
extern unsigned char g_current_season;
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x10017910
// gm_SetupEntityQuery

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char* entity)
{
	char* type_entry;
	int result;
	unsigned short* query_cursor;

	gm_GetBuildingTypeCategory((int) *entity);
	type_entry = (char*) (g_entity_type_table + (unsigned int) *entity * 0x24d);
	result = gm_CheckEntityType(entity);
	if (result != 0) {
		return (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 0, 0xfd);
	}
	if (*type_entry == 4) {
		return (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 0, 0x54);
	}
	query_cursor = (unsigned short*) gm_ff_Objekt(*(int*) (entity + 0x5d), 1, 4, 2);
	while (query_cursor != (unsigned short*) 0 && *query_cursor == 0xfd) {
		query_cursor = gm_NextEntityQueryMatch();
	}
	return query_cursor;
}

/* Returns the category of a building type. Maps a building
 * type ID to its category (production, storage, service, etc.). */

// FUNCTION: SERVER 0x100179b0
// gm_GetBuildingTypeCategory

int __cdecl gm_GetBuildingTypeCategory(int arg1)
{
	switch (*(unsigned char*) (g_entity_type_table + arg1 * 0x24d)) {
	case 0xb:
	case 0xc:
	case 0xd:
		return 2;
	case 0x13:
		return 7;
	case 4:
	case 5:
	case 9:
		return 8;
	case 8:
	case 0xe:
	case 0x12:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x1d:
	case 0x1f:
	case 0x20:
		return 1;
	case 1:
	case 3:
	case 6:
	case 0xf:
		return 3;
	case 7:
		return 4;
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
		return 5;
	case 2:
	case 0x1e:
		return 6;
	case 0x21:
		return 9;
	default:
		return 0;
	}
}

/* Searches a specific entity table (type 0x67) for a matching
 * entry. Used for specialized entity lookups. */

// FUNCTION: SERVER 0x10017A70
// gm_SearchTable67

void* __cdecl gm_SearchTable67(int id)
{
	char* query_cursor;
	int i;

	i = 0;
	query_cursor = (char*) g_entity_ptr;
	for (; i < 256; i++, query_cursor += 0xa9) {
		if (*(char*) query_cursor == 0) {
			continue;
		}
		if (*(int*) (query_cursor + 1) != id) {
			continue;
		}
		return (void*) (g_entity_ptr + i * 0xa9);
	}
	return 0;
}

/* Checks if an entity's type matches the expected class.
 * Returns non-zero if the entity type field matches. */

// FUNCTION: SERVER 0x10017AB0
// gm_CheckEntityType

int __cdecl gm_CheckEntityType(unsigned char* entity_ptr)
{
	char* type_entry;

	if (entity_ptr == NULL) {
		return 0;
	}
	type_entry = (char*) g_entity_type_table + (unsigned int) *entity_ptr * 0x24d;
	if (*type_entry == 0x0b || *type_entry == 0x0d || *type_entry == 0x0c ||
	    *type_entry == 0x10 || *type_entry == 0x1c || *type_entry == 0x1d ||
	    *type_entry == 0x1f) {
		return 1;
	}
	return 0;
}

/* Assigns a building owner. Updates the building's owner
 * field and maintains the owner-to-building linkage in
 * both directions. */

// FUNCTION: SERVER 0x10017b00
// gm_AssignBuildingOwner

#define PTR_10035A10(idx) (*(unsigned char***) (((idx) * 0x21c) + 0x10035a10))
#define BYTE_100358A2(idx) (*(unsigned char*) (((idx) * 0x21c) + 0x100358a2))
#define DWORD_100358A4(idx) (*(unsigned int*) (((idx) * 0x21c) + 0x100358a4))

void __cdecl gm_AssignBuildingOwner(unsigned char* building, unsigned short new_owner, unsigned int owner_slot)
{
	char building_class;
	unsigned short prev_owner;
	unsigned char* owner_building;
	int loop_count;
	unsigned short* obj_iter;
	char* type_entry;
	int owner_index;

	type_entry = g_entity_type_table + *building * 0x24d;
	*(unsigned short*) (building + 0x25) = new_owner;
	if (owner_slot != 0xffff) {
		prev_owner = *(unsigned short*) (building + 0x27);
		if ((prev_owner != 0xffff) && (PTR_10035A10(prev_owner) == (unsigned char**) building)) {
			PTR_10035A10(prev_owner) = 0;
		}
		*(unsigned short*) (building + 0x27) = (unsigned short) owner_slot;
		if (*type_entry == '\x02') {
			owner_building = (unsigned char*) PTR_10035A10(owner_slot & 0xffff);
			if ((owner_building == 0) || (*owner_building <= *building)) {
				PTR_10035A10(owner_slot & 0xffff) = (unsigned char**) building;
			}
		}
		owner_index = owner_slot;
		if (((BYTE_100358A2(owner_index) == '\x06') || (BYTE_100358A2(owner_index) == '\a')) &&
			(loop_count = (int) gm_FindEntityByOwner((int) building), loop_count != 0)) {
			*(unsigned char*) (loop_count + 0x165) = 0;
			*(unsigned int*) (loop_count + 0x1b4) = *(unsigned int*) (loop_count + 0x1b4) & 0xfffffffe;
			building_class = *type_entry;
			if ((building_class == '\x05') || (building_class == '\t')) {
				*(unsigned int*) (loop_count + 0x16c) = 0;
			}
		}
		loop_count = 0x5008;
		obj_iter = (unsigned short*) g_query_base;
		do {
			if (((*(unsigned short*) obj_iter != 0) &&
				 (*(g_item_def_table + *(unsigned short*) obj_iter * 0x41) == '\x1d')) &&
				(*(unsigned int*) ((unsigned char*) obj_iter + 0x1c) == *(unsigned int*) (building + 1))) {
				*(unsigned int*) ((unsigned char*) obj_iter + 0xa) = DWORD_100358A4(owner_index);
				if (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) != 0) {
					*(unsigned int*) (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) + 0xa) =
						DWORD_100358A4(owner_index);
				}
			}
			obj_iter = (unsigned short*) ((unsigned char*) obj_iter + 0x43);
			loop_count = loop_count - 1;
		} while (loop_count != 0);
	}
}

/* Allocates building contents (workers, inventory items).
 * Populates a building's slots with initial entities based
 * on the building type definition. */

