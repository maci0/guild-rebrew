int __cdecl msx_FindSampleHandleIndex(int);

/* ADDRESS: GOLDTL 0x0042a8b0 */
int __cdecl msx_SetSamplePlaybackRate(int sampleHandle, int playbackRate)
{
	if (*(int*) 0x6b7f90 == 0) {
		return -1;
	}
	if (msx_FindSampleHandleIndex(sampleHandle) < 0) {
		return -1;
	}
	(*(void (__stdcall**) (int, int)) 0x6623d4)(sampleHandle, playbackRate);
	return -1;
}
