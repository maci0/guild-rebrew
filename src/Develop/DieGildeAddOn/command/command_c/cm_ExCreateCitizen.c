extern unsigned char g_connections[9 * 0x264264];
#include "../command_internal.h"
#include "../../../Units/Error/error.h"
#include "../../game/entity.h"

ushort __cdecl gm_AllocSpieler(uint, int, int, ushort, int, uint, uint, uint);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern int __cdecl rand(void);

/* Execution handler: creates a new citizen (Buerger) entity.
 * Seeds RNG state into the command packet, resolves the GI_Id
 * family filter, allocates the entity, links it to its home
 * building, and publishes the new entity id into the player
 * slot at offset 0x264200. Writes result status into result[0]. */

extern unsigned char g_slot_table[0x300 * 0x21c];
/* Round-536: ascending REF VA decl order (R521/R531–R535 mid-pocket lever; 2-string cluster). */
// FUNCTION: GOLDTL 0x44c460
// SIZE: 441
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
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x5246,
			                   "Invalid 'GI_Id' for cmdt_ALLOC_CHARACTER in cm_ExecCommand()", 1);
			return 1;
		}
	}
	entity = gm_AllocSpieler(
	    *(unsigned char *) (cmd + 0x14), -1, -1, 0x14, 0,
	    *(unsigned char *) (cmd + 0x1f), *(unsigned char *) (cmd + 0x20), 0);
	entity = entity & 0xffff;
	if (entity == 0xffff) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x525a,
		                   "cm_ExAllocCharacter():gm_AllocSpieler() failed", 1);
		return 1;
	}
	if (*(int *) (cmd + 0x1b) != -1) {
		gm_FindRecordById(*(int *) (cmd + 0x1b));
	}
	idx = entity * 0x21c;
	*(unsigned int*) (g_slot_table + idx + 0x16c) = 0;
	((char*) g_slot_table)[idx + 2] = 0xd;
	if (*(unsigned char *) (cmd + 0x21) != 0) {
		gm_AllocObjekt(*(unsigned int *) ((char*) g_slot_table + idx + 4),
		               *(unsigned char *) (cmd + 0x21), 1);
	}
	*((unsigned int *) ((int) (g_connections + 0x264200) + (unsigned char) *(char *) (cmd + 3) * 0x264264)) =
	    *(unsigned int *) ((char*) g_slot_table + idx + 4);
	if (result) {
		result[0] = 1;
		result[1] = 1;
		*(int *) (result + 6) = (int) (g_slot_table + idx);
	}
	return 0;
}
