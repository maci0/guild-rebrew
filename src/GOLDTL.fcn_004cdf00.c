// FUNCTION: GOLD 0x4cd380
// SIZE: 58
// FUNCTION: GOLDTL 0x4cdf00
// SIZE: 58

char* __cdecl fcn_004cded0(void);
extern char g_9baae0[];

char* __cdecl fcn_004cdf00(int a1)
{
	int i;
	int a;

	if (a1 == 0) {
		return 0;
	}
	for (i = 0, a = (int) g_9baae0; a < (int) (g_9baae0 + 0x2b8); a += 0x57, i++) {
		if (*(int*) a == a1) {
			return g_9baae0 + i * 87;
		}
	}
	return fcn_004cded0();
}
