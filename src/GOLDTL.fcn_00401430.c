// FUNCTION: GOLD 0x00401340
// SIZE: 49
// FUNCTION: GOLDTL 0x401430
// SIZE: 49

void __cdecl fcn_00401360(int, int);
int __cdecl fcn_00430910(int, int, int, int);

int __cdecl fcn_00401430(int a1, int a2, int a3, int a4)
{
	fcn_00401360(a1, a3);
	fcn_00401360(a1, a2);
	return fcn_00430910(a4, a2, a3, a1);
}
