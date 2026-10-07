// FUNCTION: GOLD 0x0040edc0
// fcn_0040edc0 — if(fcn_004225e0(*a)){ fcn_00455750(*a); return 0; } log(0x5f2908); return 0.

int __cdecl fcn_004225e0(int);
int __cdecl fcn_00455750(int);
int __cdecl fcn_004273d0(int, int, int);

int __cdecl fcn_0040edc0(int u, void* a)
{
	int e;
	e = *(int*) a;
	if (fcn_004225e0(e) != 0) {
		fcn_00455750(e);
		return 0;
	}
	fcn_004273d0(*(int*) 0x6332b8, *(int*) (*(int*) 0x6332b8 + 0x118), 0x5f2908);
	return 0;
}
