


// SIZE 0x64
typedef struct {
	int type;
	char text[0x60];
} Token;

extern char* evt_CurrentScript;
void __cdecl fcn_00426680(char* pos, Token* t);
char* __cdecl evt_LoadGfxScript(const char* name);
void __cdecl evt_ParseScript(char* s);
void __cdecl evt_LogScriptError(char* g, char* pos, const char* msg);
int __cdecl fcn_00428720(char* c);

void __cdecl evt_IncludeScript(void)
{
	Token tok;
	char* s;
	int i;

	fcn_00426680(*(char**) (evt_CurrentScript + 0x118), &tok);
	if (tok.type == 7) {
		s = evt_LoadGfxScript(tok.text);
		if (s != 0) {
			evt_ParseScript(s);
			for (i = 0; i < 8; i++) {
				if (((char**) (evt_CurrentScript + 0xc3c))[i] == 0) {
					((char**) (evt_CurrentScript + 0xc3c))[i] = s;
					return;
				}
			}
			return;
		}
		evt_LogScriptError(evt_CurrentScript, *(char**) (evt_CurrentScript + 0x118), "Error including the script!");
		fcn_00428720(evt_CurrentScript);
		return;
	}
	evt_LogScriptError(evt_CurrentScript, *(char**) (evt_CurrentScript + 0x118), "Wrong include parameter!");
	fcn_00428720(evt_CurrentScript);
}
