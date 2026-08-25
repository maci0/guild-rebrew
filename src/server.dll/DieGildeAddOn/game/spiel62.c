#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

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
void __cdecl gm_InitEntitySlots(void);
unsigned short* g_query_base;
extern int g_query_limit;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern unsigned char* g_entity_ptr;
int g_entity_type_table;
extern char* g_item_def_table;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern char* g_array_base;
extern char g_entity_array[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
int g_next_object_id = 1;
int g_current_year;
char s_D__Develop_DieGildeAddOn_game_sp_10031004[] = "D:\\Develop\\DieGildeAddOn\\game\\spiel.c";
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
extern char* g_array;
void __cdecl gv_Free3Fields(void* param);
extern int g_query_state_a0c;
extern unsigned char g_byte_table_30861;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocBuildingContents(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl AllocGraveyardField(char* geb);
void __cdecl SpawnGraveyardEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
extern char* g_table_a9;
extern char* dword_100a8c30;
extern unsigned short* dword_100a8c34;
extern char* dword_101de450;
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int g_citizen_count;
extern int g_dynasty_field_2c;
extern int g_dynasty_generation_counter;
extern char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
int __cdecl gm_MapEntityStatRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
extern float g_const_57bc;
int __cdecl gm_RandomMod(unsigned short range);
extern char entity_table[];
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
extern char entity_slot_table[];
extern float g_const_5fb8; /* 0x10025fb8 */
extern float g_const_5fb4; /* 0x10025fb4 */
extern float g_const_5fb0; /* 0x10025fb0 */
extern float g_const_5fac; /* 0x10025fac */
extern float g_const_5fa8; /* 0x10025fa8 */
extern double g_const_5fa0; /* 0x10025fa0 */
extern float g_float_const_cc; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_57d0; /* 0x100257d0 */
double __cdecl gm_CalculateProductionValue(int, int);
extern char g_type_idx;
extern int g_key_table[];
extern char entity_array[];
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); /* 0x10019d00 */
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */
int __cdecl gm_GetMsgField(char*, char*); /* 0x10019cd0 */
int __cdecl ahm_LookupEntityInTable(int); /* 0x1000c670 */
extern float g_const_5fbc;
double __cdecl gm_RandomFloat01(void);
extern float g_float_const_a0;
extern float g_float_const_a8;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x10017f30
// gm_RemoveObjectWrapper

int __cdecl gm_RemoveObjectWrapper(int entity_record, unsigned int obj_type)
{
	int remove_result;

	remove_result = gm_RemoveObjectByType((void**) (entity_record + 0x5d), obj_type);
	if (remove_result == -2) {
		return -3;
	}
	return 0;
}

/* Removes a link from an entity. Clears a specific entity
 * reference field, breaking the association. */

// FUNCTION: SERVER 0x10017f60
// gm_RemoveEntityLink

void __cdecl gm_RemoveEntityLink(int entity)
{
	int parent_entity;

	parent_entity = (int) gm_EntityAccumulate((void*) entity);
	if (parent_entity != 0) {
		gm_RemoveLinkedNodeById((int*) (parent_entity + 0x5d), *(int*) (entity + 2));
	}
}

/* Initializes an entity if it exists. Validates the entity
 * pointer, then sets default field values. No-op on NULL. */


/* EntityStruct — stride 0x21c (540 bytes), 768 entries at g_entity_array (0x100358a0)
 * Field map derived from EXE cross-reference (Europa1400Gold_TL.exe):
 *   +0x00 (2)  entity_index      Self-index in array (0xFFFF = free slot)
 *   +0x02 (1)  entity_state      0x0F = dead/free, 0x06/0x07 = active types
 *   +0x04 (4)  entity_id         Unique ID from g_next_object_id
 *   +0x08 (1)  health            Init 100 (0x64)
 *   +0x09 (1)  gender
 *   +0x0A (2)  profession_type
 *   +0x0D (1)  is_active         Init 1
 *   +0x10 (4)  pos_x             float
 *   +0x14 (4)  pos_y             float
 *   +0x18 (4)  pos_z             float
 *   +0x1C (4)  scale             float (init 1000.0)
 *   +0x20 (4)  rotation          float
 *   +0x25 (2)  owner_index
 *   +0x27 (2)  parent_index      Used in gm_ResolveParentEntity
 *   +0x28 (2)  season_born       Set to g_current_year on alloc
 *   +0x50 (2)  max_hp            Init 0x7FFF
 *   +0x5C (32) ref_table[8]      Reference IDs (init -1)
 *   +0x80 (5)  name              Random chars on alloc
 *   +0x88 (168) stats_block      Skills/attributes
 *   +0x164(1)  age
 *   +0x16C(4)  home_building
 *   +0x170(4)  current_building
 *   +0x178(1)  linked_list_head  Free list for gm_FreeObjectListRecursive
 *   +0x18C(4)  target_id         Init -1
 *   +0x190(4)  ai_state          Init 4
 *   +0x1CC(4)  entity_flags      Bitfield
 *   +0x1E4(4)  move_speed        Init 1.0f (0x3F800000)
 *   +0x1F0(4)  quest_state
 *   +0x20C(4)  cutscene_id       Used in check_cutscene_ready
 *   +0x210(4)  patrol_target     Init -1
 */
struct EntityStruct {
	unsigned short word0; /* +0x00: entity_index */
	unsigned char byte2;  /* +0x02: entity_state */
	unsigned char pad3;
	int id;     /* +0x04: entity_id (g_next_object_id) */
	char byte8; /* +0x08: health */
	char pad9[0x28 - 9];
	unsigned short word28; /* +0x28: season_born */
	char pad2a[0x5c - 0x2a];
	int table5c[8]; /* +0x5C: ref_table (init -1) */
	char pad7c[0x178 - 0x7c];
	char field178; /* +0x178: linked_list_head */
	char pad179[0x21c - 0x179];
};

// DATA: SERVER 0x10035880
extern unsigned short g_something_1[1];
// DATA: SERVER 0x1009acfc
// DATA: SERVER 0x100358fc
extern int g_entity_ref_table[1];

// DATA: SERVER 0x10031500
// DATA: SERVER 0x10031538

/* Deallocates an entity completely. Frees all linked objects,
 * removes from entity tables, and releases memory. */

// FUNCTION: SERVER 0x10017fb0
// gm_DeallocEntity
//   NEAR_MATCHING 182/278: logic, calls, and sprintf blocks (fmt 0x10031500 for
//   arg2==0, 0x10031538 for arg2==1) all correct. Remaining diffs are msvc6
//   register allocation: the ref-clear loop reloads [esi+4] per inner
//   iteration in the original (ours per outer, `cmp [eax],edi` folded), and
//   the memset/store order after the ref loop differs by two instructions.
//   Semantics identical.

int __cdecl sprintf(char* buffer, const char* format, ...); /* 0x1001a299 */

void __cdecl gm_DeallocEntity(unsigned int index, int arg2)
{
	char buffer[0x200];
	char* entity;
	int entity_id;
	int i;
	int j;
	int* ref;

	entity = (char*) 0x100358a0 + index * 0x21c;
	entity_id = *(int*) (entity + 4);
	if (*(unsigned char*) (entity + 2) != 0xf) {
		entity[8] = 0;
		*(short*) (entity + 0x28) = *(short*) 0x10035880;
		gm_InitEntityIfValid((short*) entity);
		entity[2] = 0xf;
	}
	gm_FreeObjectListRecursive((char**) (entity + 0x178));
	if (arg2 != 0) {
		if (*(unsigned short*) entity != 0xffff) {
			g_citizen_count--;
		}
		for (i = 0; i < 0x300; i++) {
			ref = (int*) ((char*) 0x100358fc + i * 0x21c);
			for (j = 0; j < 8; j++) {
				if (*(int*) (entity + 4) == ref[j]) {
					ref[j] = -1;
				}
			}
		}
		memset(entity, 0, 0x21c);
		*(unsigned short*) entity = 0xffff;
		*(int*) (entity + 4) = -1;
		memset((char*) 0x100358fc + index * 0x21c, 0xff, 0x20);
		if (arg2 == 1) {
			sprintf(buffer, (char*) 0x10031538, entity_id);
		}
	} else {
		sprintf(buffer, (char*) 0x10031500, entity_id);
	}
}

/* Initializes entity slots to default/empty values. Zeros
 * link fields and sets capacity counters. */

// FUNCTION: SERVER 0x100180D0
// gm_InitEntitySlots

void __cdecl gm_InitEntitySlots(void)
{
	int i;
	char* ptr;

	for (i = 0; i < 0x300; i++) {
		gm_DeallocEntity(i, 2);
	}

	ptr = g_entity_base;
	do {
		memset(ptr, 0, 0xAC);
		*(short*) ptr = (short) 0xFFFF;
		ptr = ptr + 0xAC;
	} while ((int) ptr < (int) g_entity_end);

	g_citizen_count = 0;
	g_dynasty_field_2c = 0;
	g_dynasty_generation_counter = 0;
}

/* Checks if a value is within a range [min, max]. Returns
 * non-zero if within bounds. */

// FUNCTION: SERVER 0x10018130
// gm_IsInRange

int __cdecl gm_IsInRange(int x)
{
	int r;
	r = gm_MapEntityStatRange(x);
	if (r >= 10 && r <= 14) {
		return 0;
	}
	return 2;
}

/* Checks if an entity type is of a specific class. Returns
 * non-zero if the type matches the expected entity class. */

// FUNCTION: SERVER 0x10018150
// gm_EntityClassCheck
int __cdecl gm_EntityClassCheck(int type)
{
	switch (type) {
	case 5:
	case 6:
	case 13:
	case 14:
	case 25:
	case 26:
		return 2;
	case 1:
	case 2:
	case 3:
	case 4:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		return 0;
	default:
		return 2;
	}
}

/* Checks if an entity's stat is at or above a threshold.
 * Used for skill/ability requirement checks. */

// FUNCTION: SERVER 0x100181a0
// gm_CheckStatLevel

// DATA: SERVER 0x10035a04
extern unsigned char g_entity_type_bytes[];

int __cdecl gm_CheckStatLevel(int entity_idx, int stat_id)
{
	int idx;
	int val;
	int result;

	idx = entity_idx * 0x21c;
	val = gm_MapEntityStatRange((int) g_entity_type_bytes[idx]);
	if (val == stat_id) {
		return (unsigned int) g_entity_type_bytes[idx];
	}
	result = (int) gm_GetEntityTableEntry(g_entity_array + idx);
	if (result == 0) {
		return 0;
	}
	return (unsigned int) *(unsigned char*) (result + 0x74 + stat_id);
}

/* Maps and clamps an entity stat value to a valid range.
 * Applies min/max bounds and any stat modifiers. */

// FUNCTION: SERVER 0x10018200
// gm_MapEntityStatRange

int __cdecl gm_MapEntityStatRange(int stat_id)
{
	switch (stat_id) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		return 0xb;
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xc:
		return 9;
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
	case 0x12:
		return 7;
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
		return 6;
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x1d:
	case 0x1e:
		return 8;
	case 0x1f:
	case 0x20:
	case 0x21:
		return 0x10;
	case 0x22:
	case 0x23:
	case 0x24:
	case 0x25:
	case 0x26:
	case 0x27:
		return 5;
	case 0x28:
	case 0x29:
	case 0x2a:
	case 0x2b:
	case 0x2c:
	case 0x2d:
		return 0xc;
	case 0x2e:
	case 0x2f:
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
		return 1;
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
		return 10;
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
		return 2;
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
		return 3;
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
		return 4;
	case 0x4c:
	case 0x4d:
	case 0x4e:
	case 0x4f:
	case 0x50:
	case 0x51:
		return 0xd;
	case 0x59:
	case 0x5a:
	case 0x5b:
	case 0x5c:
	case 0x5d:
	case 0x5e:
		return 0xf;
	case 0x53:
	case 0x54:
	case 0x55:
	case 0x56:
	case 0x57:
	case 0x58:
		return 0xe;
	default:
		return 0;
	}
}

