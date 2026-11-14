extern int g_6772bc, g_6772c0, g_6b5c80, g_6b5c84;
/* ADDRESS: GOLDTL 0x004127a0 */
void __cdecl fcn_004127a0(int save)
{
	int a;
	int b;
	int c;
	int d;

	if (save == 0) {
		a = g_6772bc;
		b = g_6772c0;
		c = g_6b5c80;
		*(int*) 0x6b5c64 = a;
		*(int*) 0x6b5c6c = b;
		*(int*) 0x6b5c70 = g_6b5c84;
		g_6772bc = 0x7d00;
		g_6772c0 = 0x7d00;
		*(int*) 0x6b5c74 = c;
		g_6b5c84 = (int) 0xffff8300;
		g_6b5c80 = (int) 0xffff8300;
	} else {
		c = *(int*) 0x6b5c74;
		a = *(int*) 0x6b5c64;
		b = *(int*) 0x6b5c6c;
		g_6772bc = a;
		d = *(int*) 0x6b5c70;
		g_6772c0 = b;
		g_6b5c84 = d;
		g_6b5c80 = c;
	}
}
