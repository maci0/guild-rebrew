// FUNCTION: GOLDTL 0x4b3c50
// SIZE: 46

char* __cdecl fcn_004b3c50(int a1)
{
	int i;
	int p;

	for (i = 0, p = 0x680bd0; p < 0x681110; p += 0x1c, i++) {
		if (*(int*) p == a1) {
			return (char*) (0x680bd0 + i * 0x1c);
		}
	}
	return 0;
}
