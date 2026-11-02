


#include "Develop/DieGildeAddOn/game/ch_action.h"

#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl ch_AttachAni(char* e, char* name, int flag);
int __cdecl fcn_00404f60(CH_ACTION* t);


void __cdecl fcn_004065c0(CH_ACTION* t)
{
	char* e;
	char* s;

	e = t->besitzer;
	if ((*(int*) (e + 0x70) != 0 || *(int*) (e + 0x7c) != 0) && (t->merkmale & 1) == 0) {
		t->zustand = -1;
		return;
	}
	t->merkmale |= 1;
	if (t->zustand == 0) {
		if ((*(unsigned char*) (e + 0x8c) & 0x10) == 0) {
			ch_RemoveQueueEntry((char*) (t));
			return;
		}
		s = ch_AttachAni(e, t->name, 1);
		*(char**) (e + 0x70) = s;
		if (s == 0) {
			ch_RemoveQueueEntry((char*) (t));
			return;
		}
		*(unsigned char*) (s + 0x6c) = 1;
		*(int*) (*(char**) (e + 0x70) + 0x70) &= ~3;
		*(unsigned char*) (*(char**) (e + 0x70) + 0x6d) |= 0x10;
		return;
	}
	if (fcn_00404f60(t) == -1) {
		ch_ClearSitting((unsigned char*) e);
		ch_RemoveQueueEntry((char*) (t));
	}
}
