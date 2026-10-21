#include <string.h>

struct tok_427280 {
	int type;
	union {
		char text[0x60];
		int num;
	} u;
};
/* SIZE 0x64 */

struct loop_427280 {
	int pos;
	int cond;
	int active;
	char skip;
	char padd[3];
};
/* SIZE 0x10 */

struct frame_427280 {
	char pad0[8];
	int level;
	char padc[0x24];
	struct loop_427280 loop[8];
};
/* SIZE 0xb0 */

extern char* g_6b7e98;
extern char g_14cb3c0[];

void __cdecl fcn_00426680(int lex, struct tok_427280* t);
int __cdecl fcn_00428800(int a);
int __cdecl fcn_004263b0(char dir);
int __cdecl fcn_00426340(void);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

#define FRAME_427280 (*(struct frame_427280**) (g_6b7e98 + 0xc28))
#define LEX_427280 (*(int*) (g_6b7e98 + 0x118))

/* ADDRESS: GOLDTL 0x00427280 */
/* Parses an if head: evaluates the condition and pushes a block level. */
int __cdecl fcn_00427280(void)
{
	struct tok_427280 t;
	int pos;
	int cond;
	int type;
	int num;

	pos = LEX_427280 - strlen(g_14cb3c0);
	fcn_00426680(LEX_427280, &t);
	if (t.type != 1 || t.u.num != 0xc) {
		fcn_00425bf0(g_6b7e98, LEX_427280, "Syntax error: '(' missing!");
		return 0;
	}
	cond = fcn_00428800(0);
	memset(&FRAME_427280->loop[FRAME_427280->level], 0, sizeof(struct loop_427280));
	FRAME_427280->loop[FRAME_427280->level].active = 2;
	FRAME_427280->loop[FRAME_427280->level].pos = pos;
	FRAME_427280->loop[FRAME_427280->level].cond = cond;
	pos = LEX_427280;
	fcn_00426680(pos, &t);
	type = t.type;
	num = t.u.num;
	if (type == 1 && num == 8) {
		FRAME_427280->loop[FRAME_427280->level].skip = 0;
	} else {
		FRAME_427280->loop[FRAME_427280->level].skip = 1;
		LEX_427280 = pos;
	}
	FRAME_427280->level++;
	if (FRAME_427280->level > 8) {
		fcn_00425bf0(g_6b7e98, LEX_427280, "Too many looplevel...");
		FRAME_427280->level--;
	}
	if (cond == 0) {
		if (type == 1) {
			if (num != 8)
				return 0;
			LEX_427280 = pos;
			fcn_004263b0(type);
		} else {
			if (fcn_00426340() == 0) {
				fcn_00425bf0(g_6b7e98, LEX_427280, "Syntax error: ';' missing!");
				return 0;
			}
		}
		LEX_427280--;
	}
	return 0;
}
