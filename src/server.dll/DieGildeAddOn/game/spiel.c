#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
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
// DATA: SERVER 0x100358a0
extern char g_entity_array[];
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

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10015CB0
// gm_ResetAllEntities

void __cdecl gm_ResetAllEntities(void)
{
	int i;
	char* p;
	for (i = 0; i < 0x100; i++) {
		p = g_entity_ptr + i * 0xa9;
		if (*p != 0) {
			gm_CleanupBuildingEntity((unsigned char*) p);
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
//   NEAR_MATCHING 139/194: control flow and all calls match; remaining diffs
//   are msvc6 addressing-mode choices — original encodes [esi+eax] (counter as
//   base reg) and uses `lea ecx,[esi+eax]` for the cleanup pointer (ours folds
//   to `add eax,esi`, 1 byte smaller, hence SIZE_MISMATCH). Not reachable with
//   this compiler's address-mode selection; semantics are identical.

int __cdecl gm_RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
void __cdecl gm_NoopRet2(char* slot);

void __cdecl gm_CleanupObjectEntities(void)
{
	int i;
	void* dynamic;
	void* existing;
	void* static_ptr;
	char* list_head;

	for (i = 0; i < 0x14f218; i += 0x43) {
		if (*(unsigned short*) (i + (char*) g_query_base) != 0) {
			gm_ResolveEntityById(&dynamic, &existing, &static_ptr, *(int*) (i + (char*) g_query_base + 6));
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
				gm_RemoveObjectByType((void**) list_head, *(unsigned short*) (i + (char*) g_query_base));
			} else {
				gm_NoopRet2(i + (char*) g_query_base);
				*(unsigned short*) (i + (char*) g_query_base) = 0;
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
	Record* p;

	i = 0;
	p = g_records;
	while (i < 0x5008) {
		if (p->active != 0 && p->id == id) {
			return (Record*) ((char*) g_records + i * 0x43);
		}
		i++;
		p = (Record*) ((char*) p + 0x43);
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
			ent = (int) FindNextFilteredEntity();
		} while (ent);
	}
	if (g_data_ptr) {
		free_block(g_data_ptr);
		g_data_ptr = 0;
	}
	if (g_data_ptr2) {
		free_block(g_data_ptr2);
		g_data_ptr2 = 0;
	}
	if (g_data_ptr3) {
		free_block(g_data_ptr3);
		g_data_ptr3 = 0;
	}
	if (g_data_ptr4) {
		free_block(g_data_ptr4);
		g_data_ptr4 = 0;
	}
}

/* Resolves an entity by ID to up to three pointers:
 * primary entity, object entity, and dynamic entity.
 * Returns non-zero on success. Core entity resolution API. */

// FUNCTION: SERVER 0x10015e90
// gm_ResolveEntityById

extern int g_1014d8c0;

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	int i;
	char* p;

	if (g_entity_table == NULL) {
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
		p = (char*) 0x100358a0;
		for (i = 0; i < 0x300; i++) {
			if (*(unsigned short*) p != 0xffff && *(int*) (p + 4) == entity_id) {
				*static_ptr = p;
				return 3;
			}
			p += 0x21c;
		}
	}
	if (dynamic != NULL) {
		p = (char*) g_1014d8c0;
		for (i = 0; i < 0x100; i++, p += 0xa9) {
			if (*(char*) p != 0 && *(int*) (p + 1) == entity_id) {
				*dynamic = p;
				return 1;
			}
		}
	}
	if (existing != NULL) {
		p = (char*) g_query_base;
		for (i = 0; i < g_query_limit; p += 0x43) {
			if (*(unsigned short*) p != 0) {
				if (*(int*) (p + 2) == entity_id) {
					*existing = p;
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

