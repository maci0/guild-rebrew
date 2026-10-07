// FUNCTION: GOLDTL 0x00428ef0

#include <stdlib.h>
#include <string.h>

typedef int (__cdecl* ScriptFn)();

typedef struct Cmd {
	char name[0x20];
	int argc;
	int types[8];
	ScriptFn fn;
	int ret;
} Cmd;
// SIZE 0x48

typedef struct Vm {
	char pad0[0x118];
	int line;
	char pad11c[0xc5c - 0x11c];
	Cmd* cmd;
	ScriptFn wait;
	int args[8];
	int waiting;
} Vm;
// SIZE 0xc88

extern char* g_6b7e98;
extern int g_6b7eb4;
extern char g_14cb440[];
extern int g_14cb8ec;

int __cdecl fcn_00428800(int);
void __cdecl fcn_00425bf0(Vm* g, int h, const char* msg);
void __cdecl fcn_00428720(Vm*);
int __cdecl fcn_0040c630();

int __cdecl fcn_00428ef0(Cmd* c)
{
	int result;
	int args[8];
	union {
		char c;
		int i;
	} u;
	char strs[8][0x60];
	char* d;
	char* s;
	int v;
	int i;
	int k;
	char ch;

	((Vm*) g_6b7e98)->line++;
	result = -99;
	for (i = 0; i < c->argc; i++) {
		v = fcn_00428800(0);
		result = v;
		if (c->types[i] == 7) {
			args[i] = v;
		} else if (c->types[i] == 1) {
			args[i] = v;
		} else if (c->types[i] == 2) {
			u.c = (char) v;
			args[i] = u.i;
		} else if (c->types[i] == 6) {
			strcpy(strs[i], g_14cb440);
			args[i] = (int) strs[i];
		}
	}
	if (c->argc != 0 && g_6b7eb4 != 0xd) {
		fcn_00425bf0((Vm*) g_6b7e98, ((Vm*) g_6b7e98)->line, "Expecting ')'...possible wrong parameter-count");
		fcn_00428720((Vm*) g_6b7e98);
		return 0;
	}
	if (c->argc == 0) {
		((Vm*) g_6b7e98)->line++;
	}
	switch (c->argc) {
	case 0:
		result = c->fn();
		break;
	case 1:
		result = c->fn(&args[0]);
		break;
	case 2:
		result = c->fn(&args[0], &args[1]);
		break;
	case 3:
		result = c->fn(&args[0], &args[1], &args[2]);
		break;
	case 4:
		result = c->fn(&args[0], &args[1], &args[2], &args[3]);
		break;
	case 5:
		result = c->fn(&args[0], &args[1], &args[2], &args[3], &args[4]);
		break;
	case 6:
		result = c->fn(&args[0], &args[1], &args[2], &args[3], &args[4], &args[5]);
		break;
	case 7:
		result = c->fn(&args[0], &args[1], &args[2], &args[3], &args[4], &args[5], &args[6]);
		break;
	}
	if (c->ret == 7) {
		result = g_14cb8ec;
	}
	if ((((Vm*) g_6b7e98)->waiting == 1 && ((Vm*) g_6b7e98)->wait != 0) || ((Vm*) g_6b7e98)->wait == fcn_0040c630) {
		for (i = 0; i < c->argc; i++) {
			((Vm*) g_6b7e98)->args[i] = args[i];
			if (c->types[i] == 6) {
				((Vm*) g_6b7e98)->args[i] = (int) malloc(0x60);
				s = strs[i];
				d = (char*) ((Vm*) g_6b7e98)->args[i];
				do {
					ch = *s++;
					*d++ = ch;
				} while (ch != 0);
			}
		}
		((Vm*) g_6b7e98)->cmd = c;
	}
	return result;
}
