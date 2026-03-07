
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

// FUNCTION: SERVER 0x1000d330
int __cdecl cm_MarkAndReturn(int param_1, char* param_2)
{
	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
