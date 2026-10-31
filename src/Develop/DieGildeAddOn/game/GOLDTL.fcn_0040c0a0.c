


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

#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "Develop/Units/Error/error_message.h"


Task* __cdecl fcn_0040c0a0(char* e)
{
	Task* t;
	Task* p;

	t = (Task*) ch_GetFreeQueueEntry();
	if (t == 0) {
		ReportClientMessage("no free task slot");
		return 0;
	}
	memset(t, 0, sizeof(Task));
	if (*(Task**) (e + 0x128) == 0) {
		*(Task**) (e + 0x128) = t;
	} else {
		p = *(Task**) (e + 0x128);
		while (p->next != 0) {
			p = p->next;
		}
		p->next = t;
		t->prev = p;
	}
	t->owner = e;
	t->state = 0;
	t->run = 0;
	t->next = 0;
	t->flags = 0;
	fcn_00405180(e, t);
	return t;
}
