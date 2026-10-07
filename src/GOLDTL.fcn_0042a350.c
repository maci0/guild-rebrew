// GLOBAL: GOLDTL 0x6b7f90
extern int g_6b7f90;
// GLOBAL: GOLD 0x6333b0
extern int g_6b7f90;
// GLOBAL: GOLDTL 0x6b7ed0
extern int* g_6b7ed0[16];
// GLOBAL: GOLD 0x6332f0
extern int* g_6b7ed0[16];
// FUNCTION: GOLD 0x0042b9f0
// FUNCTION: GOLDTL 0x42a350

int __cdecl fcn_0042a2d0(int);

int __cdecl fcn_0042a350(void)
{
	int r = 0;
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) g_6b7ed0; a < (int) (g_6b7ed0 + 16); a += 4) {
			if (*(int*) a != 0 && fcn_0042a2d0(*(int*) a) == -1) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
