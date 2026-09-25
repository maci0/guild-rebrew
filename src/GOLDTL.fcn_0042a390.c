typedef int (__stdcall* g_662454_f)(int);
// GLOBAL: GOLDTL 0x662454
extern g_662454_f g_662454;
// GLOBAL: GOLD 0x5eb310
extern g_662454_f g_662454;
// FUNCTION: GOLD 0x0042ba30
// SIZE: 54
// FUNCTION: GOLDTL 0x42a390
// SIZE: 54

extern int g_6b7f90;

int __cdecl fcn_0042b120(int);

int __cdecl fcn_0042a390(int* a1)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		if (fcn_0042b120((int) a1) >= 0) {
			if (g_662454(*a1) == 0) {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
