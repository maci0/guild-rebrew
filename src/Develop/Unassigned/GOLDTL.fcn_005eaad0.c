


int __cdecl atexit(void (__cdecl*)(void));
void __cdecl msx_ShutdownMilesAtexit(void);

int __cdecl fcn_005eaad0(void)
{
	atexit(msx_ShutdownMilesAtexit);
	return 0;
}
