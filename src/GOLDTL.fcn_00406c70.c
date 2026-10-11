// FUNCTION: GOLDTL 0x00406c70

#include <string.h>

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

Task* __cdecl fcn_0040c0a0(char* e);
void __cdecl ch_DroppingObject(Task* t);

int __cdecl fcn_00406c70(char* e, const char* name, const char* name2, int param)
{
	Task* t;

	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->owner = e;
	t->param = param;
	t->state = 0;
	t->run = ch_DroppingObject;
	t->kind = 0x32;
	t->next = 0;
	t->flags = 0;
	t->a34 = 0;
	t->a38 = 2;
	if (name != 0) {
		strcpy(t->name, name);
	} else {
		t->name[0] = 0;
	}
	if (name2 != 0) {
		strcpy(t->name2, name2);
	} else {
		t->name2[0] = 0;
	}
	return 1;
}
