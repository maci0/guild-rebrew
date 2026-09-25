extern char g_1038140[];

// FUNCTION: GOLDTL 0x472830
// SIZE: 69
int __cdecl fcn_00472830(int k, int j)
{
	if (j > *(int*) (g_1038140 + k * 0x2bc + 0x184) || j < 0) {
		return -1;
	}
	return ((int*) (g_1038140 + k * 0x2bc + 4))[j];
}
