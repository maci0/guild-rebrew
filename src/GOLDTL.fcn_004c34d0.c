// FUNCTION: GOLDTL 0x4c34d0
// SIZE: 101

extern int g_772e6c;
extern int g_772e70;
extern int g_772e74;
extern int g_772e7c;

void __cdecl fcn_004230e0(int);

void __cdecl fcn_004c34d0(void)
{
	if (g_772e6c != 0) {
		fcn_004230e0(g_772e6c);
		g_772e6c = 0;
	}
	if (g_772e70 != 0) {
		fcn_004230e0(g_772e70);
		g_772e70 = 0;
	}
	if (g_772e74 != 0) {
		fcn_004230e0(g_772e74);
		g_772e74 = 0;
	}
	if (g_772e7c != 0) {
		fcn_004230e0(g_772e7c);
		g_772e7c = 0;
	}
}
