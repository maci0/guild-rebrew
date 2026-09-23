// GLOBAL: GOLDTL 0x6a2bf8
extern int g_6a2bf8;
// GLOBAL: GOLDTL 0x6a2bfc
extern int g_6a2bfc;
// GLOBAL: GOLDTL 0x6a2c00
extern int g_6a2c00;
// FUNCTION: GOLDTL 0x5355f0
// SIZE: 50

void __cdecl fcn_00471e30(int);

void __cdecl fcn_005355f0(void)
{
	if (g_6a2bf8 != -1) {
		fcn_00471e30(g_6a2bf8);
		g_6a2bf8 = -1;
		g_6a2bfc = -1;
		g_6a2c00 = -1;
	}
}
