/* ADDRESS: GOLDTL 0x006b7f90 */
extern int g_6b7f90;
/* ADDRESS: GOLD 0x006333b0 */
extern int g_6b7f90;
/* ADDRESS: GOLDTL 0x006b7ed0 */
extern int* g_6b7ed0[16];
/* ADDRESS: GOLD 0x006332f0 */
extern int* g_6b7ed0[16];



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
