// FUNCTION: GOLDTL 0x411390
// SIZE: 64

typedef int (__stdcall* fcn_00411390_fn)(int, int, int, int, int*, int*);

int __cdecl fcn_00411390(int a1, int a2, int* a3)
{
	int local;

	local = 4;
	if ((*(fcn_00411390_fn*) 0x662004)(a1, a2, 0, 0, &a2, &local) == 0) {
		*a3 = a2;
		return 1;
	}
	return 0;
}
