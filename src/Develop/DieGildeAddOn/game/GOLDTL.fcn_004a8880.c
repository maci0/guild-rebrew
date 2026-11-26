

#include <string.h>

typedef struct {
	unsigned short id;
	char pad2[2];
	int h;
	char pad8[0x54];
	int x5c;
	char pad60[0xd0];
	unsigned char x130;
	char pad131[0x35];
	unsigned char x166;
	unsigned char x167;
	unsigned char x168;
	char pad169[0xb3];
} Ent;
// SIZE 0x21c

typedef struct {
	int x0;
	int id;
	unsigned char x8;
	char pad9[7];
	unsigned char x10;
	char pad11[7];
} Rec;
// SIZE 0x18

typedef struct {
	int kind;
	char pad4[0x218];
	Ent* ent;
} Req;
// SIZE 0x220

typedef struct {
	unsigned char type;
	char pad1[3];
	int h;
} Order;
// SIZE 0x8

int __cdecl amt_GetRoleTemplate(int idx, Rec* out);
#include "Develop/DieGildeAddOn/game/aemter.h"
Ent* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned short __cdecl gm_RandomMod(int n);

int __cdecl fcn_004a8880(int a1, Ent* e, Req* req, int a4, Order* out)
{
	Ent* found;
	int h;
	int k;
	int i;
	int n;
	int cnt;
	int tries;
	float score;
	Ent* p;
	Ent* list[6];
	Rec info;
	Rec other;
	OFFICE_SLOT recs[6];

	found = 0;
	if (req->kind == 1) {
		if (e->x168 != 0) {
			return 0;
		}
		h = e->h;
		k = e->x166;
	}
	else if (req->kind == 2) {
		if (req->ent == 0) {
			return 0;
		}
		k = req->ent->x166;
		h = req->ent->h;
	}
	else {
		return 0;
	}
	if (amt_GetRoleTemplate(k, &info) == 0) {
		return 0;
	}
	n = amt_FindOfficeSlotsByKind(info.id, 6, recs);
	for (i = 0, cnt = 0; i < n; i++) {
		if (recs[i].status == 2) {
			cnt++;
			if (recs[i].mplayerid == h) {
				return 0;
			}
		}
	}
	if (cnt > 2) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		list[i] = gm_LookupEntityRecordById(recs[i].mplayerid);
	}
	for (i = n; i < 6; i++) {
		list[i] = 0;
	}
	i = gm_RandomMod(6);
	for (tries = 6; tries != 0; i = (i + 1) % 6) {
		if (list[i] != 0 && h != list[i]->h && gm_CalcEntityFavor(list[i]->id, e->id, 1) < 33.0f &&
			recs[i].status == 1) {
			found = list[i];
			break;
		}
		tries--;
	}
	if (found != 0 && e->x5c != found->h) {
		out->type = 7;
		out->h = found->h;
		return 1;
	}
	if (info.x8 == 3 || info.x8 == 6 || info.x8 == 9) {
		return 0;
	}
	if (e->x130 != 7) {
		return 0;
	}
	i = gm_RandomMod(6);
	for (tries = 6; tries != 0; i = (i + 1) % 6) {
		p = list[i];
		if (p != 0 && h != p->h) {
			if (amt_GetRoleTemplate(p->x166, &other) == 0) {
				return 0;
			}
			if (other.x8 > info.x8 && recs[i].status == 1) {
				score = gm_CalcEntityFavor(p->id, e->id, 1);
				if (gm_RandomMod(0x20) + 40.0f > score) {
					found = list[i];
					break;
				}
			}
		}
		tries--;
	}
	if (found != 0 && e->x5c != found->h) {
		out->type = 7;
		out->h = found->h;
		return 1;
	}
	return 0;
}
