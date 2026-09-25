extern int g_7e1d40;

// FUNCTION: GOLDTL 0x53f630
// SIZE: 108

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_0046ac30(void);

void __cdecl fcn_0053f630(int a, int pct)
{
	int t;

	if (g_7e1d40 != -1) {
		fcn_004727a0(g_7e1d40, 0);
		fcn_004727a0(g_7e1d40, 1);
		t = fcn_00472250(g_7e1d40, 1, 0);
		fcn_00472380(t, 0, 0x246, pct * 0x246 / 100);
		fcn_0046ac30();
	}
}
