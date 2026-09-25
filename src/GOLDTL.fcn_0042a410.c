// FUNCTION: GOLDTL 0x42a410
// SIZE: 70

int __cdecl fcn_0042b120(int);
typedef int (__stdcall* fcn_0042a410_g)(int);
typedef void (__stdcall* fcn_0042a410_f)(int, unsigned int, int*, int);

void __cdecl fcn_0042a410(int* a1, int a2, unsigned int a3)
{
	if (*(int*) 0x6b7f90 != 0 && a3 >= 0x400 && fcn_0042b120((int) a1) >= 0 && (*(fcn_0042a410_g*) 0x662458)(*a1) == 0) {
		(*(fcn_0042a410_f*) 0x6622dc)(a2, a3, a1, 0);
	}
}
