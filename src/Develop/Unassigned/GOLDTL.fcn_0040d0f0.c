

char* __cdecl evt_LoadGfxScript(char*);
void __cdecl fcn_00428340(char*, int, int);

void __cdecl ch_RunQueuedAniScript(char* task)
{
	char* script;

	script = evt_LoadGfxScript(task + 0x90);
	if (script != 0) {
		fcn_00428340(script, 1, *(int*) (task + 0x180));
		*(int*) (script + 0x104) = *(int*) (task + 0x17c);
	}
}
