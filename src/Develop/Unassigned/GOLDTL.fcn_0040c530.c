


extern char* evt_CurrentScript;
char* __cdecl evt_LoadGfxScript(int id);
void __cdecl evt_CallScriptFunction(char* o, int n, ...);

char* __cdecl RunScriptInt2(int* a, int* b, int* c)
{
	char* o;

	o = evt_LoadGfxScript(*a);
	if (o == 0) {
		return 0;
	}
	*(int*) (o + 0x104) = *(int*) (evt_CurrentScript + 0x104);
	*(int*) (o + 0xc8c) = *(int*) (evt_CurrentScript + 0xc8c);
	*(int*) (o + 0xc90) = *(int*) (evt_CurrentScript + 0xc90);
	evt_CallScriptFunction(o, 2, *b, *c);
	return o;
}
