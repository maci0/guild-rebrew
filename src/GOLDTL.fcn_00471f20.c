extern char* g_1015ea0;
extern char g_1015f40[];
extern char g_1038140[];
extern int g_772534;

// FUNCTION: GOLDTL 0x471f20
// SIZE: 94
char* __cdecl fcn_00471f20(int j, int k)
{
	char* m;

	m = g_1015f40 + ((int*) (g_1038140 + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return g_1015ea0 + (*(int**) (m + 0x28))[j] * 0x2f4;
}
