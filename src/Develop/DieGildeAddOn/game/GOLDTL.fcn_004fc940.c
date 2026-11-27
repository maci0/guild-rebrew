


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
	char pad8[0x1a0 - 8];
	int count_a;
	int count_b;
	char pad1a8[0x21c - 0x1a8];
} Obj;

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int g_773d48;
extern int g_99f7ac;

void __cdecl gm_GetLawEntry(int kind, Offer* o);
char* __cdecl gm_GetGuildHall(int n);
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, int c, int d);

int __cdecl gm_CalcLaw0x0cTaxSlot(unsigned short id, Slots* s, unsigned char flags)
{
	int amt;
	Offer offer;
	int i;
	int n;
	int v;
	float f;
	char* p;

	gm_GetLawEntry(0xc, &offer);
	amt = offer.amount;
	p = gm_GetGuildHall(1);
	fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	n = (*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].value_1a0) + (*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].value_1a4);
	f = n * (amt * 0.01f);
	if (!(f > 0.0f)) {
		f = 0.0f;
	}
	v = (int) f;
	for (i = 0; i < 6; i++) {
		if (s->used[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	if (n > 0) {
		s->used[i] = 4;
		s->amount[i] = amt;
		s->value[i] = v;
		if (flags & 1) {
			p = gm_GetGuildHall(1);
			p = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
			cm_RequestTransferCurrencyNoKill(*(int*) (p + 2), (*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[id].entity_id), 0, v);
			g_773d48++;
		}
		if (flags & 2) {
			g_99f7ac += v;
		}
	}
	return 1;
}
