#include "Develop/DieGildeAddOn/game/event_deal.h"

void __cdecl fcn_00546e40(int a1, int a2, char* a3, int a4, void* a5);




#include <string.h>

void __cdecl fcn_00546e40(int id, int owner, char* name, int amount, void* pos)
{
	int i;
	EVENT_DEAL* t;

	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id == 0) {
			break;
		}
	}
	if (i < 256) {
		t = &g_7d2020[i];
		t->id = id;
		t->owner = owner;
		t->amount = amount;
		t->has_amount = 1;
		t->state = 2;
		strncpy(t->name, name, 0x7f);
		t->pos = *(Pos14*) pos;
	}
}
