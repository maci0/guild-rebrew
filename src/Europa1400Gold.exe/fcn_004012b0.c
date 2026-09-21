// FUNCTION: GOLD 0x004012b0
// SIZE: 45
// fcn_004012b0 — fcn_00401320(x, *x); fcn_00401320(x, x[1]); fcn_00401320(x, x[2]).

int __cdecl fcn_00401320(void*, int);

void __cdecl fcn_004012b0(int u1, int u2, int* x)
{
	(void) u1; (void) u2;
	fcn_00401320(x, x[0]);
	fcn_00401320(x, x[1]);
	fcn_00401320(x, x[2]);
}
