// FUNCTION: SERVER 0x1000fbd0
// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _cond_write

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _cond_write
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cond_write(void *obj,char *buf)
 * 
 * {
 *   if (buf != (char *)0x0) {
 *     *buf = '\x01';
 *     buf[1] = '\0';
 *     buf[6] = '\0';
 *     buf[7] = '\0';
 *     buf[8] = '\0';
 *     buf[9] = '\0';
 *   }
 *   return 0;
 * }
 */

int __cdecl cond_write(void* obj, char* buf)
{
	if (buf != (char*) 0) {
		*buf = 1;
		buf[1] = 0;
		*(int*) (buf + 6) = 0;
	}
	return 0;
}
