typedef void (__stdcall* g_662408_f)(int);
// GLOBAL: GOLDTL 0x6b7f50
extern int* g_6b7f50[16];
// GLOBAL: GOLD 0x633370
extern int* g_6b7f50[16];
// GLOBAL: GOLDTL 0x662408
extern g_662408_f g_662408;
// GLOBAL: GOLD 0x5eb348
extern g_662408_f g_662408;
// FUNCTION: GOLD 0x0042bf20
// SIZE: 95
// FUNCTION: GOLDTL 0x42ac40
// SIZE: 95

extern int g_6b7f90;
extern int* g_6b7ed0[16];

int __cdecl fcn_0042b280(int);
int __cdecl fcn_0042b200(int);

int __cdecl fcn_0042ac40(int a1)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = fcn_0042b280(a1)) >= 0 && (j = fcn_0042b200(a1)) >= 0) {
		g_662408(a1);
		g_6b7ed0[i][5]--;
		g_6b7f50[i][j] = r;
	} else {
		r = -1;
	}
	return r;
}
