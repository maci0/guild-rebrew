typedef void (__stdcall* g_66244c_f)(int, int);
// GLOBAL: GOLDTL 0x6b7f94
extern int g_6b7f94;
// GLOBAL: GOLD 0x6333b4
extern int g_6b7f94;
// GLOBAL: GOLDTL 0x66244c
extern g_66244c_f g_66244c;
// GLOBAL: GOLD 0x5eb308
extern g_66244c_f g_66244c;
// FUNCTION: GOLD 0x0042bb40
// FUNCTION: GOLDTL 0x42a4d0

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
