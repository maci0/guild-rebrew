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

extern char* g_6b7e98;
extern char g_14cb440[];

void __cdecl fcn_00426680(int lex, struct tok_428d50* t);
int __cdecl fcn_00428800(int a);

// FUNCTION: GOLD 0x0042a480
// SIZE: 404
// FUNCTION: GOLDTL 0x428d50
// SIZE: 404

/* Parses an assignment, increment or decrement on a script variable. */
int __cdecl fcn_00428d50(struct var_428d50* v)
{
	struct tok_428d50 t;
	int idx;

	idx = 0;
	fcn_00426680(*(int*) (g_6b7e98 + 0x118), &t);
	if (t.type != 1) {
		goto done;
	}
	if (t.u.num == 0x1b) {
		idx = fcn_00428800(idx);
		fcn_00426680(*(int*) (g_6b7e98 + 0x118), &t);
	}
	switch (t.u.num) {
	case 2:
		if (v->type == 1) {
			((int*) v->data)[idx] = fcn_00428800(0);
		} else if (v->type == 2) {
			v->data[idx] = (char) fcn_00428800(0);
		} else if (v->type == 7) {
			((float*) v->data)[idx] = (float) fcn_00428800(0);
		} else if (v->type == 6) {
			if (fcn_00428800(0) != 0) {
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
