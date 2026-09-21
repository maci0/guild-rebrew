// FUNCTION: GOLD 0x00417dd0
// SIZE: 48
// fcn_00417dd0 — if(a){ fcn_00417cf0(a, 0, 0, 0); a[0x50]=b; }.

int __cdecl fcn_00417cf0(void*, int, int, int);

void __cdecl fcn_00417dd0(int u, char* a, char* b)
{
	(void) u;
	if (a != 0) {
		fcn_00417cf0(a, 0, 0, 0);
		*(char**) (a + 0x50) = b;
	}
}
