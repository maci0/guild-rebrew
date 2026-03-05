// FUNCTION: SERVER 0x1000f3a0
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 3
// CFLAGS: /O2 /Gd
// SYMBOL: _chain_handler_noop


/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 3B
 *    CFlags: 
 *    Symbol: _chain_handler_noop
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl chain_handler_noop(void)
 * 
 * {
 *   return 0;
 * }
 */

int __cdecl chain_handler_noop(void)
{
    return 0;
}
