extern int g_6b7f94;
int __cdecl fcn_0042b2c0(void);
typedef void (__stdcall* g_66244c_f)(int, int);
extern g_66244c_f g_66244c;

extern int g_6b7f90;

int __cdecl fcn_0042b2c0(void);
extern int* g_6b7f10[16];

int __cdecl fcn_0042b120(int*);
int __cdecl fcn_0042b140(int*);
__declspec(dllimport) int __stdcall AIL_allocate_sample_handle(int);

/* ADDRESS: GOLDTL 0x0042a4a0 */
int __cdecl fcn_0042a4a0(int* a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b2c0() != 0 || g_6b7f94 != 0) {
			*a1 = g_6b7f94;
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}

/* ADDRESS: GOLD 0x0042bb40 */
/* ADDRESS: GOLDTL 0x0042a4d0 */
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

/* ADDRESS: GOLD 0x0042bb80 */
/* ADDRESS: GOLDTL 0x0042a510 */
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
