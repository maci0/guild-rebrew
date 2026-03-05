// FUNCTION: SERVER 0x1000f960
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdExecuteOffice

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _CmdExecuteOffice
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdExecuteOffice(void *param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = ExecuteOfficeAssignment((char *)((int)param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl ExecuteOfficeAssignment(char*);

int __cdecl CmdExecuteOffice(void* param_1, char* param_2)
{
	int iVar1;

	iVar1 = ExecuteOfficeAssignment((char*) ((int) param_1 + 0x10));
	return iVar1 == 0;
}
