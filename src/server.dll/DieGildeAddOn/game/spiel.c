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
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern char* g_array_base;
// DATA: SERVER 0x100358a0
extern unsigned char g_slot_table[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(char* slot);
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
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_KillSpieler(unsigned int idx, int param);
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
void* __cdecl gm_AddObjekt(int, int, int);
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

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10015CB0
// gm_ResetAllEntities

void __cdecl gm_ResetAllEntities(void)
{
	int i;
	char* entity_cursor;
	for (i = 0; i < 0x100; i++) {
		entity_cursor = g_entity_ptr + i * 0xa9;
		if (*entity_cursor != 0) {
			gm_CleanupBuildingEntity((unsigned char*) entity_cursor);
		}
	}
	{
		int* dst;
		int n;
		dst = (int*) g_entity_ptr;
		for (n = 0; n < 0x2a40; n++) {
			*dst++ = 0;
		}
	}
}

/* Cleans up object entities. Frees inventory objects and
 * linked item chains from all active entities. */

// FUNCTION: SERVER 0x10015cf0
// gm_CleanupObjectEntities
//   Loop counts records (i < 0x5008, i++) and scales by the 0x43 stride at each
//   use, rather than stepping a byte offset by 0x43.  msvc6 strength-reduces the
//   i*0x43 induction variable itself into esi, which makes esi the SIB base and
//   keeps the reloaded g_query_base live, so the gm_NoopRet2 argument is formed
//   with `lea ecx,[esi+eax]`.  Pre-computing the byte offset instead lets the
//   compiler fold it to `add eax,esi`, one byte short of the 194-byte target.

int __cdecl gm_RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
void __cdecl gm_NoopRet2(char* slot);

void __cdecl gm_CleanupObjectEntities(void)
{
	int i;
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* list_head;

	for (i = 0; i < 0x5008; i++) {
		if (*(unsigned short*) ((char*) g_query_base + i * 0x43) != 0) {
			gm_ResolveEntityById(&dynamic, &existing, &static_ptr, *(int*) ((char*) g_query_base + i * 0x43 + 6));
			if (dynamic != NULL) {
				list_head = (char*) dynamic + 0x5d;
			} else if (existing != NULL) {
				list_head = (char*) existing + 0x14;
			} else if (static_ptr != NULL) {
				list_head = (char*) static_ptr + 0x178;
			} else {
				list_head = NULL;
			}
			if (list_head != NULL) {
				gm_RemoveObjectByType((void**) list_head, *(unsigned short*) ((char*) g_query_base + i * 0x43));
			} else {
				gm_NoopRet2((char*) g_query_base + i * 0x43);
				*(unsigned short*) ((char*) g_query_base + i * 0x43) = 0;
				g_query_limit--;
			}
		}
	}
	memset(g_query_base, 0, 0x14f218);
}
/* Finds a record in the entity table by ID. Searches the
 * global entity records for a matching entity ID. Returns
 * pointer or NULL. */

// FUNCTION: SERVER 0x10015dc0
// gm_FindRecordById

Record* __cdecl gm_FindRecordById(int id)
{
	int i;
	Record* entity_cursor;

	i = 0;
	entity_cursor = (Record*) g_query_base;
	while (i < 0x5008) {
		if (entity_cursor->active != 0 && entity_cursor->id == id) {
			return (Record*) ((char*) g_query_base + i * 0x43);
		}
		i++;
		entity_cursor = (Record*) ((char*) entity_cursor + 0x43);
	}
	return (Record*) 0;
}

/* Cleans up all entities. Complete teardown of all game
 * entities including buildings, citizens, and objects. */

// FUNCTION: SERVER 0x10015E00
// gm_CleanupAllEntities

void __cdecl gm_CleanupAllEntities(void)
{
	int ent;
	ent = (int) gm_StartFilteredEntitySearch(1, 6);
	if (ent) {
		do {
			((void(__cdecl*)(unsigned char*)) gm_CleanupBuildingEntity)((unsigned char*) ent);
			ent = (int) gm_FindNextFilteredEntity();
		} while (ent);
	}
	if (g_entity_type_table) {
		m_FreeTracked(g_entity_type_table);
		g_entity_type_table = 0;
	}
	if (g_entity_ptr) {
		m_FreeTracked(g_entity_ptr);
		g_entity_ptr = 0;
	}
	if (g_item_def_table) {
		m_FreeTracked(g_item_def_table);
		g_item_def_table = 0;
	}
	if (g_query_base) {
		m_FreeTracked(g_query_base);
		g_query_base = 0;
	}
}

/* Resolves an entity by ID to up to three pointers:
 * primary entity, object entity, and dynamic entity.
 * Returns non-zero on success. Core entity resolution API. */

// FUNCTION: SERVER 0x10015e90
// gm_ResolveEntityById


int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	int i;
	char* entity_cursor;

	if (g_item_def_table == NULL) {
		return 0;
	}
	if (dynamic != NULL) {
		*dynamic = NULL;
	}
	if (existing != NULL) {
		*existing = NULL;
	}
	if (static_ptr != NULL) {
		*static_ptr = NULL;
		entity_cursor = (char*) 0x100358a0;
		for (i = 0; i < 0x300; i++) {
			if (*(unsigned short*) entity_cursor != 0xffff && *(int*) (entity_cursor + 4) == entity_id) {
				*static_ptr = entity_cursor;
				return 3;
			}
			entity_cursor += 0x21c;
		}
	}
	if (dynamic != NULL) {
		entity_cursor = (char*) g_entity_ptr;
		for (i = 0; i < 0x100; i++, entity_cursor += 0xa9) {
			if (*(char*) entity_cursor != 0 && *(int*) (entity_cursor + 1) == entity_id) {
				*dynamic = entity_cursor;
				return 1;
			}
		}
	}
	if (existing != NULL) {
		entity_cursor = (char*) g_query_base;
		for (i = 0; i < g_query_limit; entity_cursor += 0x43) {
			if (*(unsigned short*) entity_cursor != 0) {
				if (*(int*) (entity_cursor + 2) == entity_id) {
					*existing = entity_cursor;
					return 2;
				}
				i++;
			}
		}
	}
	return 0;
}

/* Refreshes market availability. Recalculates which goods
 * are available for trade based on current building production
 * and inventory states. */

