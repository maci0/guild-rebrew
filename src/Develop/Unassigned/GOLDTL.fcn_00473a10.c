extern int g_100f1e8;
extern int g_100f1ec;
extern char* g_7725c0;
extern int g_14ce8d0;
extern int g_77250c;
extern char s_67d5ec[];

int __cdecl fcn_00465950(const char* name);
char* __cdecl fcn_00466190(int idx);
void __cdecl fcn_00473800(int a, int x, int y, int w, int h);

/* ADDRESS: GOLDTL 0x00473a10 */
int __cdecl fcn_00473a10(int x, int y)
{
	int px;
	int py;
	int a;
	int b;

	px = g_100f1e8 + x;
	py = g_100f1ec + y;
	a = 6;
	b = 6;
	if (!g_7725c0) {
		g_7725c0 = fcn_00466190(fcn_00465950(s_67d5ec));
	}
	if (g_14ce8d0) {
		px--;
		py++;
		a = 7;
		b = 5;
	}
	fcn_00473800(g_77250c, px, py, a, b);
	return 1;
}
