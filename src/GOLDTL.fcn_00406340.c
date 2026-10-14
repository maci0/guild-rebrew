


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
	char pad34[0xf0 - 0x34];
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
void __cdecl fcn_00406280(Task* t);

int __cdecl fcn_00406340(char* e, const char* name, int param)
{
	Task* t;

	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->param = param;
	t->owner = e;
	t->state = 0;
	t->run = fcn_00406280;
	t->kind = 0x2e;
	t->a178 = 1.0f;
	t->next = 0;
	t->flags = 0;
	strcpy(t->name, name);
	return 1;
}
