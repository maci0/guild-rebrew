


// SIZE 0x64
typedef struct {
	int type;
	char text[0x60];
} Token;

extern char* evt_CurrentScript;
void __cdecl fcn_00426680(char* pos, Token* t);
char* __cdecl evt_LoadGfxScript(const char* name);
void __cdecl fcn_00427f00(char* s);
void __cdecl fcn_00425bf0(char* g, char* pos, const char* msg);
int __cdecl fcn_00428720(char* c);

void __cdecl fcn_00427480(void)
{
	Token tok;
	char* s;
	int i;

	fcn_00426680(*(char**) (evt_CurrentScript + 0x118), &tok);
	if (tok.type == 7) {
		s = evt_LoadGfxScript(tok.text);
		if (s != 0) {
			fcn_00427f00(s);
			for (i = 0; i < 8; i++) {
				if (((char**) (evt_CurrentScript + 0xc3c))[i] == 0) {
					((char**) (evt_CurrentScript + 0xc3c))[i] = s;
					return;
				}
			}
			return;
		}
		fcn_00425bf0(evt_CurrentScript, *(char**) (evt_CurrentScript + 0x118), "Error including the script!");
		fcn_00428720(evt_CurrentScript);
		return;
	}
	fcn_00425bf0(evt_CurrentScript, *(char**) (evt_CurrentScript + 0x118), "Wrong include parameter!");
	fcn_00428720(evt_CurrentScript);
}