/* Returns the opposite stat index for paired stats.
 * E.g., maps strength to weakness, charisma to shyness.
 * Used for character stat balancing. */

// FUNCTION: SERVER 0x10018330
// gm_GetOppositeStatIndex

/*
 * Mirrors/reverses the position of an index within its group of 6.
 * Each group of 6 consecutive values gets its position flipped:
 *   groupStart -> groupStart+5, groupStart+1 -> groupStart+4, etc.
 * Returns 0 if the index doesn't belong to any known group.
 */
int __cdecl gm_GetOppositeStatIndex(int stat_id)
{
	int result;

	result = 0;

	/* Group 1-6 (section A, row 1) */
	if ((stat_id >= 1) && (stat_id <= 6)) {
		return 7 - stat_id;
	}
	/* Group 7-12 (section A, row 2) */
	if ((stat_id >= 7) && (stat_id <= 12)) {
		return 13 - stat_id;
	}
	/* Group 34-39 (section B, row 1) */
	if ((stat_id >= 34) && (stat_id <= 39)) {
		return 40 - stat_id;
	}
	/* Group 40-45 (section B, row 2) */
	if ((stat_id >= 40) && (stat_id <= 45)) {
		return 46 - stat_id;
	}
	/* Group 46-51 (section B, row 3) */
	if ((stat_id >= 46) && (stat_id <= 51)) {
		return 52 - stat_id;
	}
	/* Group 58-63 (section B, row 5) */
	if ((stat_id >= 58) && (stat_id <= 63)) {
		return 64 - stat_id;
	}
	/* Group 64-69 (section B, row 6) */
	if ((stat_id >= 64) && (stat_id <= 69)) {
		return 70 - stat_id;
	}
	/* Group 70-75 (section B, row 7) */
	if ((stat_id >= 70) && (stat_id <= 75)) {
		return 76 - stat_id;
	}
	/* Group 13-18 (section A, row 3) */
	if ((stat_id >= 13) && (stat_id <= 18)) {
		return 19 - stat_id;
	}
	/* Group 52-57 (section B, row 4) */
	if ((stat_id >= 52) && (stat_id <= 57)) {
		return 58 - stat_id;
	}
	/* Group 25-30 (section A, row 5) */
	if ((stat_id >= 25) && (stat_id <= 30)) {
		return 31 - stat_id;
	}
	/* Group 19-24 (section A, row 4) */
	if ((stat_id >= 19) && (stat_id <= 24)) {
		return 25 - stat_id;
	}
	/* Group 76-81 (section C, row 1) */
	if ((stat_id >= 76) && (stat_id <= 81)) {
		return 82 - stat_id;
	}
	/* Group 89-94 (section C, row 3) */
	if ((stat_id >= 89) && (stat_id <= 94)) {
		return 95 - stat_id;
	}
	/* Group 83-88 (section C, row 2) */
	if ((stat_id >= 83) && (stat_id <= 88)) {
		result = 89 - stat_id;
	}
	return result;
}

