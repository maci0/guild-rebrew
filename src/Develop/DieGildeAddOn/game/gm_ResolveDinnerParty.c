// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x214];
} BANQUET_ENTITY;

// SIZE 0x8
typedef struct {
	BANQUET_ENTITY* ent;
	int value;
} BANQUET_GUEST;

// SIZE 0x34
typedef struct {
	BANQUET_ENTITY* ent;
	BANQUET_GUEST members[4];
	unsigned a;
	unsigned b;
	int text;
	unsigned char count;
} BANQUET_PARTY;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;

unsigned short __cdecl gm_RandomMod(unsigned short range);
int __cdecl amt_GetEffectiveRoleLevel(unsigned short id, int a2);
int __cdecl gm_CalcPersonWealth(unsigned short id);
void __cdecl cm_RequestCopyEntityData(int a1, int a2, int a3, int a4);
void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x00494470 */
int __cdecl gm_ResolveDinnerParty(BANQUET_PARTY* p, int flag)
{
	int i;
	int n;
	int q;
	int sum;
	int x;
	int value;
	int ya;
	int yb;

	if (p == 0) {
		return -1;
	}
	if (p->ent == 0) {
		return -2;
	}
	if (p->a > 5) {
		return -3;
	}
	if (p->b > 5) {
		return -4;
	}
	if (p->count == 0 || p->count > 4) {
		return -5;
	}
	yb = 5 - p->b;
	ya = 5 - p->a;
	n = amt_GetEffectiveRoleLevel(p->ent->slot, 0);
	sum = n / -3 - n / 4 + n + ya + yb;
	for (i = 0; i < p->count; i++) {
		if (p->members[i].ent == 0) {
			return -6;
		}
		value = sum - amt_GetEffectiveRoleLevel(p->members[i].ent->slot, 0);
		if (2 <= value) {
			value = 2;
		}
		else if (value <= -2) {
			value = -2;
		}
		p->members[i].value = value < 2 ? value : 2;
	}
	for (i = 0; i < p->count; i++) {
			switch (p->members[i].value) {
		case -2:
			x = -0x10 - gm_RandomMod(0x10);
			break;
		case -1:
			x = -8 - gm_RandomMod(8);
			break;
		case 0:
			x = gm_RandomMod(8) + 8;
			break;
		case 1:
			x = gm_RandomMod(0x10) + 0x10;
			break;
		case 2:
			x = gm_RandomMod(0x10) + 0x18;
			break;
		}
		if (flag) {
			cm_RequestCopyEntityData(p->ent->id, p->members[i].ent->id, x, 1);
		}
	}
	q = gm_CalcPersonWealth(p->ent->slot);
	p->text = (int) ((float) (10 - p->b - p->a) * q * p->count * 0.001f);
	if (flag) {
		cm_RequestMoveCredits(-1, p->ent->id, *(char*) &gm_ActiveTownIndex, p->text);
	}
	return 0;
}
