


extern int g_772f3c;

char* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScriptLine(char*, int);

int __cdecl fcn_004e44b0(int a1, int a2)
{
	char* p;

	if (g_772f3c == 0) {
		p = evt_LoadGfxScript(a1);
		if (p != 0) {
			evt_RunScriptLine(p, a2);
			return *(int*) (p + 0x100);
		}
	}
	return 0;
}
