


extern int g_772f3c;

char* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScriptLine(char*, int);

int __cdecl evt_StartGfxScript(int scriptPath, int args)
{
	char* p;

	if (g_772f3c == 0) {
		p = evt_LoadGfxScript(scriptPath);
		if (p != 0) {
			evt_RunScriptLine(p, args);
			return *(int*) (p + 0x100);
		}
	}
	return 0;
}
