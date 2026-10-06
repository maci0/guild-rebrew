
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
 *   iVar1 = fcn_004f48e0(*(int *)(param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

#include "../command_internal.h"

/* Validation handler (TL build): looks up an entity by ID from offset 0x10.
 * Differs from the server twin: the lookup runs FIRST, and on a null result
 * buffer the function returns 0 without touching anything. With a buffer it
 * clears result[1] and result[6..9] to 0 and writes result[0] = found ? 1 : 2.
 * Per-build body under the shared name; the server twin keeps its own. */

int __cdecl fcn_004f48e0(char* idPtr);

int __cdecl cm_ChkEntityLookup(int cmd, char* result)
{
	int found;

	found = fcn_004f48e0((char*) cmd + 0x10);
	if (result != (char*) 0x0) {
		result[1] = '\0';
		*result = (char) ((found == 0) + 1);
		*(int*) (result + 6) = 0;
	}
	return 0;
}
