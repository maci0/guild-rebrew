extern int g_6a2bf8;
extern int g_6a2bfc;
extern int g_6a2c00;
extern char* g_77255c;
extern char* g_1015ea0;

// FUNCTION: GOLDTL 0x535630
// SIZE: 121

void __cdecl fcn_004727a0(int, int);

void __cdecl fcn_00535630(void)
{
	int v;

	if (g_6a2bf8 != -1) {
		fcn_004727a0(g_6a2bf8, 1);
		v = *(int*) (g_77255c + 0x258) / 6 % 12;
		if (v < 0) {
			v = 0;
		}
		*(int*) (g_1015ea0 + g_6a2bfc * 0x2f4 + 0x88) = v;
		*(int*) (g_1015ea0 + g_6a2c00 * 0x2f4 + 0x88) = v;
	}
}
