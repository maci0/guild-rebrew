

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* AIL_SET_SAMPLE_FILE_FN)(int, int, int);
typedef void (__stdcall* AIL_LAST_ERROR_FN)(void);

int __cdecl msx_SetSampleFile(int sampleHandle, int fileData)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			if ((*(AIL_SET_SAMPLE_FILE_FN*) 0x66239c)(sampleHandle, fileData, 0) == 0) {
				result = -1;
			}
			(*(AIL_LAST_ERROR_FN*) 0x6623b8)();
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
