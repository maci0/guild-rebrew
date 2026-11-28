


// SIZE 0x24
typedef struct {
	char pad0[0x18];
	int amount;
	char pad1c[0x24 - 0x1c];
} Offer;

// SIZE 0x38
typedef struct {
	unsigned char used[6];
	char pad6[2];
	int value[6];
	int amount[6];
} Slots;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int owner;
	char pad8[0x19c - 8];
	int count;
	char pad1a0[0x21c - 0x1a0];
} Obj;

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int gm_QueuedCommandCount;
extern int g_99f724;

void __cdecl gm_GetLawEntry(int kind, Offer* o);
char* __cdecl gm_GetGuildHall(int n);
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, int c, int d);

int __cdecl gm_ApplySteuerLaw0aToSlots(unsigned short id, Slots* slots, unsigned char flags)
{
	Offer offer;
	int i;
	int wealth;
	int tax_amount;
	float calc_amount;
	char* treasury;

	gm_GetLawEntry(10, &offer);
	for (i = 0; i < 6; i++) {
		if (slots->used[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	wealth = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].value_19c);
	calc_amount = wealth * (offer.amount * 0.01f);
	if (!(calc_amount > 0.0f)) {
		calc_amount = 0.0f;
	}
	tax_amount = (int) calc_amount;
	if (wealth > 0) {
		slots->used[i] = 2;
		slots->value[i] = tax_amount;
		slots->amount[i] = offer.amount;
		if (flags & 1) {
			treasury = gm_GetGuildHall(1);
			treasury = fcn_00502cd0(*(int*) (treasury + 0x5d), 2, 6, 0, 0x115);
			cm_RequestTransferCurrencyNoKill(*(int*) (treasury + 2), (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), 0, tax_amount);
			gm_QueuedCommandCount++;
		}
		if (flags & 2) {
			g_99f724 += tax_amount;
		}
	}
	return 1;
}
