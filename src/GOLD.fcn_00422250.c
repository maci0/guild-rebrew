void __cdecl DispatchLogOutput(int, int, int);
__declspec(dllimport) void __stdcall FreeConsole(void);

/* ADDRESS: GOLD 0x00422250 */
void __cdecl fcn_00422250(void)
{
	int p;
	unsigned char f;
	int z;

	for (p = 0x5f6d48; p < 0x5f6d78; p += 4)
		DispatchLogOutput(0x5f7148, *(int *)0x632370, *(int *)p);
	f = *(unsigned char *)0x632370;
	z = 0;
	if ((f & 8) != 0) {
		FreeConsole();
		*(int *)0x1463564 = z;
	}
	*(int *)0x632368 = z;
	*(int *)0x1463440 = z;
	*(int *)0x632370 = z;
}
