extern unsigned char g_6a375c;
extern int g_14cbca0;
extern unsigned int g_14cbcb4;
extern unsigned int g_774948;

int __cdecl fcn_0047d220(char* a);

/* Wall: the reference keeps p in ecx across the fcn_0047d220 call and reads
 * [ecx+4] after it; no conforming C compiler may assume a call preserves ecx,
 * so the first block cannot be reproduced from C. The body matches the guard,
 * the modulo gates and both comparisons. The 96-byte extent also includes the
 * 10 nop bytes after the 86-byte body. */
/* ADDRESS: GOLDTL 0x0047d240 */
int __cdecl fcn_0047d240(char* p)
{
	if (fcn_0047d220(p) == 0) {
		return 0;
	}
	if (g_6a375c != 0) {
		if (g_14cbca0 != -1) {
			if (*(unsigned int*) (p + 4) % g_6a375c != g_14cbcb4) {
				return 0;
			}
		} else {
			if (*(unsigned int*) (p + 4) % g_6a375c != g_774948) {
				return 0;
			}
		}
	}
	return 1;
}
