extern int g_6b7d7c;
// FUNCTION: GOLD 0x00427290
// SIZE: 82
// FUNCTION: GOLDTL 0x4237f0
// SIZE: 82

extern volatile int g_6b7fac;
int __cdecl fcn_0042a880(int);

void __cdecl fcn_004237f0(int* p, int a2)
{
	if (g_6b7d7c != 0 && p != 0) {
		if (a2 != 0) {
			p[5] |= 2;
			p[4] = (g_6b7fac * 2 + g_6b7fac) * 4 + g_6b7fac;
			return;
		}
		fcn_0042a880(p[0]);
		p[5] |= 8;
	}
}
