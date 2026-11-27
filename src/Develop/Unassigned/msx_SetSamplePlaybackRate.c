int __cdecl msx_FindSampleHandleIndex(int);

/* ADDRESS: GOLDTL 0x0042a8b0 */
int __cdecl msx_SetSamplePlaybackRate(int a1, int a2)
{
	if (*(int*) 0x6b7f90 == 0) {
		return -1;
	}
	if (msx_FindSampleHandleIndex(a1) < 0) {
		return -1;
	}
	(*(void (__stdcall**) (int, int)) 0x6623d4)(a1, a2);
	return -1;
}
