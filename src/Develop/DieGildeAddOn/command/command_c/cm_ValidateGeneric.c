
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

int __cdecl amt_ValidateCommand(char*);

/* Validation handler: generic command validation by delegating
 * to amt_ValidateCommand with payload at cmd+0x10. Returns 1
 * if validation failed, 0 on success. */

// FUNCTION: SERVER 0x1000d040
int __cdecl cm_ValidateGeneric(void* cmd, char* result)
{
	int validate_result;

	(void) result;

	validate_result = amt_ValidateCommand((char*) ((int) cmd + 0x10));
	return validate_result == 0;
}
