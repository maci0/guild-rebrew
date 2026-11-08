

#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_action.h"

CH_ACTION* __cdecl ch_NewAction(char* e);
void __cdecl ch_TakingObject(CH_ACTION* t);
#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl fcn_00406ab0(char* e, const char* name, char* src, int param)
{
	CH_ACTION* t;
	char* s;
	char* d;
	char c;

	t = ch_NewAction(e);
	if (t != 0) {
		t->besitzer = e;
		t->parameter = param;
		t->zustand = 0;
		t->ausfuehren = ch_TakingObject;
		t->art = 0x31;
		t->naechste = 0;
		t->merkmale = 0;
		t->unbekannt_034 = 0;
		t->unbekannt_038 = 1;
		strcpy(t->name, name);
		if (src != 0 && *(char**) (src + 0x1ec) != 0) {
			s = *(char**) (*(char**) (src + 0x1ec) + 0x40c);
			if (s != 0) {
				d = t->name_2;
				do {
					c = *s;
					s++;
					*d = c;
					d++;
				} while (c != 0);
				return 1;
			}
		}
		ch_RemoveQueueEntry((char*) (t));
	}
	return 0;
}
