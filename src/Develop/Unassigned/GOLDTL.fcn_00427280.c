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

extern char* evt_CurrentScript;
extern char g_14cb3c0[];

void __cdecl evt_ReadToken(int lex, struct tok_427280* t);
int __cdecl evt_EvaluateExpression(int a);
int __cdecl evt_SkipBlock(char dir);
int __cdecl evt_SeekSemicolon(void);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

#define FRAME_427280 (*(struct frame_427280**) (evt_CurrentScript + 0xc28))
#define LEX_427280 (*(int*) (evt_CurrentScript + 0x118))

/* Parses an if head: evaluates the condition and pushes a block level. */
/* ADDRESS: GOLDTL 0x00427280 */
int __cdecl evt_ParseIfHead(void)
{
	struct tok_427280 t;
	int pos;
	int cond;
	int type;
	int num;

	pos = LEX_427280 - strlen(g_14cb3c0);
	evt_ReadToken(LEX_427280, &t);
	if (t.type != 1 || t.u.num != 0xc) {
		evt_LogScriptError(evt_CurrentScript, LEX_427280, "Syntax error: '(' missing!");
		return 0;
	}
	cond = evt_EvaluateExpression(0);
	memset(&FRAME_427280->loop[FRAME_427280->level], 0, sizeof(struct loop_427280));
	FRAME_427280->loop[FRAME_427280->level].active = 2;
	FRAME_427280->loop[FRAME_427280->level].pos = pos;
	FRAME_427280->loop[FRAME_427280->level].cond = cond;
	pos = LEX_427280;
	evt_ReadToken(pos, &t);
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
		evt_LogScriptError(evt_CurrentScript, LEX_427280, "Too many looplevel...");
		FRAME_427280->level--;
	}
	if (cond == 0) {
		if (type == 1) {
			if (num != 8)
				return 0;
			LEX_427280 = pos;
			evt_SkipBlock(type);
		} else {
			if (evt_SeekSemicolon() == 0) {
				evt_LogScriptError(evt_CurrentScript, LEX_427280, "Syntax error: ';' missing!");
				return 0;
			}
		}
		LEX_427280--;
	}
	return 0;
}
