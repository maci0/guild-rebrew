extern char g_7e5fc0[];
extern int g_7e46ac;
extern float g_67d368;
extern int g_1015eac;
extern int g_77250c;
extern int g_6a251c;
extern int g_6b7fac;



void __cdecl fcn_00472880(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

void __cdecl fcn_005337f0(void)
{
	int x;
	int y;

	if (g_7e5fc0[0] != 0) {
		fcn_00472880(0x53);
		if (g_7e46ac & 0x8000) {
			x = g_1015eac - 0x12c;
			y = (int) (g_67d368 * 505.0f);
		} else {
			x = g_1015eac - 0x12c;
			y = (int) (g_67d368 * 575.0f);
		}
		fcn_0046bd20(x, y, 0x258, 0x18, g_77250c, g_7e5fc0, 0x28);
		if ((*(unsigned int*)&g_6b7fac) >= g_6a251c + 0x15e) {
			g_7e5fc0[0] = 0;
		}
	}
}
