// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 72

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
 *   puVar1 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   if (puVar1 != (ushort *)0x0) {
 *     DeallocEntity((uint)*puVar1,*(int *)(param_1 + 0x14));
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x397d,
 *                      s_cm_ExKillSpieler___Could_not_fin_1002d154,1);
 *   return 0;
 * }
 */

#include "../command_internal.h"

extern void __cdecl DeallocEntity(uint, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern char s_cm_ExKillSpieler___Could_not_fin_1002d154[];

// FUNCTION: SERVER 0x1000f030
int __cdecl cm_ExKillSpieler(int param_1)
{
	ushort* puVar1;

	puVar1 = (ushort*) LookupEntityRecordById(*(int*) (param_1 + 0x10));
	if (puVar1 != (ushort*) 0x0) {
		DeallocEntity((uint) *puVar1, *(int*) (param_1 + 0x14));
		return 0;
	}
	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x397d,
		s_cm_ExKillSpieler___Could_not_fin_1002d154,
		1
	);
	return 0;
}
