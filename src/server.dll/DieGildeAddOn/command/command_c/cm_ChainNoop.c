// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 3

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 3B
 *    CFlags: 
 *    Symbol: _chain_handler_noop
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChainNoop(void)
 * 
 * {
 *   return 0;
 * }
 */

/* Chain handler: no-op stub that always returns 0. */

// FUNCTION: SERVER 0x1000f3a0
int __cdecl cm_ChainNoop(void)
{
	return 0;
}
