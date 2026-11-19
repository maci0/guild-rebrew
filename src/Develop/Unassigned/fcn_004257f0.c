void __cdecl msx_StopSample(int);

/* ADDRESS: GOLDTL 0x004257f0 */
void __cdecl fcn_004257f0(void)
{
	if (*(void**) 0x6b7d80 != 0) {
		msx_StopSample(*(int*) 0x6b7d80);
	}
}
