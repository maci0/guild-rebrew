// FUNCTION: GOLD 0x005286a0
// SIZE: 52
// fcn_005286a0 — if(fcn_005de800(a,0x624180)) push esi into a array.

int __cdecl fcn_005de800(void*, int);

void __cdecl fcn_005286a0(int* a, int esi)
{
	int n;
	if (fcn_005de800(a, 0x624180) == 0) {
		return;
	}
	n = a[0];
	a[n + 1] = esi;
	a[0] = n + 1;
}
