#include "Develop/DieGildeAddOn/game/event_deal.h"

void __cdecl he_AddEventDeal(int id, int owner, char* name, int amount, void* pos);




#include <string.h>

void __cdecl he_AddEventDeal(int id, int owner, char* name, int amount, void* pos)
{
	int i;
	EVENT_DEAL* t;

	for (i = 0; i < 256; i++) {
		if (he_EventDeals[i].id == 0) {
			break;
		}
	}
	if (i < 256) {
		t = &he_EventDeals[i];
		t->id = id;
		t->owner = owner;
		t->amount = amount;
		t->has_amount = 1;
		t->state = 2;
		strncpy(t->name, name, 0x7f);
		t->pos = *(Pos14*) pos;
	}
}
