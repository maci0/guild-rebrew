// FUNCTION: GOLDTL 0x42aaa0
// SIZE: 46

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* fcn_0042aaa0_f)(int);

int __cdecl fcn_0042aaa0(int a1)
{
	int r = -1;

	if (*(int*) 0x6b7f90 != 0 && fcn_0042b1c0(a1) >= 0) {
		r = (*(fcn_0042aaa0_f*) 0x662450)(a1);
	}
	return r;
}
