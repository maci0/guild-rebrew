typedef void (__stdcall* g_662408_f)(int);
extern int* g_6b7f50[16];
extern int* g_6b7f50[16];
extern g_662408_f g_662408;
extern g_662408_f g_662408;



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
