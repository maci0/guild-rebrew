
#include "../command_internal.h"
#include "../../../Units/Error/error.h"
#include "../../game/entity.h"

ushort __cdecl gm_AllocSpieler(uint, int, int, ushort, int, uint, uint, uint);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern int __cdecl rand(void);
extern char g_entity_state_base[];
extern int g_entity_id_field; /* 0x100358A4 */
extern unsigned char g_slot_table[];
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
/* Round-536: ascending REF VA decl order (R521/R531–R535 mid-pocket lever; 2-string cluster). */
char s_cm_ExAllocCharacter___gm_AllocSp_1002d364[] = "cm_ExAllocCharacter():gm_AllocSpieler() failed";
char s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394[] = "Invalid 'GI_Id' for cmdt_ALLOC_CHARACTER in cm_ExecCommand()";

/* Execution handler: creates a new citizen (Buerger) entity.
 * Seeds RNG state into the command packet, resolves the GI_Id
 * family filter, allocates the entity, links it to its home
 * building, and publishes the new entity id into the player
 * slot at offset 0x264200. Writes result status into result[0]. */

// FUNCTION: SERVER 0x1000f980

int __cdecl cm_ExCreateCitizen(int cmd, char* result)
{
	int field;
	unsigned int entity;
	unsigned int idx;

	*(int *) (cmd + 0x10) = g_next_object_id;
	*(int *) (cmd + 0x22) = rand();
	if (result) {
		result[0] = 2;
		result[1] = 1;
		*(int *) (result + 6) = 0;
	}
	srv_SeedRandom(*(int *) (cmd + 0x22));
	if (*(int *) (cmd + 0x17) != -1) {
		field = gm_GetFieldByType((char *) cmd, *(int *) (cmd + 0x17));
		*(int *) (cmd + 0x17) = field;
		if (gm_StartFilteredEntitySearch(1, 1, field) == 0) {
			LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x5246,
			                   s_Invalid__GI_Id__for_cmdt_ALLOC_C_1002d394, 1);
			return 1;
		}
	}
	entity = gm_AllocSpieler(
	    *(unsigned char *) (cmd + 0x14), -1, -1, 0x14, 0,
	    *(unsigned char *) (cmd + 0x1f), *(unsigned char *) (cmd + 0x20), 0);
	entity = entity & 0xffff;
	if (entity == 0xffff) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x525a,
		                   s_cm_ExAllocCharacter___gm_AllocSp_1002d364, 1);
		return 1;
	}
	if (*(int *) (cmd + 0x1b) != -1) {
		gm_FindRecordById(*(int *) (cmd + 0x1b));
	}
	idx = entity * 0x21c;
	g_query_state_a0c[entity * 0x87] = 0;
	g_entity_state_base[idx] = 0xd;
	if (*(unsigned char *) (cmd + 0x21) != 0) {
		gm_AllocObjekt(*(unsigned int *) ((char*) &g_entity_id_field + idx),
		               *(unsigned char *) (cmd + 0x21), 1);
	}
	*((unsigned int *) (0x10442d00 + (unsigned char) *(char *) (cmd + 3) * 0x264264)) =
	    *(unsigned int *) ((char*) &g_entity_id_field + idx);
	if (result) {
		result[0] = 1;
		result[1] = 1;
		*(int *) (result + 6) = (int) (g_slot_table + idx);
	}
	return 0;
}
