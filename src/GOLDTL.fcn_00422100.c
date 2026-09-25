// GLOBAL: GOLD 0x6332a8
extern int g_6b7e88;
extern int g_6b7d7c;
// FUNCTION: GOLD 0x00425ce0
// SIZE: 62
// FUNCTION: GOLDTL 0x422100
// SIZE: 62

void __cdecl fcn_004232f0(void);
void __cdecl fcn_0041ddd0(int);
int __cdecl fcn_0042a2d0(int);

void __cdecl fcn_00422100(void)
{
	fcn_004232f0();
	if (g_6b7e88 != 0) {
		fcn_0041ddd0(g_6b7e88);
		g_6b7e88 = 0;
	}
	if (g_6b7d7c != 0) {
		fcn_0042a2d0(g_6b7d7c);
		g_6b7d7c = 0;
	}
}
