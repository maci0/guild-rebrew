extern int g_7725d0;
extern char* g_1015ea0;
extern int g_67d8e8;
extern int g_100f1d8;
extern int g_100f1e0;
extern int g_6772c0;
extern int g_6b5c84;

/* ADDRESS: GOLDTL 0x00473fe0 */
void __cdecl fcn_00473fe0(void)
{
	if ((*(char**)&g_7725d0) != 0) {
		((int*)g_1015ea0)[*(int*) ((*(char**)&g_7725d0) + 0x134) * 189 + 15] = 0;
		(*(char**)&g_7725d0) = 0;
		if (g_67d8e8 != -1) {
			g_67d8e8 = -1;
			g_6772c0 = g_100f1d8;
			g_6b5c84 = g_100f1e0;
		}
	}
}
