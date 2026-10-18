
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 14B
 *    CFlags:
 *    Symbol: _MarkAndReturn
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_MarkAndReturn(int param_1,char *param_2)
 *
 * {
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

/* Inferred name: the independent TL method-start callback at 0x4959f0.
 * command.c owns the separate cm_MarkAndReturn dispatch handler. */

int __cdecl cm_TestCommandResult(int cmd, int dummy, char* result)
{
	if (cmd != 0) {
		return 0;
	}
	return result == (char*) 0x0;
}
