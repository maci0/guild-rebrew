// FUNCTION: GOLD 0x004fe1e0
// fcn_004fe1e0 — a[4]=b; a[0xa]=c; a[6]=d.

void __cdecl fcn_004fe1e0(char* a, char b, int c, int d)
{
	*(short*) (a + 4) = (short) (unsigned char) b;
	*(int*) (a + 0xa) = c & 0xff;
	*(int*) (a + 6) = d & 0xff;
}
