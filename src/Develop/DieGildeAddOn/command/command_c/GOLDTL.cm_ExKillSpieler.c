
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 72B
 *    CFlags:
 *    Symbol: _CmdKillPlayer
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExKillSpieler(int param_1)
 *
 * {
 *   ushort *puVar1;
 *
 *   puVar1 = (ushort *)gm_LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   if (puVar1 != (ushort *)0x0) {
 *     gm_KillSpieler((uint)*puVar1,*(int *)(param_1 + 0x14));
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x397d,
 *                      s_cm_ExKillSpieler___Could_not_fin,1);
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

// FUNCTION: GOLDTL 0x40fcd0
// SIZE: 65
void* __cdecl fcn_0041dd90(int);
int __cdecl fcn_00452420(int);
int __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl cm_ExKillSpieler(int cmd)
{
	void* e;
	e = fcn_0041dd90(*(int*) cmd);
	if (e != 0) {
		fcn_00452420(*(int*) cmd);
	} else {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676988);
	}
	return 0;
}
