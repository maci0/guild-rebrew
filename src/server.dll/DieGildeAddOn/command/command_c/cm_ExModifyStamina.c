
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 110B
 *    CFlags: 
 *    Symbol: _ModifyEntityStamina
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExModifyStamina(int cmd)
 * 
 * {
 *   int iVar1;
 *   char cVar2;
 *   uint uVar3;
 *   
 *   iVar1 = gm_LookupEntityRecordById(*(int *)(cmd + 0x10));
 *   if (iVar1 != 0) {
 *     uVar3 = *(int *)(cmd + 0x14) + (uint)*(byte *)(iVar1 + 0x1b1);
 *     uVar3 = uVar3 & ((int)uVar3 < 0) - 1;
 *     if (0xfe < (int)uVar3) {
 *       uVar3 = 0xff;
 *     }
 *     cVar2 = (char)uVar3;
 *     *(char *)(iVar1 + 0x1b1) = cVar2;
 *     if (cVar2 == '\0') {
 *       cVar2 = '\0';
 *     }
 *     *(char *)(iVar1 + 0x1b1) = cVar2;
 *     amt_UpdateEntityLinks(iVar1,*(int *)(cmd + 0x18));
 *     return 0;
 *   }
 *   return 1;
 * }
 */

#include "../command_internal.h"

void __cdecl amt_UpdateEntityLinks(int, int);

/* Execution handler: modifies an entity's stamina value.
 * Looks up entity by ID at cmd+0x10 and applies the stamina
 * delta from the command payload. */

// FUNCTION: SERVER 0x10010010
int __cdecl cm_ExModifyStamina(int cmd)
{
	int entity;
	unsigned int stamina;

	entity = gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	if (entity == 0) {
		return 1;
	}
	stamina = *(int*) (cmd + 0x14) + (unsigned int) *(unsigned char*) (entity + 0x1b1);
	stamina = stamina & ((int) stamina < 0) - 1;
	if ((int) stamina >= 0xff) {
		stamina = 0xff;
	}
	*(char*) (entity + 0x1b1) = (char) stamina;
	if ((unsigned char) stamina > '\0') {
		stamina = stamina & 0xff;
	}
	else {
		stamina = 0;
	}
	*(char*) (entity + 0x1b1) = (char) stamina;
	amt_UpdateEntityLinks(entity, *(int*) (cmd + 0x18));
	return 0;
}
