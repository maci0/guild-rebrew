extern char* g_1015ea0;
extern char g_102cbc4[];

// FUNCTION: GOLDTL 0x469540
// SIZE: 91
void __cdecl fcn_00469540(int g, int flag)
{
	int j;

	for (j = 0; j < *(int*) (g_102cbc4 + g * 0x8c); j++) {
		*(int*) (g_1015ea0 + ((int*) (g_102cbc4 + g * 0x8c + 8))[j] * 0x2f4 + 0x4c) = flag == 0;
	}
}
