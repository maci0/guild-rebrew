

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int, int);

int __cdecl msx_RegisterSampleEosCallback(int sampleHandle, int callback)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			(*(f*) 0x00662400)(sampleHandle, callback);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
