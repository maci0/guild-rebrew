

int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* f)(int, int);

int __cdecl msx_SetSampleVolume(int sampleHandle, int volume)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			(*(f*) 0x6623dc)(sampleHandle, volume);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
