

extern int g_772514;
extern int g_1015f78[];
extern int g_772544;
extern int g_772548;
extern int g_77254c;
extern int g_772550;
extern char* g_1015ea0;

void __cdecl fcn_00472880(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, int, int);
void __cdecl fcn_00472ea0(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl fcn_00472900(int, int);

void __cdecl fcn_005c9090(int text, int x, int y, int w, int font)
{
	int r;

	fcn_00472880(font);
	if (g_1015f78[g_772514 * 243] != 0) {
		fcn_0046bd20(x - w / 2, y, w, 0x140, 0, text, 8);
		fcn_00472ea0(g_77254c, g_772550, g_772544, g_772548);
	}
	r = fcn_0046fac0(x - w / 2, y, text, g_772514);
	*(int*) (g_1015ea0 + r * 756 + 0x6c) = 1;
	*(int*) (g_1015ea0 + r * 756 + 0x18) = w;
	fcn_00472900(r, font);
}
