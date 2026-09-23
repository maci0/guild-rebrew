// FUNCTION: GOLD 0x00440140
// SIZE: 47
// fcn_00440140 — a[0x1c70]|=1; fill 8x8 block at a+0x13f stride 0x64 with 0xff.

void __cdecl fcn_00440140(char* a)
{
	int r;
	int c;
	a[0x1c70] |= 1;
	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			*(char*) (a + 0x13f + r * 0x64 + c) = 0xff;
		}
	}
}
