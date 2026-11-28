


#include <string.h>

#include "Develop/DieGildeAddOn/game/event_deal.h"

#pragma pack(1)
// SIZE 0x1e
typedef struct {
	int id;
	EVENT_DEAL* deal;
	char* tail;
	int amount;
	Pos14 pos;
} Entry;

// SIZE 0x21d
typedef struct {
	int width;
	char pad4[0x31 - 4];
	int height;
	Entry entries[16];
	int total;
	int count;
} Summary;
#pragma pack()

// SIZE 0x98
typedef struct {
	int count;
	int ids[36];
	int special;
} Sorted;


char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int owner);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl gm_CollectBuildingObjectSlots(char* obj, Sorted* out);

/* ADDRESS: GOLDDE 0x004f90d0 */
int __cdecl gm_BuildDealSummary(int owner, Summary* out)
{
	Sorted sorted;
	int k;
	EVENT_DEAL* d;
	char* p;
	int i;

	memset(out, 0, sizeof(Summary));
	p = gm_StartFilteredEntitySearch(1, 4, owner);
	while (p != 0) {
		gm_CollectBuildingObjectSlots(p, &sorted);
		if (sorted.special != 0xffff && sorted.special == owner) {
			out->width += 0xe;
			out->height += 0xe;
			break;
		}
		p = gm_FindNextFilteredEntity();
	}
	k = 0;
	for (i = 0; i < 256; i++) {
		d = &he_EventDeals[i];
		if (d->id != 0 && d->owner == owner) {
			out->entries[k].id = d->id;
			if (d->has_amount != 0) {
				out->entries[k].amount = d->amount;
			}
			out->entries[k].pos = d->pos;
			out->entries[k].tail = d->name;
			if (d->has_amount != 0) {
				out->total -= d->amount;
			}
			out->entries[k].deal = d;
			out->count++;
			k++;
		}
	}
	return 0;
}
