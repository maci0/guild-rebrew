// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _cm_ExAssignOffice

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _call_with_off2
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAssignOffice(void *obj)
 * 
 * {
 *   uint uVar1;
 *   
 *   uVar1 = ValidateAndAssignOffice((uint *)((int)obj + 0x10));
 *   return (uint)(uVar1 == 0);
 * }
 */

extern unsigned int __cdecl ValidateAndAssignOffice(unsigned int*);

// FUNCTION: SERVER 0x1000f940
int __cdecl cm_ExAssignOffice(void* obj)
{
	unsigned int result;

	result = ValidateAndAssignOffice((unsigned int*) ((int) obj + 0x10));
	return result == 0;
}
