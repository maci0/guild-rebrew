extern char g_100f8c0[];
extern char g_7766ba;
extern int g_77250c;
extern int g_100f1ec;
extern int g_100f1e8;


void __cdecl fcn_00472880(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

void __cdecl fcn_005337a0(void)
{
	if (g_100f8c0[0] != 0 && g_7766ba != 0) {
		fcn_00472880(0x54);
		fcn_0046bd20(g_100f1e8 - 0x36, g_100f1ec + 0x34, 0xa0, 0x60, g_77250c, g_100f8c0, 0xa8);
	}
}
