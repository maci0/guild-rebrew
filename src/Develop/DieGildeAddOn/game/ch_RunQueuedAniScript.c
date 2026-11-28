

char* __cdecl evt_LoadGfxScript(char*);
void __cdecl evt_CallScriptFunction(char*, int, int);

/* ADDRESS: GOLDDE 0x0040bf00 */
void __cdecl ch_RunQueuedAniScript(char* task)
{
	char* script;

	script = evt_LoadGfxScript(task + 0x90);
	if (script != 0) {
		evt_CallScriptFunction(script, 1, *(int*) (task + 0x180));
		*(int*) (script + 0x104) = *(int*) (task + 0x17c);
	}
}
