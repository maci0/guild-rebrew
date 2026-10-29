#include <stdio.h>
#include <string.h>

/* SIZE 0x64 */
struct tok_428800 {
	int type;
	union {
		char text[0x60];
		void* sym;
		int num;
		float fnum;
	} u;
};

/* SIZE 0x10 */
struct loop_428800 {
	int pos;
	int cond;
	int active;
	char skip;
	char pad[3];
};

/* SIZE 0xb0 */
struct frame_428800 {
	char pad0[8];
	int count;
	char padc[0x24];
	struct loop_428800 loop[8];
};

/* SIZE 0x30 */
struct sym_428800 {
	int kind : 4;
	int pad0 : 4;
	char pad1[0x1b];
	char tag;
	char pad2[3];
	int count;
	char* data;
};

extern char* g_6b7e98;
extern char* g_6b7eb8;
extern char g_14cb440[];

int __cdecl fcn_00428800(char* pEnd);
char* __cdecl fcn_00426620(char* s, int unused, char* end);
void __cdecl fcn_00426680(char* s, struct tok_428800* t);
int __cdecl fcn_00428ef0(void* cmd);
void __cdecl fcn_00425bf0(char* g, int pos, const char* msg);
void __cdecl fcn_00428720(char* g);


/* Evaluates one script expression from the lexer position, stopping at the
 * expression end ("," , ";" or the pEnd bound) or at a ")" / "]" token. */
/* ADDRESS: GOLDTL 0x00428800 */
int __cdecl fcn_00428800(char* pEnd)
{
	struct tok_428800 t;
	char msg[0x200];
	int value;
	int level;
	int op;
	int n;
	char* g;
	char* p;

	g = g_6b7e98;
	value = 0;
	level = 2;
	op = 2;
	if ((*(unsigned char*) (g + 0x124) & 1) != 0) {
		for (;;) {
			if (pEnd != 0 && *(char**) (g + 0x118) >= pEnd - 1) {
				break;
			}
			if (level == 0xb) {
				break;
			}
			if (level == 0xa) {
				break;
			}
			if (pEnd != 0) {
				p = fcn_00426620(*(char**) (g + 0x118), 0x679680, pEnd);
				if (p != 0 && p < pEnd) {
					value = fcn_00428800(p);
				}
			} else {
				p = fcn_00426620(*(char**) (g + 0x118), 0x679680,
						*(char**) (g + 0x11c) + *(int*) (g + 0x120));
				if (p != 0) {
					value = fcn_00428800(p);
				}
			}
			fcn_00426680(*(char**) (g + 0x118), &t);
			level = 0;
			if (t.type == 1) {
				*(char**) &g_6b7eb8 = 0;
				level = t.u.num;
			} else if (t.type == 4) {
				value = fcn_00428ef0(t.u.sym);
			} else if (t.type == 2) {
				struct sym_428800* sym = (struct sym_428800*) t.u.sym;
				int pos = (int) *(char**) (g + 0x118);
				int index;

				fcn_00426680(*(char**) (g + 0x118), &t);
				if (t.type == 1 && t.u.num == 0x1b) {
					index = fcn_00428800(0);
				} else {
					*(int*) (g + 0x118) = pos;
					index = 0;
				}
				if (index > sym->count - 1 || index < 0) {
					sprintf(msg, "Array index out of bounce: '%s'", (char*) sym + 4);
					fcn_00425bf0(g, *(int*) (g + 0x118), msg);
					fcn_00428720(g);
					return 0;
				}
				switch (sym->kind) {
				case 1:
					n = ((int*) sym->data)[index];
					break;
				case 2:
					n = ((char*) sym->data)[index];
					break;
				case 6:
					n = (int) strcpy(g_14cb440, (char*) sym->data + index * 0x60);
					break;
				case 7:
					break;
				}
			} else if (t.type == 5) {
				n = t.u.num;
			} else if (t.type == 6) {
				/* float literals are not evaluated here */
			} else if (t.type == 7) {
				n = (int) strcpy(g_14cb440, t.u.text);
			} else if (t.type == 0) {
				sprintf(msg, "Unknown symbol: '%s'", t.u.text);
				fcn_00425bf0(g, *(int*) (g + 0x118), msg);
				fcn_00428720(g);
				return 0;
			} else if (t.type == 0xb) {
				*(char**) &g_6b7eb8 = (char*) t.u.num;
				level = 2;
				op = 2;
				(*(char**) (g + 0x118))++;
			}
			switch (level) {
			case 1:
				return value == fcn_00428800(pEnd);
			case 7:
				return value != fcn_00428800(pEnd);
			case 0xc:
				n = fcn_00428800(pEnd);
				break;
			case 0xd:
			case 0x1c:
				return value;
			case 0x10:
				return value <= fcn_00428800(pEnd);
			case 0x11:
				return value < fcn_00428800(pEnd);
			case 0x12:
				return value >= fcn_00428800(pEnd);
			case 0x13:
				return value > fcn_00428800(pEnd);
			case 0x16:
				return fcn_00428800(pEnd) | value;
			case 0x17:
				return fcn_00428800(pEnd) & value;
			}
			switch (op) {
			case 2:
				value = n;
				break;
			case 4:
				value = value + n;
				break;
			case 6:
				value = value - n;
				break;
			case 0x14:
				value = value / n;
				break;
			case 0x15:
				value = value * n;
				break;
			case 0x18:
				value = value | n;
				break;
			case 0x19:
				value = value & n;
				break;
			}
			op = level;
			if (t.type == 0xc) {
				break;
			}
			if ((*(unsigned char*) (g + 0x124) & 1) == 0) {
				break;
			}
		}
	}
	if (level == 0xa) {
		struct frame_428800* fr = *(struct frame_428800**) (g + 0xc28);
		n = fr->count;
		if (n > 1 && fr->loop[n - 1].pos != 0 && fr->loop[n - 1].skip != 0) {
			fr->count = n - 1;
			fr = *(struct frame_428800**) (g + 0xc28);
			if (fr->loop[fr->count].active == 1) {
				*(int*) (g + 0x118) = fr->loop[fr->count].pos;
			}
		}
	}
	*(char**) &g_6b7eb8 = 0;
	return value;
}
