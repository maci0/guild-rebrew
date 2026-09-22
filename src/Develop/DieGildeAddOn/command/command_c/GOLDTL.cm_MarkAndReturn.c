
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

// FUNCTION: GOLDTL 0x4959f0
// SIZE: 32
/* TL build differs from the server twin (SERVER 0x1000d330, 14B): the client
 * passes an extra arg and the body tests both — `if (a) return 0;
 * return b == 0`. Shared name, per-build body: this file carries the GOLDTL
 * marker only. */
// BLOCKER: none — implemented, pending test promotion
int __cdecl cm_MarkAndReturn(int cmd, int dummy, char* result)
{
	if (cmd != 0) {
		return 0;
	}
	return result == (char*) 0x0;
}
