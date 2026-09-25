// GLOBAL: GOLDTL 0x1052c60
extern int g_1052c60[0x60];
// GLOBAL: GOLD 0xfe7aa0
extern int g_1052c60[0x60];
// FUNCTION: GOLD 0x0042e9d0
// SIZE: 49
// FUNCTION: GOLDTL 0x42def0
// SIZE: 49
int __cdecl fcn_0042def0(int a1)
{
	int i;
	int a;

	for (i = 0, a = (int) g_1052c60; a < (int) (g_1052c60 + 0x60); a += 0xc, i++) {
		if (*(int*) a == a1) {
			g_1052c60[i * 3] = 0;
			return 1;
		}
	}
	return 0;
}
