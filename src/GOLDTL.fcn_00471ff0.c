extern char g_1015f40[];
extern char g_1038140[];
extern int g_772534;

int __cdecl fcn_00471f80(int id);

// FUNCTION: GOLDTL 0x471ff0
// SIZE: 84
int __cdecl fcn_00471ff0(int j, int k)
{
	char* m;

	m = g_1015f40 + ((int*) (g_1038140 + g_772534 * 0x2bc + 4))[k] * 0x3cc;
	if (j > *(int*) (m + 0x2c)) {
		return 0;
	}
	return fcn_00471f80((*(int**) (m + 0x28))[j]);
}
