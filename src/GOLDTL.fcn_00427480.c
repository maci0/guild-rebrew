// FUNCTION: GOLD 0x00428bf0
// FUNCTION: GOLDTL 0x00427480

// SIZE 0x64
typedef struct {
	int type;
	char text[0x60];
} Token;

extern char* g_6b7e98;
void __cdecl fcn_00426680(char* pos, Token* t);
char* __cdecl fcn_00426fd0(const char* name);
void __cdecl fcn_00427f00(char* s);
void __cdecl fcn_00425bf0(char* g, char* pos, const char* msg);
int __cdecl fcn_00428720(char* c);

void __cdecl fcn_00427480(void)
{
	Token tok;
	char* s;
	int i;

	fcn_00426680(*(char**) (g_6b7e98 + 0x118), &tok);
	if (tok.type == 7) {
		s = fcn_00426fd0(tok.text);
		if (s != 0) {
			fcn_00427f00(s);
			for (i = 0; i < 8; i++) {
				if (((char**) (g_6b7e98 + 0xc3c))[i] == 0) {
					((char**) (g_6b7e98 + 0xc3c))[i] = s;
					return;
				}
			}
			return;
		}
		fcn_00425bf0(g_6b7e98, *(char**) (g_6b7e98 + 0x118), "Error including the script!");
		fcn_00428720(g_6b7e98);
		return;
	}
	fcn_00425bf0(g_6b7e98, *(char**) (g_6b7e98 + 0x118), "Wrong include parameter!");
	fcn_00428720(g_6b7e98);
}
