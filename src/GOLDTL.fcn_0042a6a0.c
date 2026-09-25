// FUNCTION: GOLDTL 0x42a6a0
// SIZE: 95

extern char* g_6b7ed0[16];
extern int* g_6b7f10[16];

int __cdecl fcn_0042b240(int);
int __cdecl fcn_0042b1c0(int);
typedef void (__stdcall* fcn_0042a6a0_f)(int);

int __cdecl fcn_0042a6a0(int a1)
{
	int r = 0;
	int i;
	int j;

	if (*(int*) 0x6b7f90 != 0 && (i = fcn_0042b240(a1)) >= 0 && (j = fcn_0042b1c0(a1)) >= 0) {
		(*(fcn_0042a6a0_f*) 0x6623bc)(a1);
		g_6b7f10[i][j] = r;
		(*(int*) (g_6b7ed0[i] + 0x14))--;
	} else {
		r = -1;
	}
	return r;
}
