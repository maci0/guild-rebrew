// GLOBAL: GOLDTL 0x6b7f94
extern int g_6b7f94;
// GLOBAL: GOLD 0x6333b4
extern int g_6b7f94;
// GLOBAL: GOLDTL 0x66244c
extern void (__stdcall* g_66244c)(int, int);
// GLOBAL: GOLD 0x5eb308
extern void (__stdcall* g_66244c)(int, int);
// FUNCTION: GOLD 0x0042bb40
// SIZE: 49
// FUNCTION: GOLDTL 0x42a4d0
// SIZE: 49

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
