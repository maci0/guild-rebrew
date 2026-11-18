extern int g_6791d0;



void* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScript(void*);

int __cdecl fcn_00429fe0(int a1, int a2, int a3)
{
	int result;
	void* script;

	script = evt_LoadGfxScript(a3);
	if (script != 0) {
		evt_RunScript(script);
		result = *(int*) ((char*) script + 0x100);
		g_6791d0 = result;
		return result;
	}
	g_6791d0 = -1;
	return -1;
}
