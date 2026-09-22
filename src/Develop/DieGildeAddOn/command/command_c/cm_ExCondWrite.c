
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: EXACT
 *    Origin: GAME
 *    Size: 22B
 *    CFlags:
 *    Symbol: _cond_write
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExCondWrite(void *obj,char *buf)
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

// FUNCTION: SERVER 0x1000fbd0
int __cdecl cm_ExCondWrite(void* obj, char* buf)
{
	if (buf != (char*) 0) {
		*buf = 1;
		buf[1] = 0;
		*(int*) (buf + 6) = 0;
	}
	return 0;
}
