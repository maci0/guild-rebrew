typedef void (__stdcall* g_6623bc_f)(int);
// GLOBAL: GOLDTL 0x6b7f10
extern int* g_6b7f10[16];
// GLOBAL: GOLD 0x633330
extern int* g_6b7f10[16];
// GLOBAL: GOLDTL 0x6623bc
extern g_6623bc_f g_6623bc;
// GLOBAL: GOLD 0x5eb35c
extern g_6623bc_f g_6623bc;
// FUNCTION: GOLD 0x0042bc40
// FUNCTION: GOLDTL 0x42a6a0

extern int g_6b7f90;
extern int* g_6b7ed0[16];

int __cdecl fcn_0042b240(int);
int __cdecl fcn_0042b1c0(int);

int __cdecl fcn_0042a6a0(int a1)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = fcn_0042b240(a1)) >= 0 && (j = fcn_0042b1c0(a1)) >= 0) {
		g_6623bc(a1);
		g_6b7f10[i][j] = r;
		g_6b7ed0[i][5]--;
	} else {
		r = -1;
	}
	return r;
}
