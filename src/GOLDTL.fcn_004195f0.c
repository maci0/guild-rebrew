// FUNCTION: GOLDTL 0x4195f0
// SIZE: 76

extern int g_6b5d0c;
extern int g_6b5d10;
extern int g_6b5d14;
void __cdecl fcn_0041ddd0(int);

void __cdecl fcn_004195f0(void)
{
	if (g_6b5d0c != 0) {
		fcn_0041ddd0(g_6b5d0c);
		g_6b5d0c = 0;
		fcn_0041ddd0(g_6b5d10);
		g_6b5d10 = 0;
		fcn_0041ddd0(g_6b5d14);
		g_6b5d14 = 0;
		g_6b5d10 = 0;
		g_6b5d0c = 0;
	}
}
