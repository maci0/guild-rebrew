// FUNCTION: GOLDTL 0x42a3d0
// SIZE: 61

int __cdecl fcn_0042a390(int);

int __cdecl fcn_0042a3d0(void)
{
	int r = 0;
	int a;

	if (*(int*) 0x6b7f90 != 0) {
		for (a = 0x6b7ed0; a < 0x6b7f10; a += 4) {
			if (*(int*) a != 0 && fcn_0042a390(*(int*) a) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
