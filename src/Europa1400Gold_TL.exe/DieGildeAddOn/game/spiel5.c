#include "../../game_structs.h"
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
void __cdecl m_FreeTracked(void*);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern unsigned char g_slot_table[2];
int __cdecl gm_FreeObjectListRecursive(char**);
extern int g_next_object_id; /* defined in spiel.c */
int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[]; /* defined in spiel.c */
void __cdecl gv_Free3Fields(void* param);
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

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: GOLDTL 0x504100
// SIZE: 48
// gm_SearchStruct

char* __cdecl gm_SearchStruct(void)
{
	EntityQueryRecord* entity_cursor;
	EntityQueryRecord* end;
	entity_cursor = (EntityQueryRecord*) g_entity_ptr;
	end = entity_cursor + 0x100;
	while (entity_cursor < end) {
		if (entity_cursor->type == 0) {
			break;
		}
		entity_cursor++;
	}
	if (entity_cursor < end) {
		return entity_cursor;
	}
	return 0;
}

/* Cleans up a building entity. Frees all contained entities
 * (workers, inventory, production slots) and resets the
 * building to an empty state. */
