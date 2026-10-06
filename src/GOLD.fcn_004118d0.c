// FUNCTION: GOLD 0x004118d0
// fcn_004118d0 — if(!f(a,a)){ [0x6310ec]=a; return 0; } return 1. (a=param2)

int __cdecl fcn_005eab80(int, int);

int __cdecl fcn_004118d0(int u, int a)
{
	(void) u;
	if (fcn_005eab80(a, a) != 0) {
		return 1;
	}
	*(int*) 0x6310ec = a;
	return 0;
}
