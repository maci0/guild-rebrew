// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 70

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 70B
 *    CFlags: 
 *    Symbol: _ModifyEntityHealth
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExModifyHealth(int param_1)
 * 
 * {
 *   int iVar1;
 *   uint uVar2;
 *   
 *   iVar1 = gm_LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   if (iVar1 == 0) {
 *     return 1;
 *   }
 *   uVar2 = *(int *)(param_1 + 0x14) + *(int *)(iVar1 + 0x194);
 *   uVar2 = uVar2 & ((int)uVar2 < 0) - 1;
 *   if (0x31 < (int)uVar2) {
 *     uVar2 = 0x32;
 *   }
 *   *(uint *)(iVar1 + 0x194) = uVar2;
 *   return 0;
 * }
 */

#include "../command_internal.h"

/* Execution handler: modifies an entity's health value.
 * Looks up entity by ID at cmd+0x10 and applies the health
 * delta from the command payload. */

// FUNCTION: SERVER 0x1000ffc0
int __cdecl cm_ExModifyHealth(int param_1)
{
	int entity;
	uint health;

	entity = gm_LookupEntityRecordById(*(int*) (param_1 + 0x10));
	if (entity == 0) {
		return 1;
	}
	health = *(int*) (param_1 + 0x14) + *(int*) (entity + 0x194);
	health = health & ((int) health < 0) - 1;
	if ((int) health >= 0x32) {
		health = 0x32;
	}
	*(uint*) (entity + 0x194) = health;
	return 0;
}
