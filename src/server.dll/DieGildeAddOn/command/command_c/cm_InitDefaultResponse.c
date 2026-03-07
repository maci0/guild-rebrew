
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 25B
 *    CFlags: 
 *    Symbol: _InitDefaultResponse
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_InitDefaultResponse(int param_1,char *param_2)
 * 
 * {
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\b';
 *     param_2[6] = '\0';
 *     param_2[7] = '\0';
 *     param_2[8] = '\0';
 *     param_2[9] = '\0';
 *   }
 *   return 0;
 * }
 */

// FUNCTION: SERVER 0x1000fbf0
int __cdecl cm_InitDefaultResponse(int param_1, char* param_2)
{
	if (param_2 != (char*) 0) {
		*param_2 = 1;
		param_2[1] = 8;
		*(int*) (param_2 + 6) = 0;
	}
	return 0;
}
