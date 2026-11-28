extern char g_7e246c[];
extern char g_774974[];
void __cdecl main_ShutdownGameModules(void);
void __cdecl main_ShutdownSubsystems(void);
void __cdecl main_ShutdownClientSubsystems(void);
void __cdecl fcn_00538140(void);
void __cdecl main_SetScreensaverActive(int v);

/* ADDRESS: GOLDTL 0x00538220 */
/* ADDRESS: GOLDDE 0x0051faf0 */
void __cdecl main_ShutdownEngine(void)
{
	main_ShutdownGameModules();
	main_ShutdownSubsystems();
	main_ShutdownClientSubsystems();
	fcn_00538140();
	if (*(int*) &g_7e246c != 0)
		return;
	if (*(int*) &g_774974 == 0)
		return;
	main_SetScreensaverActive(1);
}
