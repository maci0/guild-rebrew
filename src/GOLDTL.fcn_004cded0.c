// GLOBAL: GOLDTL 0x9baae0
extern char g_9baae0[];
// GLOBAL: GOLD 0x9364e0
extern char g_9baae0[];
// FUNCTION: GOLD 0x004cd350
// SIZE: 46
// FUNCTION: GOLDTL 0x4cded0
// SIZE: 46

char* __cdecl fcn_004cded0(void)
{
	int i;
	int a;

	for (i = 0, a = (int) g_9baae0; a < (int) g_9baae0 + 0x2b8; a += 0x57, i++) {
		if (*(int*) a == 0) {
			return (char*) ((int) g_9baae0 + i * 87);
		}
	}
	return 0;
}
