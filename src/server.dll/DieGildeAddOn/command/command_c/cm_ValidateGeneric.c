// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _CmdValidateGeneric
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ValidateGeneric(void *param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   
 *   iVar1 = amt_ValidateCommand((char *)((int)param_1 + 0x10));
 *   return (uint)(iVar1 == 0);
 * }
 */

extern int __cdecl amt_ValidateCommand(char*);

// FUNCTION: SERVER 0x1000d040
int __cdecl cm_ValidateGeneric(void* param_1, char* param_2)
{
	int validate_result;

	validate_result = amt_ValidateCommand((char*) ((int) param_1 + 0x10));
	return validate_result == 0;
}
