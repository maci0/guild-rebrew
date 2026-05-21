
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 85B
 *    CFlags:
 *    Symbol: _cm_ExKillTransporter
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExKillTransporter(int cmd,char *result)
 *
 * {
 *   void *pvVar1;
 *
 *   pvVar1 = gm_FindRecordById(*(int *)(cmd + 0x10));
 *   if (pvVar1 == (void *)0x0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x52d8,
 *                        s_cm_ExKillTransporter____invalid_t_1002d3d4,1);
 *     return 1;
 *   }
 *   gm_RemoveEntityLink((int)pvVar1);
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
 *     result[1] = '\0';
 *     result[6] = '\0';
 *     result[7] = '\0';
 *     result[8] = '\0';
 *     result[9] = '\0';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExKillTransporter____invalid_t_1002d3d4[];

/* Execution handler: removes a transporter entity. Resolves
 * entity by ID and deallocates it from the game world. */

// FUNCTION: SERVER 0x1000fad0
int __cdecl cm_ExKillTransporter(int cmd, char* result)
{
	void* record;

	record = gm_FindRecordById(*(int*) (cmd + 0x10));
	if (record == (void*) 0x0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x52d8,
			s_cm_ExKillTransporter____invalid_t_1002d3d4,
			1
		);
		return 1;
	}
	gm_RemoveEntityLink((int) record);
	if (result != (char*) 0x0) {
		*result = '\x01';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}
	return 0;
}
