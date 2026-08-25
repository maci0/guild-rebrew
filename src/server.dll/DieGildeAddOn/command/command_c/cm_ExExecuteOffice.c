
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags:
 *    Symbol: _CmdExecuteOffice
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExExecuteOffice(void *param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *
 *   iVar1 = ExecuteOfficeAssignment((char *)((int)param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

int __cdecl ExecuteOfficeAssignment(char*);

/* Execution handler: executes an office action by delegating
 * to amt_SwapOfficeHolders with the payload at cmd+0x10.
 * Returns 1 if the swap failed, 0 on success. */

// FUNCTION: SERVER 0x1000f960
int __cdecl cm_ExExecuteOffice(void* cmd, char* result)
{
	int assignResult;

	(void) result;

	assignResult = ExecuteOfficeAssignment((char*) ((int) cmd + 0x10));
	return assignResult == 0;
}
