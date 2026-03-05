// FUNCTION: SERVER 0x1000ffc0
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 70
// CFLAGS: /O2 /Gd
// SYMBOL: _ModifyEntityHealth

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 70B
 *    CFlags: 
 *    Symbol: _ModifyEntityHealth
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ModifyEntityHealth(int param_1)
 * 
 * {
 *   int iVar1;
 *   uint uVar2;
 *   
 *   iVar1 = LookupEntityRecordById(*(int *)(param_1 + 0x10));
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

typedef unsigned int uint;

extern int __cdecl LookupEntityRecordById(int);

int __cdecl ModifyEntityHealth(int param_1)
{
	int iVar1;
	uint uVar2;

	iVar1 = LookupEntityRecordById(*(int*) (param_1 + 0x10));
	if (iVar1 == 0) {
		return 1;
	}
	uVar2 = *(int*) (param_1 + 0x14) + *(int*) (iVar1 + 0x194);
	uVar2 = uVar2 & ((int) uVar2 < 0) - 1;
	if ((int) uVar2 >= 0x32) {
		uVar2 = 0x32;
	}
	*(uint*) (iVar1 + 0x194) = uVar2;
	return 0;
}
