#include <string.h>

struct tok_428d50 {
	int type;
	union {
		char text[0x60];
		int num;
	} u;
};
// SIZE 0x64

struct var_428d50 {
	int type : 4;
	int pad4 : 28;
	char pad4b[0x28];
	char* data;
};
// SIZE 0x30

extern char* evt_CurrentScript;
extern char g_14cb440[];

void __cdecl evt_ReadToken(int lex, struct tok_428d50* t);
int __cdecl evt_EvaluateExpression(int a);


/* Parses an assignment, increment or decrement on a script variable. */
/* ADDRESS: GOLDTL 0x00428d50 */
int __cdecl evt_ParseVariableAssignment(struct var_428d50* v)
{
	struct tok_428d50 t;
	int idx;

	idx = 0;
	evt_ReadToken(*(int*) (evt_CurrentScript + 0x118), &t);
	if (t.type != 1) {
		goto done;
	}
	if (t.u.num == 0x1b) {
		idx = evt_EvaluateExpression(idx);
		evt_ReadToken(*(int*) (evt_CurrentScript + 0x118), &t);
	}
	switch (t.u.num) {
	case 2:
		if (v->type == 1) {
			((int*) v->data)[idx] = evt_EvaluateExpression(0);
		} else if (v->type == 2) {
			v->data[idx] = (char) evt_EvaluateExpression(0);
		} else if (v->type == 7) {
			((float*) v->data)[idx] = (float) evt_EvaluateExpression(0);
		} else if (v->type == 6) {
			if (evt_EvaluateExpression(0) != 0) {
				strcpy(v->data + idx * 0x60, g_14cb440);
			}
		}
		break;
	case 3:
		if (v->type == 1) {
			((int*) v->data)[idx]++;
		} else if (v->type == 2) {
			v->data[idx]++;
		}
		break;
	case 5:
		if (v->type == 1) {
			((int*) v->data)[idx]--;
		} else if (v->type == 2) {
			v->data[idx]--;
		}
		break;
	}
done:
	return 0;
}
