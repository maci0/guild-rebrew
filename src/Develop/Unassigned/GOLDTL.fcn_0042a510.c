


extern int* g_6b7f10[16];
extern int g_6b7f90;

int __cdecl fcn_0042b120(int*);
int __cdecl fcn_0042b140(int*);
__declspec(dllimport) int __stdcall AIL_allocate_sample_handle(int);

int __cdecl fcn_0042a510(int* a1, int* a2)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = fcn_0042b120(a1)) >= 0 && (j = fcn_0042b140(a1)) >= 0 &&
	    (*a2 = AIL_allocate_sample_handle(*a1)) != 0) {
		a1[5]++;
		g_6b7f10[i][j] = *a2;
	} else {
		r = -1;
	}
	return r;
}
