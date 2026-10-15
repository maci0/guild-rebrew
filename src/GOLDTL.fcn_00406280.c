


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

extern float g_6628a8;
void __cdecl fcn_00404300(char* e, char* name, int n);
int __cdecl fcn_004042b0(char* e);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
void __cdecl fcn_004045c0(char* e);

void __cdecl fcn_00406280(Task* t)
{
	char* e;
	char* s;

	e = t->owner;
	if (t->b190 != 0 && *(char**) (e + 0x70) != 0 &&
	    *(unsigned char*) (*(char**) (e + 0x70) + 0x6c) > 2) {
		*(unsigned char*) (*(char**) (e + 0x70) + 0x6c) = 2;
	}
	if (t->state == 0) {
		if (t->param == -1) {
			*(unsigned short*) (e + 0x8c) |= 2;
		}
		fcn_00404300(e, t->name, t->param < 1 ? 1 : t->param);
	} else if (t->b190 != 0 || t->param != -1) {
		if (t->param == -1) {
			*(unsigned short*) (e + 0x8c) &= ~2;
		}
		if (fcn_004042b0(e)) {
			fcn_004050c0((char*) (t));
			fcn_004045c0(e);
		}
	}
	s = *(char**) (e + 0x70);
	if (s != 0 && t->a178 != g_6628a8) {
		*(float*) (s + 0x60) = t->a178;
	}
}
