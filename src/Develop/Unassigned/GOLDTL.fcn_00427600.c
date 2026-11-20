#include <string.h>

typedef struct {
	int type;
	union {
		char text[0x60];
		char* sym;
		int num;
	} u;
} tok_427600;

extern char* evt_CurrentScript;

void __cdecl evt_ReadToken(int lex, tok_427600* t);
void __cdecl evt_LogScriptError(char* script, unsigned int position, const char* message);
void __cdecl evt_RequestScriptExit(char* c);

/* ADDRESS: GOLDTL 0x00427600 */
int __cdecl fcn_00427600(char* g, int arg)
{
	char* e;
	tok_427600 t;
	char* d;

	e = *(char**) (g + 0x10c) + *(int*) (g + 0x110) * 0x14c;
	e[0x24] = 0;
	memset(&t, 0, sizeof(t));
	for (;;) {
		evt_ReadToken(*(int*) (evt_CurrentScript + 0x118), &t);
		if (t.type == 8 && ((t.u.num >= 1 && t.u.num <= 2) || t.u.num == 6)) {
			*(int*) (e + 0x28 + e[0x24] * 4) = t.u.num;
			evt_ReadToken(*(int*) (evt_CurrentScript + 0x118), &t);
			if (t.type != 0) {
				if (t.type == 2)
					evt_LogScriptError(g, *(int*) (g + 0x118), (char*) 0x679460);
				else
					evt_LogScriptError(g, *(int*) (g + 0x118), (char*) 0x67944c);
				evt_RequestScriptExit(g);
				return 0;
			}
			d = e + 0x48 + e[0x24] * 0x20;
			strcpy(d, t.u.text);
			e[0x24]++;
		}
		evt_ReadToken(*(int*) (evt_CurrentScript + 0x118), &t);
		if (t.type == 1 && t.u.num == 0xd) {
			break;
		}
	}
	(*(int*) (g + 0x110))++;
	return arg;
}
