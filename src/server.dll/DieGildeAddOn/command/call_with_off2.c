// FUNCTION: SERVER 0x1000f940
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _call_with_off2

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _call_with_off2
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl call_with_off2(void *obj)
 * 
 * {
 *   uint uVar1;
 *   
 *   uVar1 = ValidateAndAssignOffice((uint *)((int)obj + 0x10));
 *   return (uint)(uVar1 == 0);
 * }
 */

extern unsigned int __cdecl ValidateAndAssignOffice(unsigned int*);

int __cdecl call_with_off2(void* obj)
{
	unsigned int uVar1;

	uVar1 = ValidateAndAssignOffice((unsigned int*) ((int) obj + 0x10));
	return uVar1 == 0;
}
