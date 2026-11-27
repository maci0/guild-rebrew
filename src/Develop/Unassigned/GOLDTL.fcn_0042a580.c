

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* fcn_0042a580_f)(int, int, int);
typedef void (__stdcall* AIL_LAST_ERROR_FN)(void);

int __cdecl msx_SetSampleFile(int a1, int a2)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			if ((*(fcn_0042a580_f*) 0x66239c)(a1, a2, 0) == 0) {
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
