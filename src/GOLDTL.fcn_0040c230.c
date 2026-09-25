// FUNCTION: GOLD 0x0040b400
// SIZE: 208
// FUNCTION: GOLDTL 0x0040c230
// SIZE: 208

#include <stdarg.h>

typedef struct Task Task;

// SIZE 0x194
struct Task {
	void (__cdecl* run)(Task* t);
	void (__cdecl* done)(Task* t);
	unsigned char level;
	char kind;
	char pad0a[2];
	int state;
	unsigned char flags;
	char pad11[3];
	char* owner;
	char pad18[0x24 - 0x18];
	Task* prev;
	Task* next;
	char pad2c[4];
	int param;
	int a34;
	int a38;
	char pad3c[0xf0 - 0x3c];
	char name[0x40];
	char name2[0x40];
	int a170;
	int a174;
	float a178;
	char pad17c[0x190 - 0x17c];
	unsigned char b190;
	char pad191[3];
};

// SIZE 0x4c
typedef struct {
	void (__cdecl* handler)(Task* t);
	unsigned char kind;
	char name[0x43];
	int nargs;
} Entry;

extern Entry g_14d0c40[];
Task* __cdecl fcn_0040c0a0(char* e);
void __cdecl fcn_004079d0(Task* t);

Task* __cdecl fcn_0040c230(char* e, void (__cdecl* done)(Task* t), unsigned char level, int kind, ...)
{
	Task* t;
	va_list ap;
	int i;

	if (e == 0) {
		return 0;
	}
	if (g_14d0c40[kind].handler == 0) {
		kind = 0;
	}
	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->run = g_14d0c40[kind].handler;
	t->kind = (char) kind;
	t->owner = e;
	t->state = 0;
	va_start(ap, kind);
	for (i = 0; i < g_14d0c40[(unsigned char) t->kind].nargs; i++) {
		(&t->param)[i] = va_arg(ap, int);
	}
	va_end(ap);
	t->next = 0;
	t->flags = 0;
	t->done = done;
	t->level = level;
	if (t->run == fcn_004079d0) {
		t->param = (unsigned char) t->kind;
	}
	return t;
}
