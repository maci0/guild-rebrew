


int sprintf(char*, const char*, ...);
char* __cdecl evt_LoadGfxScript(int);
void __cdecl fcn_00428340(char*, int, char*);

char* __cdecl ch_AttachEntityGfxScript(char* ent, int script_id)
{
	char buf[0x80];
	char* script;

	sprintf(buf, "sp_%i", *(int*) (ent + 4));
	script = evt_LoadGfxScript(script_id);
	if (script != 0) {
		fcn_00428340(script, 1, buf);
		*(int*) (script + 0xc94) = *(int*) (ent + 0x184);
		*(int*) (*(char**) (ent + 0x184) + 0x28) = *(int*) (script + 0x100);
	}
	return script;
}
