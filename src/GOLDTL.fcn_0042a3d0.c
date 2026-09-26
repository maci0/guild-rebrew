// FUNCTION: GOLD 0x0042ba70
// SIZE: 61
// FUNCTION: GOLDTL 0x42a3d0
// SIZE: 61

extern int g_6b7f90;
extern int* g_6b7ed0[16];

int __cdecl fcn_0042a390(int);

int __cdecl fcn_0042a3d0(void)
{
	int r = 0;
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) g_6b7ed0; a < (int) (g_6b7ed0 + 16); a += 4) {
			if (*(int*) a != 0 && fcn_0042a390(*(int*) a) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
