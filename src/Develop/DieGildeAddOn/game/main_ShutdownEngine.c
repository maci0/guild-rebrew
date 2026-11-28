void __cdecl main_ShutdownGameModules(void);
void __cdecl main_ShutdownSubsystems(void);
void __cdecl main_ShutdownClientSubsystems(void);
void __cdecl fcn_00538140(void);
void __cdecl main_SetScreensaverActive(int v);

/* ADDRESS: GOLDTL 0x00538220 */
void __cdecl main_ShutdownEngine(void)
{
	main_ShutdownGameModules();
	main_ShutdownSubsystems();
	main_ShutdownClientSubsystems();
	fcn_00538140();
	if (*(int*) 0x7e246c != 0)
		return;
	if (*(int*) 0x774974 == 0)
		return;
	main_SetScreensaverActive(1);
}
