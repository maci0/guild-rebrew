// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 6
// CFLAGS: /O2 /Gd
// SYMBOL: _RejectCommand

/*
 * Ghidra decompilation reference:
 * /+ WARNING: Unknown calling convention -- yet parameter storage is locked * / * / * [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 6B
 *    CFlags: 
 *    Symbol: _RejectCommand
 *    Files: DieGildeAddOn/command/command.c * /
 * 
 * int RejectCommand(void)
 * 
 * {
 *   return 1;
 * }
 */

// FUNCTION: SERVER 0x1000d340
int __cdecl RejectCommand(void)
{
	return 1;
}
