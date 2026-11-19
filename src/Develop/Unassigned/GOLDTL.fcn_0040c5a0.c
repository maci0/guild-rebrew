

extern char* evt_CurrentScript;
char* __cdecl evt_LoadGfxScript(int id);
void __cdecl fcn_00428340(char* o, int n, ...);

char* __cdecl RunScriptString(int* a, int* b)
{
	char* o;

	o = evt_LoadGfxScript(*a);
	if (o == 0) {
		return 0;
	}
	*(int*) (o + 0x104) = *(int*) (evt_CurrentScript + 0x104);
	*(int*) (o + 0xc8c) = *(int*) (evt_CurrentScript + 0xc8c);
	*(int*) (o + 0xc90) = *(int*) (evt_CurrentScript + 0xc90);
	fcn_00428340(o, 1, *b);
	return o;
}
