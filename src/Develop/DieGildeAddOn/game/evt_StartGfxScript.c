


extern int cut_SkipMode;

char* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScriptLine(char*, int);

/* ADDRESS: GOLDDE 0x004d0ea0 */
int __cdecl evt_StartGfxScript(int scriptPath, int args)
{
	char* p;

	if (cut_SkipMode == 0) {
		p = evt_LoadGfxScript(scriptPath);
		if (p != 0) {
			evt_RunScriptLine(p, args);
			return *(int*) (p + 0x100);
		}
	}
	return 0;
}
