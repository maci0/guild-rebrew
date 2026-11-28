extern char* evt_CurrentScript;



char* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_RunScript(char*);

/* ADDRESS: GOLDDE 0x0040b2e0 */
char* __cdecl RunScript(int* scriptName)
{
	char* p;

	p = evt_LoadGfxScript(*scriptName);
	if (p == 0) {
		return 0;
	}
	*(int*) (p + 0x104) = *(int*) (evt_CurrentScript + 0x104);
	*(int*) (p + 0xc8c) = *(int*) (evt_CurrentScript + 0xc8c);
	*(int*) (p + 0xc90) = *(int*) (evt_CurrentScript + 0xc90);
	evt_RunScript(p);
	return p;
}
