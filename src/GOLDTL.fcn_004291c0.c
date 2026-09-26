#include <stdio.h>

// SIZE 0x64
struct tok_4291c0 {
	int type;
	union {
		char text[0x60];
		int num;
	} u;
};

// SIZE 0x10
struct frame_4291c0 {
	int pos;
	int x4;
	int kind;
	unsigned char open;
	char padd[3];
};

// SIZE 0x40 (f[] runs on past the declared element)
struct stack_4291c0 {
	char pad0[8];
	int count;
	char padc[0x24];
	struct frame_4291c0 f[1];
};

extern int g_6b7ec4;
extern int g_6b7eb8;

void __cdecl fcn_00426680(int lex, struct tok_4291c0* t);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
void __cdecl fcn_00428720(char* g);
int __cdecl fcn_00427b40(char* g);
void __cdecl fcn_00427070(void);
void __cdecl fcn_00427280(void);
void __cdecl fcn_00427480(void);
void __cdecl fcn_00427530(void);
void __cdecl fcn_00427570(void);
void __cdecl fcn_00427580(void);
void __cdecl fcn_00427590(void);
void __cdecl fcn_004275a0(void);
void __cdecl fcn_00428ef0(int);
void __cdecl fcn_00428d50(int);
void __cdecl fcn_00427c40(char*, int);
int __cdecl fcn_00425fe0(char*, int);

// FUNCTION: GOLDTL 0x004291c0
// SIZE: 720

/* Runs script statements until a block end (keyword 10), token type 12, or
 * the running flag at g+0x124 clears. */
int __cdecl fcn_004291c0(char* g)
{
	struct tok_4291c0 t;
	char msg[0x100];
	char msg2[0x100];
	struct stack_4291c0* s;
	int n;

	g_6b7ec4 = 0;
	do {
		fcn_00426680(*(int*) (g + 0x118), &t);
		if (t.type == 1) {
			g_6b7eb8 = 0;
			if (t.u.num == 9) {
				s = *(struct stack_4291c0**) (g + 0xc28);
				if (s->count > 0) {
					s->count--;
					s = *(struct stack_4291c0**) (g + 0xc28);
					if (s->f[s->count].pos != 0 && s->f[s->count].kind == 1) {
						*(int*) (g + 0x118) = s->f[s->count].pos;
					}
					return 0;
				}
				if (fcn_00427b40(g) == 0) {
					fcn_00428720(g);
				}
				return 0;
			}
		} else if (t.type == 10) {
			g_6b7eb8 = 0;
			switch (t.u.num) {
			case 1:
				fcn_00427070();
				break;
			case 2:
				fcn_00427280();
				break;
			case 4:
				fcn_004275a0();
				break;
			case 5:
				fcn_00427480();
				break;
			case 6:
				fcn_00427570();
				break;
			case 8:
				fcn_00427580();
				break;
			case 7:
				fcn_00427590();
				break;
			case 3:
				fcn_00427530();
				break;
			default:
				sprintf(msg2, "Keyword is not surported!");
				fcn_00425bf0(g, *(int*) (g + 0x118), msg2);
				fcn_00428720(g);
				return 0;
			}
		} else if (t.type == 4) {
			fcn_00428ef0(t.u.num);
		} else if (t.type == 2) {
			fcn_00428d50(t.u.num);
		} else if (t.type == 3) {
			fcn_00427c40(g, t.u.num);
		} else if (t.type == 8) {
			fcn_00425fe0(g, t.u.num);
		} else if (t.type == 11) {
			g_6b7eb8 = t.u.num;
			(*(int*) (g + 0x118))++;
		} else if (t.type != 12) {
			sprintf(msg, "Unknown symbol : '%s'", t.u.text);
			fcn_00425bf0(g, *(int*) (g + 0x118), msg);
			fcn_00428720(g);
		}
	} while ((*(unsigned char*) (g + 0x124) & 1) && t.type != 12 && !(t.type == 1 && t.u.num == 10));
	if (t.type == 1 && t.u.num == 10) {
		s = *(struct stack_4291c0**) (g + 0xc28);
		n = s->count;
		if (n > 1 && s->f[n - 1].pos != 0 && s->f[n - 1].open != 0) {
			s->count = n - 1;
			s = *(struct stack_4291c0**) (g + 0xc28);
			if (s->f[s->count].kind == 1) {
				*(int*) (g + 0x118) = s->f[s->count].pos;
			}
		}
	}
	if (t.type == 12) {
		*(int*) (g + 0x124) &= ~1;
	}
	return 0;
}
