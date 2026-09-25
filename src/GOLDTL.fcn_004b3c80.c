// FUNCTION: GOLD 0x004b3b10
// SIZE: 39
// FUNCTION: GOLDTL 0x4b3c80
// SIZE: 39

extern char g_10069a0[];

int __cdecl fcn_004b3c80(int a1)
{
	int p;

	for (p = (int) g_10069a0 + 4; p < (int) g_10069a0 + 0x1204; p += 0x24) {
		if (*(int*) (p - 4) != 0) {
			if (*(int*) p == a1) {
				return 1;
			}
		}
	}
	return 0;
}
