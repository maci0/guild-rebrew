// FUNCTION: GOLDTL 0x4edce0
// SIZE: 65

extern int g_772fd8;
extern int g_772fdc;
extern int g_772fe0;
extern int g_772fe4;

void __cdecl fcn_0041ddd0(int);

void __cdecl fcn_004edce0(void)
{
	if (g_772fdc != 0) {
		fcn_0041ddd0(g_772fdc);
		g_772fdc = 0;
	}
	if (g_772fe4 != 0) {
		fcn_0041ddd0(g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe0 = 0;
	g_772fd8 = 0;
}
