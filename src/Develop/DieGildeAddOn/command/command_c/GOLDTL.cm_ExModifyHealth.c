
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 70B
 *    CFlags:
 *    Symbol: _ModifyEntityHealth
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExModifyHealth(int cmd)
 *
 * {
 *   int iVar1;
 *   uint uVar2;
 *
 *   iVar1 = gm_LookupEntityRecordById(*(int *)(cmd + 0x10));
 *   if (iVar1 == 0) {
 *     return 1;
 *   }
 *   uVar2 = *(int *)(cmd + 0x14) + *(int *)(iVar1 + 0x194);
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

// FUNCTION: GOLDTL 0x406510
// SIZE: 80
void* __cdecl fcn_0040c0a0(int);

int __cdecl cm_ExModifyHealth(int cmd, char* name)
{
	unsigned char* obj;
	char* d;
	char* s;

	obj = (unsigned char*) fcn_0040c0a0(cmd);
	if (obj != 0) {
		*(int*) (obj + 0x14) = cmd;
		*(int*) (obj + 0xc) = 0;
		*(void**) (obj + 0) = (void*) 0x406410;
		obj[9] = 0x2f;
		*(int*) (obj + 0x28) = 0;
		obj[0x10] = 0;
		d = (char*) obj + 0xf0;
		s = name;
		while ((*d++ = *s++) != 0) {
		}
	}
	return 0;
}
