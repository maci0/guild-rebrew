extern int g_773de4;
extern int g_7f3e20[];
// FUNCTION: GOLDTL 0x00516000
// SIZE: 59

void __cdecl fcn_004237f0(int, int);

void __cdecl fcn_00516000(void)
{
	int i;

	for (i = 0; i < g_773de4; i++) {
		fcn_004237f0(g_7f3e20[i], 1);
		g_7f3e20[i] = 0;
	}
	g_773de4 = 0;
}
