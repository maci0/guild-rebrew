


int sprintf(char*, const char*, ...);
char* __cdecl evt_LoadGfxScript(int);
void __cdecl evt_CallScriptFunction(char*, int, char*);

char* __cdecl ch_AttachEntityGfxScript(char* ent, int script_id)
{
	char buf[0x80];
	char* script;

	sprintf(buf, "sp_%i", *(int*) (ent + 4));
	script = evt_LoadGfxScript(script_id);
	if (script != 0) {
		evt_CallScriptFunction(script, 1, buf);
		*(int*) (script + 0xc94) = *(int*) (ent + 0x184);
		*(int*) (*(char**) (ent + 0x184) + 0x28) = *(int*) (script + 0x100);
	}
	return script;
}
