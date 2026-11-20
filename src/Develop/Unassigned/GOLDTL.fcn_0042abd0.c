


extern int* g_6b7f50[16];
extern int g_6b7f90;

int __cdecl msx_FindWaveDriverIndex(int*);
int __cdecl fcn_0042b180(int*);
typedef int (__stdcall* fcn_0042abd0_f)(int, int, int);
typedef void (__stdcall* fcn_0042abd0_g)(void);
extern fcn_0042abd0_f g_662404;
extern fcn_0042abd0_g g_6623b8;

int __cdecl fcn_0042abd0(int* device, int a2, int* outHandle)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = msx_FindWaveDriverIndex(device)) >= 0 && (j = fcn_0042b180(device)) >= 0) {
		*outHandle = g_662404(*device, a2, r);
		if (*outHandle != 0) {
			g_6b7f50[i][j] = *outHandle;
			device[5]++;
		} else {
			g_6623b8();
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
