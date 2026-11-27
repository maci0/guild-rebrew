extern int g_6b7f94;
int __cdecl msx_CountActiveWaveDrivers(void);
typedef void (__stdcall* g_66244c_f)(int, int);
extern g_66244c_f g_66244c;

extern int g_6b7f90;

int __cdecl msx_CountActiveWaveDrivers(void);
extern int* g_6b7f10[16];

int __cdecl msx_FindWaveDriverIndex(int*);
int __cdecl msx_FindFreeSampleSlot(int*);
__declspec(dllimport) int __stdcall AIL_allocate_sample_handle(int);

/* ADDRESS: GOLDTL 0x0042a4a0 */
int __cdecl msx_GetSampleHandleLimit(int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_CountActiveWaveDrivers() != 0 || g_6b7f94 != 0) {
			*out = g_6b7f94;
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

	if (g_6b7f90 != 0) {
		if (msx_CountActiveWaveDrivers() <= 1) {
			g_6b7f94 = value;
			g_66244c(1, value);
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

	if (g_6b7f90 != 0 && (i = msx_FindWaveDriverIndex(device)) >= 0 && (j = msx_FindFreeSampleSlot(device)) >= 0 &&
	    (*outHandle = AIL_allocate_sample_handle(*device)) != 0) {
		device[5]++;
		g_6b7f10[i][j] = *outHandle;
	} else {
		r = -1;
	}
	return r;
}
