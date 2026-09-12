
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 41B
 *    CFlags:
 *    Symbol: _ValidateEntityLookup
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ChkEntityLookup(int param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *     param_2[1] = '\0';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   iVar1 = gm_LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

#include "../command_internal.h"

/* Validation handler: looks up an entity by ID from offset 0x10
 * of the command. Returns 1 (fail) if no entity found, 0 on
 * success. Clears param_2[1] if result buffer is non-null. */

// FUNCTION: GOLDTL 0x4cc490
// SIZE: 44
int __cdecl cm_ChkEntityLookup(int cmd, char* result)
{
	int found;

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}
	found = gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	return (unsigned int) (found == 0);
}
