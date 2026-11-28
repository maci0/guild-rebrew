#include <string.h>

// SIZE 0x64
struct tok_425fe0 {
	int type;
	union {
		char text[0x60];
		char* sym;
		int num;
	} u;
};

void __cdecl evt_ReadToken(int lex, struct tok_425fe0* t);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);
void __cdecl evt_RequestScriptExit(char* g);
int __cdecl evt_AllocateLocalVariable(char* g, int arg, int kind, char* name);

/* ADDRESS: GOLDTL 0x00425fe0 */
/* ADDRESS: GOLDDE 0x00420ab0 */
int __cdecl evt_ParseSymbolDeclaration(char* g, int arg)
{
	struct tok_425fe0 t;
	char name[0x20];
	int kind;
	int r;

	kind = 1;
	r = 0;
	evt_ReadToken(*(int*) (g + 0x118), &t);
	if (t.type != 0 && (t.type != 2 || *(int*) (t.u.sym + 0x28) != 0)) {
		if (t.type == 2) {
			evt_LogScriptError(g, *(int*) (g + 0x118), "Syntax error: Propably duplicate symbol...");
		} else {
			evt_LogScriptError(g, *(int*) (g + 0x118), "Syntax error: unknown");
		}
		evt_RequestScriptExit(g);
	} else {
		if (t.type == 0) {
			strcpy(name, t.u.text);
		} else {
			strcpy(name, t.u.sym + 4);
		}
		evt_ReadToken(*(int*) (g + 0x118), &t);
		if (t.type == 1 && t.u.num == 0x1b) {
			evt_ReadToken(*(int*) (g + 0x118), &t);
			if (t.type == 5) {
				kind = t.u.num;
			}
		}
		r = evt_AllocateLocalVariable(g, arg, kind, name);
	}
	return r;
}
