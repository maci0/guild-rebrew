// FUNCTION: GOLD 0x0042beb0
// FUNCTION: GOLDTL 0x42abd0

extern int* g_6b7f50[16];
extern int g_6b7f90;

int __cdecl fcn_0042b120(int*);
int __cdecl fcn_0042b180(int*);
typedef int (__stdcall* fcn_0042abd0_f)(int, int, int);
typedef void (__stdcall* fcn_0042abd0_g)(void);
extern fcn_0042abd0_f g_662404;
extern fcn_0042abd0_g g_6623b8;

int __cdecl fcn_0042abd0(int* a1, int a2, int* a3)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = fcn_0042b120(a1)) >= 0 && (j = fcn_0042b180(a1)) >= 0) {
		*a3 = g_662404(*a1, a2, r);
		if (*a3 != 0) {
			g_6b7f50[i][j] = *a3;
			a1[5]++;
		} else {
			g_6623b8();
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
