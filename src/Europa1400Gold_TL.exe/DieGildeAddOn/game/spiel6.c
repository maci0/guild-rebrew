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
extern unsigned char g_slot_table[2];
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

// FUNCTION: GOLDTL 0x504b30
// SIZE: 160
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
