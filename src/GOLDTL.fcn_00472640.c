extern char* g_1015ea0;

// FUNCTION: GOLDTL 0x472640
void __cdecl fcn_00472640(int i, int flag)
{
	int v;

	if (i != -1) {
		v = flag == 0;
		*(int*) (g_1015ea0 + i * 0x2f4 + 0x4c) = v;
		*(int*) (g_1015ea0 + i * 0x2f4 + 0x60) = v;
	}
}
