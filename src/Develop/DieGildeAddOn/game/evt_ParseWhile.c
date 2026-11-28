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

extern char* evt_CurrentScript;
extern char g_14cb3b0[];

void __cdecl evt_ReadToken(int lex, struct tok_427070* t);
int __cdecl evt_EvaluateExpression(int a);
int __cdecl evt_SkipBlock(char dir);
int __cdecl evt_SeekSemicolon(void);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

#define FRAME_427070 (*(struct frame_427070**) (evt_CurrentScript + 0xc28))
#define LEX_427070 (*(int*) (evt_CurrentScript + 0x118))


/* Parses a while head: evaluates the condition and pushes a loop level. */
/* ADDRESS: GOLDTL 0x00427070 */
/* ADDRESS: GOLDDE 0x00421ad0 */
int __cdecl evt_ParseWhile(void)
{
	struct tok_427070 t;
	int pos;
	int cond;

	pos = LEX_427070 - strlen(g_14cb3b0);
	evt_ReadToken(LEX_427070, &t);
	if (t.type != 1 || t.u.num != 0xc) {
		evt_LogScriptError(evt_CurrentScript, LEX_427070, "Syntax error: '(' missing!");
		return 0;
	}
	cond = evt_EvaluateExpression(0);
	FRAME_427070->loop[FRAME_427070->level].cond = cond;
	if (cond == 0) {
		evt_ReadToken(LEX_427070, &t);
		if (t.type == 1) {
			if (t.u.num == 8) {
				LEX_427070 = pos;
				evt_SkipBlock(1);
			}
		} else if (evt_SeekSemicolon() == 0) {
			evt_LogScriptError(evt_CurrentScript, LEX_427070, "Syntax error: ';' missing!");
		}
		return 0;
	}
	memset(&FRAME_427070->loop[FRAME_427070->level], 0, sizeof(struct loop_427070));
	FRAME_427070->loop[FRAME_427070->level].active = 1;
	FRAME_427070->loop[FRAME_427070->level].pos = pos;
	pos = LEX_427070;
	evt_ReadToken(pos, &t);
	if (t.type == 1 && t.u.num == 8) {
		FRAME_427070->loop[FRAME_427070->level].skip = 0;
	} else {
		FRAME_427070->loop[FRAME_427070->level].skip = 1;
		LEX_427070 = pos;
	}
	FRAME_427070->level++;
	if (FRAME_427070->level > 8) {
		evt_LogScriptError(evt_CurrentScript, LEX_427070, "Too many looplevel...");
		FRAME_427070->level--;
	}
	return 0;
}
