


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
	char pad8[0x1a8 - 8];
	int count;
	char pad1ac[0x21c - 0x1ac];
} Obj;

extern char gm_EntitySlotTable[];
extern unsigned char gm_ActiveTownIndex;
extern int g_99f768;

void __cdecl gm_GetLawEntry(int kind, Offer* o);
char* __cdecl gm_GetGuildHall(int n);
char* __cdecl gm_QueryEntities(int obj, int mode, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, char c, int d);
int __cdecl gm_AccumulateTyped2(Obj* o);

int __cdecl gm_CalcLaw0x0dTaxSlot(unsigned short id, Slots* s, unsigned char flags)
{
	int amt;
	Offer offer;
	int i;
	int n;
	int v;
	float f;
	char* p;

	gm_GetLawEntry(0xd, &offer);
	amt = offer.amount;
	p = gm_GetGuildHall(1);
	gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	for (i = 0; i < 6; i++) {
		if (s->used[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	n = ((Obj*)gm_EntitySlotTable)[id].count;
	f = n * (amt * 0.01f);
	if (!(f > 0.0f)) {
		f = 0.0f;
	}
	v = (int) f;
	if (n > 0) {
		s->used[i] = 3;
		s->value[i] = v;
		s->amount[i] = amt;
		if (flags & 1) {
			p = gm_GetGuildHall(1);
			p = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
			if (gm_AccumulateTyped2(&((Obj*)gm_EntitySlotTable)[id]) >= v) {
				cm_RequestTransferCurrencyNoKill(*(int*) (p + 2), ((Obj*)gm_EntitySlotTable)[id].owner, (*(char*)&gm_ActiveTownIndex), v);
			}
		}
		if (flags & 2) {
			g_99f768 += v;
			((Obj*)gm_EntitySlotTable)[id].count = 0;
		}
	}
	return 1;
}
