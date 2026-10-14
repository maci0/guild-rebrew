extern int g_6a2bf8;
extern int g_6a2bfc;
extern int g_6a2c00;
extern int g_772514;



int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_0046f740(int, int, int, int);

int __cdecl fcn_00535570(void)
{
	if (g_6a2bf8 != -1) {
		return -1;
	}
	g_6a2bf8 = fcn_00470820(0, 0, "misc\\scroll_perga");
	fcn_00471b60(g_6a2bf8);
	if (g_6a2bf8 == -1) {
		return g_6a2bf8;
	}
	fcn_004727a0(g_6a2bf8, 0);
	g_6a2bfc = fcn_0046f740(0, 0, 0x6e0, g_772514);
	g_6a2c00 = fcn_0046f740(0, 0x1d1, 0x6e0, g_772514);
	return g_6a2bf8;
}
