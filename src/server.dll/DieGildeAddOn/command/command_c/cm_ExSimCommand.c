// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _ExSimCommand
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExSimCommand(void *param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = amt_SwapOfficeHolders((int *)((int)param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl amt_SwapOfficeHolders(int*);

// FUNCTION: SERVER 0x10010080
int __cdecl cm_ExSimCommand(void* param_1, char* param_2)
{
	int swap_result;

	swap_result = amt_SwapOfficeHolders((int*) ((int) param_1 + 0x10));
	return (unsigned int) (swap_result == 0);
}
