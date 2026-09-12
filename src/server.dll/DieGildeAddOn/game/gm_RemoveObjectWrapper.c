/* gm_RemoveObjectWrapper / gm_RemoveEntityLink.  Split out of spiel62.c:
 * the reference places gm_InitEntityIfValid (0x10017f90) between these
 * two and gm_KillSpieler (0x10017fb0), and order-sources orders whole
 * objects by their first VA, so they cannot share spiel62.c's object.
 * Prelude shared verbatim with spiel62.c. */

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
extern unsigned char g_slot_table[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
extern int g_next_object_id; /* defined in spiel.c */
extern int g_current_year;
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
