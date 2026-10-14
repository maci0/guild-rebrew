extern char g_100f8c0[];
extern int g_67d8dc;
extern int g_77250c;
extern int g_100f1e8;
extern int g_100f1ec;

void __cdecl fcn_00472880(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00475240 */

void __cdecl fcn_00475240(int a)
{
	if (g_100f8c0[0] != 0 && g_67d8dc != 0) {
		fcn_00472880(a);
		fcn_0046bd20(g_100f1e8 - 0x36, g_100f1ec + 0x34, 0xa0, 0x60, g_77250c, g_100f8c0, 0xa8);
	}
}
