

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int, int);

int __cdecl fcn_0042ab90(int a1, int a2)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x00662400)(a1, a2);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
