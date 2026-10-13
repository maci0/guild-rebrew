#include "client_types.h"
// FUNCTION: GOLDTL 0x40c120

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

/* SIZE 0x4c. nargs sits at +0x48, the dword the copy loop indexes. */
typedef struct {
	void (__cdecl* handler)(Task* t);
	unsigned char kind;
	char name[0x43];
	int nargs;
} Entry;

extern Entry_14d0c40 g_14d0c40[];
Task* __cdecl fcn_0040c0a0(char* e);
void __cdecl fcn_004079d0(Task* t);
void __cdecl fcn_00405180(char* e, Task* t);
int __cdecl fcn_004050c0(Task* t);

/* Build a task for kind and copy the trailing stack dwords into its
 * params. i is the copy counter, so i = -1 reuses ecx (or ecx,-1) for
 * the kind 0x33 checks. Those checks are two separate ifs: an else
 * would jump over the second test instead of retesting param. */
Task* __cdecl fcn_0040c120(char* e, int kind, ...)
{
	Task* t;
	va_list ap;
	int i;

	if (e == 0) {
		return 0;
	}
	if (((Entry*) g_14d0c40)[kind].handler == 0) {
		kind = 0;
	}
	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->run = ((Entry*) g_14d0c40)[kind].handler;
	t->kind = (char) kind;
	t->owner = e;
	t->state = 0;
	va_start(ap, kind);
	for (i = 0; i < ((Entry*) g_14d0c40)[(unsigned char) t->kind].nargs; i++) {
		(&t->param)[i] = va_arg(ap, int);
	}
	va_end(ap);
	t->next = 0;
	t->flags = 0;
	if (kind == 0x33) {
		i = -1;
		if (t->a34 != i && t->a38 == i) {
			__asm { int 3 }
		}
		if (t->param == 0 && t->a34 != i) {
			goto drop;
		}
		if (t->param != 0 && t->a34 == i) {
			goto drop;
		}
	}
	fcn_00405180(e, t);
	if (t->run == fcn_004079d0) {
		t->param = (unsigned char) t->kind;
	}
	return t;
drop:
	fcn_004050c0(t);
	return 0;
}
