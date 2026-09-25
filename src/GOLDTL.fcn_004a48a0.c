int __cdecl fcn_0050cf50(int, int);

// FUNCTION: GOLD 0x4a4e30
// SIZE: 64
// FUNCTION: GOLDTL 0x4a48a0
// SIZE: 63

int __cdecl fcn_004a48a0(int a, int kind)
{
	int n;

	a = fcn_0050cf50(a, 100);
	n = (int) (a * 0.005f);
	if (kind == 50)
		n *= 4;
	else if (kind == 30)
		n *= 2;
	else if (kind != 10)
		n = 0;
	return n;
}
