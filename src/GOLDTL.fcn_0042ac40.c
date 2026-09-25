// FUNCTION: GOLDTL 0x42ac40
// SIZE: 95

extern char* g_6b7ed0[16];
extern int* g_6b7f50[16];

int __cdecl fcn_0042b280(int);
int __cdecl fcn_0042b200(int);
typedef void (__stdcall* fcn_0042ac40_f)(int);

int __cdecl fcn_0042ac40(int a1)
{
	int r = 0;
	int i;
	int j;

	if (*(int*) 0x6b7f90 != 0 && (i = fcn_0042b280(a1)) >= 0 && (j = fcn_0042b200(a1)) >= 0) {
		(*(fcn_0042ac40_f*) 0x662408)(a1);
		(*(int*) (g_6b7ed0[i] + 0x14))--;
		g_6b7f50[i][j] = r;
	} else {
		r = -1;
	}
	return r;
}
