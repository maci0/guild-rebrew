// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 22
// CFLAGS: /O2 /Gd
// SYMBOL: _cm_ExCondWrite2

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 22B
 *    CFlags: 
 *    Symbol: _cond_write2
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExCondWrite2(void *obj,char *buf)
 * 
 * {
 *   if (buf != (char *)0x0) {
 *     buf[1] = '\0';
 *     buf[6] = '\0';
 *     buf[7] = '\0';
 *     buf[8] = '\0';
 *     buf[9] = '\0';
 *     *buf = '\x01';
 *   }
 *   return 0;
 * }
 */

// FUNCTION: SERVER 0x1000ff10
int __cdecl cm_ExCondWrite2(void* obj, char* buf)
{
	if (buf != (char*) 0) {
		buf[1] = 0;
		*(int*) (buf + 6) = 0;
		*buf = 1;
	}
	return 0;
}
