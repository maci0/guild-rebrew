extern int g_7749c8;

// FUNCTION: GOLD 0x00537dc0
// SIZE: 113
// FUNCTION: GOLDTL 0x53f6a0
// SIZE: 113

void __cdecl fcn_0053f630(int, int);

void __cdecl fcn_0053f6a0(int mode, int a, int b)
{
	int v;

	if (mode == 0) {
		fcn_0053f630(0, a * 70 / (b * 2) + 10);
	} else if (mode == 1) {
		v = a * 70 / (b * 2) + 0x2d;
		if (v != g_7749c8) {
			g_7749c8 = v;
			fcn_0053f630(0, v);
		}
	}
}
