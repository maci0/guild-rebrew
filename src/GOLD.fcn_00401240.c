// FUNCTION: GOLD 0x00401240
// fcn_00401240 — fcn_004011d0(x + i*4, x) for i in 0..2.

int __cdecl fcn_004011d0(int*, int*);

void __cdecl fcn_00401240(int u, int* x)
{
	(void) u;
	fcn_004011d0(x, x);
	fcn_004011d0(x + 1, x);
	fcn_004011d0(x + 2, x);
}
