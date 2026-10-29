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

void __cdecl fcn_00426680(int lex, struct tok_425fe0* t);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
void __cdecl fcn_00428720(char* g);
int __cdecl fcn_00425ec0(char* g, int arg, int kind, char* name);

/* ADDRESS: GOLDTL 0x00425fe0 */
int __cdecl fcn_00425fe0(char* g, int arg)
{
	struct tok_425fe0 t;
	char name[0x20];
	int kind;
	int r;

	kind = 1;
	r = 0;
	fcn_00426680(*(int*) (g + 0x118), &t);
	if (t.type != 0 && (t.type != 2 || *(int*) (t.u.sym + 0x28) != 0)) {
		if (t.type == 2) {
			fcn_00425bf0(g, *(int*) (g + 0x118), "Syntax error: Propably duplicate symbol...");
		} else {
			fcn_00425bf0(g, *(int*) (g + 0x118), "Syntax error: unknown");
		}
		fcn_00428720(g);
	} else {
		if (t.type == 0) {
			strcpy(name, t.u.text);
		} else {
			strcpy(name, t.u.sym + 4);
		}
		fcn_00426680(*(int*) (g + 0x118), &t);
		if (t.type == 1 && t.u.num == 0x1b) {
			fcn_00426680(*(int*) (g + 0x118), &t);
			if (t.type == 5) {
				kind = t.u.num;
			}
		}
		r = fcn_00425ec0(g, arg, kind, name);
	}
	return r;
}
