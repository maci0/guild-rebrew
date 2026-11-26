


extern int* g_6b7f50[16];
extern int g_6b7f90;

int __cdecl msx_FindWaveDriverIndex(int*);
int __cdecl fcn_0042b180(int*);
typedef int (__stdcall* AILOpenStreamFn)(int, int, int);
typedef void (__stdcall* AILLastErrorFn)(void);
extern AILOpenStreamFn g_662404;
extern AILLastErrorFn g_6623b8;

int __cdecl msx_OpenStream(int* device, int filename, int* outHandle)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = msx_FindWaveDriverIndex(device)) >= 0 && (j = fcn_0042b180(device)) >= 0) {
		*outHandle = g_662404(*device, filename, r);
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
