

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetSamplePosition(int sampleHandle, int* out)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			*out = (*(f*) 0x006623f8)(sampleHandle);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
