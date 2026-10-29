extern int g_6b5cbc;
extern int g_14ce8e8;
extern int g_774774;
extern int g_14ce8c0;
extern int g_14ce8c2;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_6772bc;
extern int g_6772c0;
extern int g_6772c4;
extern int g_774754;
extern int g_773e38;
extern int g_774758;
extern int g_773df8;
extern int g_773e00;
extern int g_773df0;
extern int g_773e34;
extern int g_77464c;

/* Client update/init routine: returns early once g_6b5cbc is set, then runs the
 * g_774774 coordinate-range init block (0x7d00 / -0x7d00 bounds copied through
 * g_6772bc/g_6772c0 and g_6b5c80/g_6b5c84) under the g_14ce8e8 gate. The
 * remaining 0x52c129-0x52c9a7 body (per-frame x87 transforms, the 0x451840 /
 * 0x438b40 / 0x509570 / 0x52ac60 calls and the fsin/fcos prediction path) is
 * not transcribed yet. */
/* ADDRESS: GOLDTL 0x0052c060 */
int __cdecl fcn_0052c060(void)
{
	if (g_6b5cbc != 0) {
		return 0;
	}
	if (g_14ce8e8 != 0) {
		if (g_774774 == 0) {
			g_774754 = (int) (short) g_14ce8c0;
			g_773e38 = (int) (short) g_14ce8c0;
			g_774758 = (int) (short) g_14ce8c2;
			g_773df8 = (int) (short) g_14ce8c2;
			g_773e00 = g_6772bc;
			g_773df0 = g_6772c0;
			g_773e34 = g_6b5c80;
			g_77464c = g_6b5c84;
			g_774774 = 1;
			g_6772c4 = 0;
			g_6772bc = 0x7d00;
			g_6772c0 = 0x7d00;
			g_6b5c80 = 0xffff8300;
			g_6b5c84 = 0xffff8300;
		}
	}
	return 0;
}
