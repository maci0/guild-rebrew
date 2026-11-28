extern int d2_ScreenSurface;
extern unsigned long d3_LastReleaseRefCount;

/* ADDRESS: GOLDTL 0x00473610 */
short __cdecl d3_ReleaseBackBuffer(void)
{
	int obj;
	int r;

	obj = *(int*) (d2_ScreenSurface + 0x24);
	r = ((int (__stdcall*) (int)) *(int*) (*(int*) obj + 8))(obj);
	d3_LastReleaseRefCount = r;
	*(int*) (d2_ScreenSurface + 0x24) = 0;
	return (short) r;
}
