// FUNCTION: GOLD 0x00405cb0
// SIZE: 144
// FUNCTION: GOLDTL 0x00406850
// SIZE: 144

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
void __cdecl fcn_004066d0(Task* t);
void __cdecl fcn_0041d9e0(const char* msg);

Task* __cdecl fcn_00406850(char* e, const char* name, const char* name2, int a, int b, int c)
{
	Task* t;

	t = fcn_0040c0a0(e);
	if (t == 0) {
		return 0;
	}
	t->run = fcn_004066d0;
	t->kind = 0x34;
	strcpy(t->name, name);
	strcpy(t->name2, name2);
	t->a170 = a;
	t->a174 = b;
	if (*(int*) &t->a178 == -1) {
		fcn_0041d9e0("task value unset");
	}
	*(int*) &t->a178 = c;
	return t;
}
