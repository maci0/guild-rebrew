extern char* g_6338c4;
extern char* g_6338b8;
extern char* g_6338bc;
extern char* g_6338c0;
extern char g_633438;
extern char s_5fbd8c[];
extern char s_5fbe80[];
extern char s_5fbe78[];
extern char s_5fbe70[];

char* __cdecl fcn_0043c570(int kind, char* name);
void __cdecl fcn_0043b7f0(char* o, float x, float y, float z);
void __cdecl fcn_0043b920(char* o, float x, float y, float z);
void __cdecl fcn_0043ca20(char* o);

// FUNCTION: GOLD 0x448910
void __cdecl fcn_00448910(void)
{
	g_6338c4 = fcn_0043c570(3, s_5fbd8c);
	fcn_0043b7f0(g_6338c4, 0.0f, 0.0f, -256.0f);
	fcn_0043b920(g_6338c4, 0.0f, 0.0f, 0.0f);
	fcn_0043ca20(g_6338c4);
	if (g_633438 != 0) {
		g_6338b8 = fcn_0043c570(3, s_5fbe80);
		fcn_0043b7f0(g_6338b8, 0.0f, 256.0f, 0.0f);
		fcn_0043b920(g_6338b8, -1.5707964f, 0.0f, 0.0f);
		fcn_0043ca20(g_6338b8);
		g_6338b8[0x211] &= ~2;
		g_6338bc = fcn_0043c570(3, s_5fbe78);
		fcn_0043b7f0(g_6338bc, 0.0f, 0.0f, -256.0f);
		fcn_0043b920(g_6338bc, 0.0f, 0.0f, 0.0f);
		fcn_0043ca20(g_6338bc);
		g_6338bc[0x211] &= ~2;
		g_6338c0 = fcn_0043c570(3, s_5fbe70);
		fcn_0043b7f0(g_6338c0, 256.0f, 0.0f, 0.0f);
		fcn_0043b920(g_6338c0, 0.0f, 1.5707964f, 0.0f);
		fcn_0043ca20(g_6338c0);
		g_6338c0[0x211] &= ~2;
	}
}
