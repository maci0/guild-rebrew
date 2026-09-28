
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

// GLOBAL: SERVER 0x1002d154
extern char s_cm_ExKillSpieler___Could_not_fin[];

/* Execution handler: removes/kills a player entity (Spieler).
 * Deallocates the player and cleans up associated resources. */

// FUNCTION: SERVER 0x1000f030
int __cdecl cm_ExKillSpieler(int cmd)
{
	ushort* entity;

	entity = (ushort*) gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	if (entity != (ushort*) 0x0) {
		gm_KillSpieler((uint) *entity, *(int*) (cmd + 0x14));
		return 0;
	}
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\command\\command.c",
		0x397d,
		"cm_ExKillSpieler():Could not find SpielerID!",
		1
	);
	return 0;
}
