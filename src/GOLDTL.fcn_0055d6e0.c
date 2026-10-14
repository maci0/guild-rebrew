extern int g_7e453c;
extern int g_7e4538;

/* ADDRESS: GOLD 0x00555510 */
/* ADDRESS: GOLDTL 0x0055d6e0 */

void __cdecl fcn_0055d6e0(char* a, char* b)
{
	char* d;

	d = *(char**) (b + 0x3b);
	if (((int*)g_7e453c) != 0 && *((int*)g_7e453c) > 0x64) {
		*(float*) (d + 0x1a0) = *(float*) (a + 0xc0) * 0.7;
	} else if (((int*)g_7e4538) != 0 && *((int*)g_7e4538) > 0xc8) {
		*(float*) (d + 0x1a0) = *(float*) (a + 0xc0) * 0.8;
	} else {
		*(float*) (d + 0x1a0) = *(float*) (a + 0xc0);
	}
	if (a[0xf1] == 2) {
		*(float*) (d + 0x1a0) = *(float*) (d + 0x1a0) * 0.8;
	}
}
