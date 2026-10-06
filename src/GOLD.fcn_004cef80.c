// FUNCTION: GOLD 0x004cef80
// fcn_004cef80 — stride 0x14 reset over 0x9304c4..0x930604.

void __cdecl fcn_004cef80(void)
{
	int p;
	int z;
	int m;
	z = 0;
	m = -1;
	for (p = 0x9304c4; p < 0x930604; p += 0x14) {
		*(int*) p = z;
		*(int*) (p + 4) = m;
		*(int*) (p + 8) = z;
	}
}
