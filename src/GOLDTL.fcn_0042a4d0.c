typedef void (__stdcall* g_66244c_f)(int, int);
/* ADDRESS: GOLDTL 0x006b7f94 */
extern int g_6b7f94;
/* ADDRESS: GOLD 0x006333b4 */
extern int g_6b7f94;
/* ADDRESS: GOLDTL 0x0066244c */
extern g_66244c_f g_66244c;
/* ADDRESS: GOLD 0x005eb308 */
extern g_66244c_f g_66244c;



extern int g_6b7f90;

int __cdecl fcn_0042b2c0(void);

int __cdecl fcn_0042a4d0(int a1)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		if (fcn_0042b2c0() <= 1) {
			g_6b7f94 = a1;
			g_66244c(1, a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
