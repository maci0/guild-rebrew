
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

// FUNCTION: GOLDTL 0x4c75e0
// SIZE: 32
int __cdecl cm_MarkAndReturn(int cmd, char* result)
{
	(void) cmd;
	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
