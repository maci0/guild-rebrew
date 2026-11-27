

int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* AIL_END_SAMPLE_FN)(int);

int __cdecl msx_EndSample(int sampleHandle)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			(*(AIL_END_SAMPLE_FN*) 0x6623d0)(sampleHandle);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
