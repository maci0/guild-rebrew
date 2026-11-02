#include "Develop/DieGildeAddOn/game/ch_action.h"
#include "Develop/DieGildeAddOn/game/ch_queue.h"

void __cdecl fcn_00435500(char*, char*);


int __cdecl ch_CancelActionQueueWithMotion(char* e)
{
	CH_ACTION* t;

	if (e == 0) {
		return 0;
	}
	t = *(CH_ACTION**) (e + 0x128);
	if (t == 0) {
		return 0;
	}
	t->unbekannt_190 = 1;
	while (t->naechste != 0) {
		ch_RemoveQueueEntry((char*) (t->naechste));
	}
	if (t->art == 0x2e) {
		if (*(int*) (e + 0x70) != 0) {
			fcn_00435500(*(char**) (*(char**) (e + 0x34) + 0x1ec) + 0xf4,
				     *(char**) (*(char**) (e + 0x70) + 0x68));
			*(int*) (e + 0x70) = 0;
		}
		ch_RemoveQueueEntry((char*) (t));
	}
	if ((*(unsigned char*) (e + 0x8c) & 0x10) != 0) {
		ch_ClearSitting((unsigned char*) e);
	}
	return 1;
}

