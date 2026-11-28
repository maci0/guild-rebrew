extern int evt_LastGfxScriptId;



void* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScript(void*);

int __cdecl evt_LoadAndRunGfxScript(int a1, int a2, int a3)
{
	int result;
	void* script;

	script = evt_LoadGfxScript(a3);
	if (script != 0) {
		evt_RunScript(script);
		result = *(int*) ((char*) script + 0x100);
		evt_LastGfxScriptId = result;
		return result;
	}
	evt_LastGfxScriptId = -1;
	return -1;
}
