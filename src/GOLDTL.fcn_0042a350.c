// FUNCTION: GOLDTL 0x42a350
// SIZE: 61

int __cdecl fcn_0042a2d0(int);

int __cdecl fcn_0042a350(void)
{
	int r = 0;
	int a;

	if (*(int*) 0x6b7f90 != 0) {
		for (a = 0x6b7ed0; a < 0x6b7f10; a += 4) {
			if (*(int*) a != 0 && fcn_0042a2d0(*(int*) a) == -1) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
