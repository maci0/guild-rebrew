// FUNCTION: GOLD 0x0053f1e0
// SIZE: 38
// FUNCTION: GOLDTL 0x00546fb0
// SIZE: 38

extern char g_7dcae0[];

int __cdecl fcn_00546fb0(int k)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < 0x100; i++) {
		if (*(int*) (g_7dcae0 + i * 0x50 + 8) != 0 && *(int*) (g_7dcae0 + i * 0x50 + 4) == k) {
			sum += *(int*) (g_7dcae0 + i * 0x50 + 8);
		}
	}
	return sum;
}
