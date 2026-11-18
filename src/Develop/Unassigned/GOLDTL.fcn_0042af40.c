

int __cdecl fcn_0042b200(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042af40(int a1, int* out)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b200(a1) >= 0) {
			*out = (*(f*) 0x0066242c)(a1);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
