// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22

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

// FUNCTION: SERVER 0x1000f960
int __cdecl cm_ExExecuteOffice(void* param_1, char* param_2)
{
	int assignResult;

	assignResult = ExecuteOfficeAssignment((char*) ((int) param_1 + 0x10));
	return assignResult == 0;
}
