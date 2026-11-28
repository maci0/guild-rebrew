typedef int (__stdcall* g_662398_f)(int, int, int, int, int);
extern g_662398_f msx_SetNamedSampleFileFn;
extern g_662398_f msx_SetNamedSampleFileFn;



extern int msx_Initialized;

int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl msx_SetSampleData(int sampleHandle, int fileExt, int data, int size)
{
	int r = 0;

	if (msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			if (msx_SetNamedSampleFileFn(sampleHandle, fileExt, data, size, 0) == 0) {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
