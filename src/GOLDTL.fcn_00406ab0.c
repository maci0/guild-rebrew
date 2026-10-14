

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
void __cdecl ch_TakingObject(Task* t);
int __cdecl fcn_004050c0(Task* t);

int __cdecl fcn_00406ab0(char* e, const char* name, char* src, int param)
{
	Task* t;
	char* s;
	char* d;
	char c;

	t = fcn_0040c0a0(e);
	if (t != 0) {
		t->owner = e;
		t->param = param;
		t->state = 0;
		t->run = ch_TakingObject;
		t->kind = 0x31;
		t->next = 0;
		t->flags = 0;
		t->a34 = 0;
		t->a38 = 1;
		strcpy(t->name, name);
		if (src != 0 && *(char**) (src + 0x1ec) != 0) {
			s = *(char**) (*(char**) (src + 0x1ec) + 0x40c);
			if (s != 0) {
				d = t->name2;
				do {
					c = *s;
					s++;
					*d = c;
					d++;
				} while (c != 0);
				return 1;
			}
		}
		fcn_004050c0(t);
	}
	return 0;
}
