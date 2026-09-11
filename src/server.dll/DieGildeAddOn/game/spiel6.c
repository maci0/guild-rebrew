#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
int __cdecl _ftol(void);

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

void __cdecl gm_InitEntitySlots(void);
extern int g_query_limit;
void __cdecl m_FreeTracked(void*);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern char* g_array_base;
extern unsigned char g_slot_table[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */
extern char s_gm_AddObjekt____obj____ob_NULL_10031390[];
extern char s_gm_AddObjekt____Parent_not_found_10031358[];
extern unsigned char* g_EntityListStart;
extern unsigned char* g_EntitySearchPtr;
extern int g_SearchCount;
extern unsigned char g_SearchFlag;
extern void* g_SomeGlobal;
extern unsigned char g_FilterActive;
extern unsigned char g_FilterType;
extern int g_FilterId;
extern unsigned short g_FilterVal25;
extern unsigned short g_FilterVal27;
extern unsigned char g_FilterVal30;
void __cdecl gv_Free3Fields(void* param);
extern int g_query_state_a0c[];
extern unsigned char g_byte_table_30861;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocBuildingContents(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl gv_AllocField(char* geb);
void __cdecl gv_SpawnEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int g_citizen_count;
extern int g_dynasty_field_2c;
extern int g_dynasty_generation_counter;
extern unsigned char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
int __cdecl gm_MapEntityStatRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_RandomMod(unsigned short range);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
extern unsigned int g_entity_slot_table[];
extern float g_const_1_5; /* 0x10025fb4 */
extern float g_const_2_2; /* 0x10025fb0 */
extern float g_const_0_06875; /* 0x10025fac */
extern float g_const_896_0; /* 0x10025fa8 */
extern double g_const_1_over_720; /* 0x10025fa0 */
extern float g_const_0_0; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_half; /* 0x100257d0 */
double __cdecl gm_CalculateProductionValue(int, int);
extern unsigned char g_current_season;
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); /* 0x10019d00 */
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */
int __cdecl gm_GetMsgField(char*, char*); /* 0x10019cd0 */
int __cdecl ahm_LookupEntityInTable(int); /* 0x1000c670 */
double __cdecl gm_RandomFloat01(void);
extern float g_const_1_0;
extern float g_const_neg_1_0;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x10017910
// gm_SetupEntityQuery

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char* entity)
{
	char* type_entry;
	int result;
	unsigned short* p;

	gm_GetBuildingTypeCategory((int) *entity);
	type_entry = (char*) (g_entity_type_table + (unsigned int) *entity * 0x24d);
	result = gm_CheckEntityType(entity);
	if (result != 0) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0xfd);
	}
	if (*type_entry == 4) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0x54);
	}
	p = (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 4, 2);
	while (p != (unsigned short*) 0 && *p == 0xfd) {
		p = gm_NextEntityQueryMatch();
	}
	return p;
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
	char* p;
	int i;

	i = 0;
	p = (char*) g_entity_ptr;
	for (; i < 256; i++, p += 0xa9) {
		if (*(char*) p == 0) {
			continue;
		}
		if (*(int*) (p + 1) != id) {
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

