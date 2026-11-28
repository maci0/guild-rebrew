


int __cdecl atexit(void (__cdecl*)(void));
void __cdecl msx_ShutdownMilesAtexit(void);

/* ADDRESS: GOLDDE 0x005cb2d0 */
int __cdecl msx_RegisterAILShutdown(void)
{
	atexit(msx_ShutdownMilesAtexit);
	return 0;
}
