// FUNCTION: GOLDTL 0x411350

typedef int (__stdcall* fcn_00411350_fn)(int, int, int, int, int*, int*);

int __cdecl fcn_00411350(int a1, int a2)
{
	int local;

	local = 4;
	return (*(fcn_00411350_fn*) 0x662004)(a1, a2, 0, 0, &a2, &local) == 0 ? a2 : 0;
}
