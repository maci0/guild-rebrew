// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _call_with_off
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkOfficeCandidate(void *obj)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = amt_ValidateOfficeCandidate((int *)((int)obj + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

int __cdecl amt_ValidateOfficeCandidate(int*);

/* Validation handler: delegates to amt_ValidateOfficeCandidate
 * to check if the entity at cmd+0x10 is eligible for an office.
 * Returns 1 if invalid, 0 if valid. */

// FUNCTION: SERVER 0x1000d020
int __cdecl cm_ChkOfficeCandidate(void* obj)
{
	int result;

	result = amt_ValidateOfficeCandidate((int*) ((int) obj + 0x10));
	return result == 0;
}
