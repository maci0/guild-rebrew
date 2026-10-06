#include <string.h>

struct tok_427070 {
	int type;
	union {
		char text[0x60];
		int num;
	} u;
};
// SIZE 0x64

struct loop_427070 {
	int pos;
	int cond;
	int active;
	char skip;
	char padd[3];
};
// SIZE 0x10

struct frame_427070 {
	char pad0[8];
	int level;
	char padc[0x24];
	struct loop_427070 loop[8];
};
// SIZE 0xb0

extern char* g_6b7e98;
extern char g_14cb3b0[];

void __cdecl fcn_00426680(int lex, struct tok_427070* t);
int __cdecl fcn_00428800(int a);
int __cdecl fcn_004263b0(char dir);
int __cdecl fcn_00426340(void);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

#define FRAME_427070 (*(struct frame_427070**) (g_6b7e98 + 0xc28))
#define LEX_427070 (*(int*) (g_6b7e98 + 0x118))

// FUNCTION: GOLD 0x004287e0
// FUNCTION: GOLDTL 0x427070

/* Parses a while head: evaluates the condition and pushes a loop level. */
int __cdecl fcn_00427070(void)
{
	struct tok_427070 t;
	int pos;
	int cond;

	pos = LEX_427070 - strlen(g_14cb3b0);
	fcn_00426680(LEX_427070, &t);
	if (t.type != 1 || t.u.num != 0xc) {
		fcn_00425bf0(g_6b7e98, LEX_427070, "Syntax error: '(' missing!");
		return 0;
	}
	cond = fcn_00428800(0);
	FRAME_427070->loop[FRAME_427070->level].cond = cond;
	if (cond == 0) {
		fcn_00426680(LEX_427070, &t);
		if (t.type == 1) {
			if (t.u.num == 8) {
				LEX_427070 = pos;
				fcn_004263b0(1);
			}
		} else if (fcn_00426340() == 0) {
			fcn_00425bf0(g_6b7e98, LEX_427070, "Syntax error: ';' missing!");
		}
		return 0;
	}
	memset(&FRAME_427070->loop[FRAME_427070->level], 0, sizeof(struct loop_427070));
	FRAME_427070->loop[FRAME_427070->level].active = 1;
	FRAME_427070->loop[FRAME_427070->level].pos = pos;
	pos = LEX_427070;
	fcn_00426680(pos, &t);
	if (t.type == 1 && t.u.num == 8) {
		FRAME_427070->loop[FRAME_427070->level].skip = 0;
	} else {
		FRAME_427070->loop[FRAME_427070->level].skip = 1;
		LEX_427070 = pos;
	}
	FRAME_427070->level++;
	if (FRAME_427070->level > 8) {
		fcn_00425bf0(g_6b7e98, LEX_427070, "Too many looplevel...");
		FRAME_427070->level--;
	}
	return 0;
}
