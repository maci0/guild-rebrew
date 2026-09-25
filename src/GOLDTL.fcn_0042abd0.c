// FUNCTION: GOLDTL 0x42abd0
// SIZE: 112

extern int* g_6b7f50[16];

int __cdecl fcn_0042b120(int*);
int __cdecl fcn_0042b180(int*);
typedef int (__stdcall* fcn_0042abd0_f)(int, int, int);
typedef void (__stdcall* fcn_0042abd0_g)(void);

int __cdecl fcn_0042abd0(int* a1, int a2, int* a3)
{
	int r = 0;
	int i;
	int j;

	if (*(int*) 0x6b7f90 != 0 && (i = fcn_0042b120(a1)) >= 0 && (j = fcn_0042b180(a1)) >= 0) {
		*a3 = (*(fcn_0042abd0_f*) 0x662404)(*a1, a2, r);
		if (*a3 != 0) {
			g_6b7f50[i][j] = *a3;
			a1[5]++;
		} else {
			(*(fcn_0042abd0_g*) 0x6623b8)();
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
