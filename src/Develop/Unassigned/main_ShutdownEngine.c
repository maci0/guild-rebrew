void __cdecl fcn_005381a0(void);
void __cdecl main_ShutdownSubsystems(void);
void __cdecl fcn_00538790(void);
void __cdecl fcn_00538140(void);
void __cdecl main_SetScreensaverActive(int v);

/* ADDRESS: GOLDTL 0x00538220 */
void __cdecl main_ShutdownEngine(void)
{
	fcn_005381a0();
	main_ShutdownSubsystems();
	fcn_00538790();
	fcn_00538140();
	if (*(int*) 0x7e246c != 0)
		return;
	if (*(int*) 0x774974 == 0)
		return;
	main_SetScreensaverActive(1);
}