/* Generates a random stat modifier. Produces a random
 * delta value for stat variation during entity creation
 * or level-up events. */

// FUNCTION: SERVER 0x10018450
// gm_RandomStatModifier
//   NEAR_MATCHING 24/78: logic correct (zero-case, const-57bc double compare,
//   0xb/6 ranges, byte accumulation). Remaining diffs are msvc6 FPU/branch
//   codegen: original emits `fcomp [const]` + `test ah,1` (ours fld+fcompp +
//   test ah,0x41), byte-width loads/adds (mov bl / add al / add bl,al vs our
//   dword forms), and the range-select branch layout. Not reproducible.

char __cdecl gm_RandomStatModifier(char stat_value)
{
	if (stat_value == 0) {
		return (char) (gm_RandomMod(0x2a) + 0x15);
	}
	if ((double) (unsigned char) stat_value < g_const_57bc) {
		return (char) (stat_value + gm_RandomMod(6));
	}
	return (char) (stat_value + gm_RandomMod(0xb));
}

/* Looks up an entity record by its integer ID. Searches
 * the global entity table and returns a pointer to the
 * matching entity, or 0 if not found. */

// FUNCTION: SERVER 0x100184A0
// gm_LookupEntityRecordById
int __cdecl gm_LookupEntityRecordById(int search_id)
{
	char* p;
	int i;
	i = 0;
	p = (char*) 0x100358A4;
	while ((int) p < (int) 0x1009ACA4) {
		if (*(unsigned short*) (p - 4) != 0xFFFF) {
			if (*(int*) p == search_id) {
				return i * 0x21C + 0x100358A0;
			}
		}
		p += 0x21C;
		i++;
	}
	return 0;
}

/* Gets a pointer to an entity's type table entry.
 * Indexes into g_entity_type_table by the entity's type byte. */

// FUNCTION: SERVER 0x100184e0
// gm_GetEntityTableEntry

short* __cdecl gm_GetEntityTableEntry(char* param)
{
	char type;
	int table_index;

	type = param[2];
	if (type == 6 || type == 7 || type == 5) {
		if ((*(unsigned short*) (param + 0x50) & 0x8000) != 0) {
			table_index = *(unsigned short*) (param + 0x50) & 0xf;
			if (table_index >= 0 && table_index < 0x10) {
			}
			if (table_index >= 0 && table_index < 0x10) {
				return (short*) (&entity_table[table_index * 0xac]);
			}
		}
	}
	return (short*) 0;
}

/* Implementation of player identity change. Swaps player
 * entity identity between two IDs, updating all back-
 * references in buildings and citizens. */

