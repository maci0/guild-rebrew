typedef int (__stdcall* g_662454_f)(int);
/* ADDRESS: GOLDTL 0x00662454 */
extern g_662454_f g_662454;
/* ADDRESS: GOLD 0x005eb310 */
extern g_662454_f g_662454;



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
