// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _call_with_off

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _call_with_off
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl call_with_off(void *obj)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = ValidateOfficeCandidate((int *)((int)obj + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl ValidateOfficeCandidate(int*);

// FUNCTION: SERVER 0x1000d020
int __cdecl call_with_off(void* obj)
{
	int result;

	result = ValidateOfficeCandidate((int*) ((int) obj + 0x10));
	return result == 0;
}
