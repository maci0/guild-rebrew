// FUNCTION: SERVER 0x10010010
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 110
// CFLAGS: /O2 /Gd
// SYMBOL: _ModifyEntityStamina

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 110B
 *    CFlags: 
 *    Symbol: _ModifyEntityStamina
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ModifyEntityStamina(int param_1)
 * 
 * {
 *   int iVar1;
 *   char cVar2;
 *   uint uVar3;
 *   
 *   iVar1 = LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   if (iVar1 != 0) {
 *     uVar3 = *(int *)(param_1 + 0x14) + (uint)*(byte *)(iVar1 + 0x1b1);
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
 *     UpdateEntityLinks(iVar1,*(int *)(param_1 + 0x18));
 *     return 0;
 *   }
 *   return 1;
 * }
 */

extern int __cdecl LookupEntityRecordById(int);
extern void __cdecl UpdateEntityLinks(int, int);

int __cdecl ModifyEntityStamina(int param_1)
{
	int iVar1;
	unsigned int uVar3;

	iVar1 = LookupEntityRecordById(*(int*) (param_1 + 0x10));
	if (iVar1 == 0) {
		return 1;
	}
	uVar3 = *(int*) (param_1 + 0x14) + (unsigned int) *(unsigned char*) (iVar1 + 0x1b1);
	uVar3 = uVar3 & ((int) uVar3 < 0) - 1;
	if ((int) uVar3 >= 0xff) {
		uVar3 = 0xff;
	}
	*(char*) (iVar1 + 0x1b1) = (char) uVar3;
	if ((unsigned char) uVar3 > '\0') {
		uVar3 = uVar3 & 0xff;
	}
	else {
		uVar3 = 0;
	}
	*(char*) (iVar1 + 0x1b1) = (char) uVar3;
	UpdateEntityLinks(iVar1, *(int*) (param_1 + 0x18));
	return 0;
}
