// FUNCTION: GOLDTL 0x42a580
// SIZE: 67

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* fcn_0042a580_f)(int, int, int);
typedef void (__stdcall* fcn_0042a580_g)(void);

int __cdecl fcn_0042a580(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			if ((*(fcn_0042a580_f*) 0x66239c)(a1, a2, 0) == 0) {
				r = -1;
			}
			(*(fcn_0042a580_g*) 0x6623b8)();
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
