// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdValidateGeneric

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _CmdValidateGeneric
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdValidateGeneric(void *param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = ValidateCommand((char *)((int)param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl ValidateCommand(char*);

// FUNCTION: SERVER 0x1000d040
int __cdecl CmdValidateGeneric(void* param_1, char* param_2)
{
	int iVar1;

	iVar1 = ValidateCommand((char*) ((int) param_1 + 0x10));
	return iVar1 == 0;
}
