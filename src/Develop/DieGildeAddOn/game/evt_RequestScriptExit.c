


char* __cdecl evt_FindDefinition(char* c, const char* name);
void __cdecl evt_EnterFunction(char* c, char* d);
void __cdecl evt_RunGfxScript(char* c);
void __cdecl evt_LogScriptError(char* c, int h, const char* msg);
void __cdecl evt_LogScriptError(char* c, int h, const char* msg);

/* ADDRESS: GOLDDE 0x00423180 */
int __cdecl evt_RequestScriptExit(char* c)
{
	unsigned int flags;
	char* d;
	char* t;

	if (c == 0) {
		return 0;
	}
	flags = *(unsigned int*) (c + 0x124);
	*(int*) (c + 0xc5c) = 0;
	*(int*) (c + 0xc60) = 0;
	if ((flags & 2) == 0) {
		d = evt_FindDefinition(c, "exit");
		if (d != 0) {
			*(unsigned int*) (c + 0x124) = flags | 3;
			evt_EnterFunction(c, d);
			*(int*) (c + 0xc84) = 2;
			evt_RunGfxScript(c);
			return 0;
		}
	}
	t = *(char**) (c + 0xc94);
	*(int*) (c + 0x100) = 0;
	*(int*) (c + 0x124) = 0;
	if (t != 0) {
		*(int*) (t + 0x28) = -1;
	}
	evt_LogScriptError(c, 0, "Script done...");
	evt_FreeScript(c);
	return 1;
}
