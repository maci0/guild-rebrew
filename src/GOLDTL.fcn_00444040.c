extern int g_6b8484;
extern char* g_6b8478;
extern char* g_6b847c;
extern char* g_6b8480;
extern char g_6b8004;
extern char s_67a9ac[];
extern char s_67a9c4[];
extern char s_67a9bc[];
extern char s_67a9b4[];

char* __cdecl fcn_00439750(int kind, char* name);
void __cdecl fcn_00438ba0(char* o, float x, float y, float z);
void __cdecl fcn_00438d70(char* o, float x, float y, float z);
void __cdecl fcn_00439aa0(char* o);

// FUNCTION: GOLDTL 0x444040
// SIZE: 310
void __cdecl fcn_00444040(void)
{
	(*(char**)&g_6b8484) = fcn_00439750(3, s_67a9ac);
	fcn_00438ba0((*(char**)&g_6b8484), 0.0f, 0.0f, -256.0f);
	fcn_00438d70((*(char**)&g_6b8484), 0.0f, 0.0f, 0.0f);
	fcn_00439aa0((*(char**)&g_6b8484));
	if (g_6b8004 != 0) {
		g_6b8478 = fcn_00439750(3, s_67a9c4);
		fcn_00438ba0(g_6b8478, 0.0f, 256.0f, 0.0f);
		fcn_00438d70(g_6b8478, -1.5707964f, 0.0f, 0.0f);
		fcn_00439aa0(g_6b8478);
		g_6b8478[0x214] &= 0x7f;
		g_6b847c = fcn_00439750(3, s_67a9bc);
		fcn_00438ba0(g_6b847c, 0.0f, 0.0f, -256.0f);
		fcn_00438d70(g_6b847c, 0.0f, 0.0f, 0.0f);
		fcn_00439aa0(g_6b847c);
		g_6b847c[0x214] &= 0x7f;
		g_6b8480 = fcn_00439750(3, s_67a9b4);
		fcn_00438ba0(g_6b8480, 256.0f, 0.0f, 0.0f);
		fcn_00438d70(g_6b8480, 0.0f, 1.5707964f, 0.0f);
		fcn_00439aa0(g_6b8480);
		g_6b8480[0x214] &= 0x7f;
	}
}
