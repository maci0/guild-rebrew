extern unsigned char g_6a375c;
extern int g_14cbca0;
extern unsigned int g_14cbcb4;
extern unsigned int g_774948;

int __cdecl fcn_0047dd60(char* a);

/* ADDRESS: GOLDTL 0x0047d240 */
/* The reference keeps p in ecx across the fcn_0047dd60 call and uses it
 * afterwards; no conforming compiler may do that, so this C form (p in a
 * callee-saved register after a reload) cannot reproduce the first block.
 * The 96-byte extent also includes the 10 nop bytes after the 86-byte body. */
int __cdecl fcn_0047d240(char* p)
{
	if (fcn_0047dd60(p) == 0) {
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
