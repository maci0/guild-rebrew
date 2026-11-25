extern int d2_MouseRightBoundary, d2_MouseBottomBoundary, g_6b5c80, d2_MouseTopBoundary;
/* ADDRESS: GOLDTL 0x004127a0 */
void __cdecl fcn_004127a0(int save)
{
	int a;
	int b;
	int c;

	if (save == 0) {
		a = d2_MouseRightBoundary;
		b = d2_MouseBottomBoundary;
		c = g_6b5c80;
		*(int*) 0x6b5c64 = a;
		*(int*) 0x6b5c6c = b;
		*(int*) 0x6b5c70 = d2_MouseTopBoundary;
		d2_MouseRightBoundary = 0x7d00;
		d2_MouseBottomBoundary = 0x7d00;
		*(int*) 0x6b5c74 = c;
		d2_MouseTopBoundary = (int) 0xffff8300;
		g_6b5c80 = (int) 0xffff8300;
	} else {
		c = *(int*) 0x6b5c74;
		a = *(int*) 0x6b5c64;
		b = *(int*) 0x6b5c6c;
		d2_MouseRightBoundary = a;
		d2_MouseBottomBoundary = b;
		d2_MouseTopBoundary = *(int*) 0x6b5c70;
		g_6b5c80 = c;
	}
}
