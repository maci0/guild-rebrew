


extern int* msx_StreamHandles[16];
extern int msx_Initialized;

int __cdecl msx_FindWaveDriverIndex(int*);
int __cdecl msx_FindFreeStreamSlot(int*);
typedef int (__stdcall* AILOpenStreamFn)(int, int, int);
typedef void (__stdcall* AILLastErrorFn)(void);
extern AILOpenStreamFn g_662404;
extern AILLastErrorFn g_6623b8;

int __cdecl msx_OpenStream(int* device, int filename, int* outHandle)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0 && (i = msx_FindWaveDriverIndex(device)) >= 0 && (j = msx_FindFreeStreamSlot(device)) >= 0) {
		*outHandle = g_662404(*device, filename, r);
		if (*outHandle != 0) {
			msx_StreamHandles[i][j] = *outHandle;
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
