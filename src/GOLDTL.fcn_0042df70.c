// FUNCTION: GOLD 0x0042ea50
// FUNCTION: GOLDTL 0x42df70

extern int g_1052c60[0x60];

int __cdecl fcn_0042df70(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_1052c60; a < (int) (g_1052c60 + 0x60); a += 0xc, i++) {
		if (*(int*) a == a1) {
			return (g_1052c60 + 2)[i * 3] != 0;
		}
	}
	return 0;
}
