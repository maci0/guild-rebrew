extern int msx_SampleHandleLimit;
int __cdecl msx_CountActiveWaveDrivers(void);
typedef void (__stdcall* g_66244c_f)(int, int);
extern g_66244c_f imp_AIL_set_preference;

extern int msx_Initialized;

int __cdecl msx_CountActiveWaveDrivers(void);
extern int* msx_SampleHandles[16];

int __cdecl msx_FindWaveDriverIndex(int*);
int __cdecl msx_FindFreeSampleSlot(int*);
__declspec(dllimport) int __stdcall AIL_allocate_sample_handle(int);

/* ADDRESS: GOLDTL 0x0042a4a0 */
int __cdecl msx_GetSampleHandleLimit(int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_CountActiveWaveDrivers() != 0 || msx_SampleHandleLimit != 0) {
			*out = msx_SampleHandleLimit;
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
int __cdecl msx_SetSampleHandleLimit(int value)
{
	int r = 0;

	if (msx_Initialized != 0) {
		if (msx_CountActiveWaveDrivers() <= 1) {
			msx_SampleHandleLimit = value;
			imp_AIL_set_preference(1, value);
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
int __cdecl msx_AllocateSampleHandle(int* device, int* outHandle)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0 && (i = msx_FindWaveDriverIndex(device)) >= 0 && (j = msx_FindFreeSampleSlot(device)) >= 0 &&
	    (*outHandle = AIL_allocate_sample_handle(*device)) != 0) {
		device[5]++;
		msx_SampleHandles[i][j] = *outHandle;
	} else {
		r = -1;
	}
	return r;
}
