// FUNCTION: GOLDTL 0x42af10
// SIZE: 41

int __cdecl fcn_0042b200(int);
typedef int (__stdcall* fcn_0042af10_f)(int);

int __cdecl fcn_0042af10(int a1)
{
	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b200(a1) >= 0) {
			return (*(fcn_0042af10_f*) 0x662428)(a1);
		}
	}
	return -1;
}
