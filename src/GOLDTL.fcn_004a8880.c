

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

int __cdecl fcn_004e8b40(int idx, Rec* out);
int __cdecl fcn_004e8b80(int kind, int max, Rec* out);
Ent* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
unsigned short __cdecl gm_RandomMod(int n);

int __cdecl fcn_004a8880(int a1, Ent* e, Req* req, int a4, Order* out)
{
	Ent* found;
	int h;
	int k;
	int i;
	int n;
	int cnt;
	int t;
	float d;
	Ent* p;
	Ent* list[6];
	Rec info;
	Rec other;
	Rec recs[6];

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
	if (fcn_004e8b40(k, &info) == 0) {
		return 0;
	}
	n = fcn_004e8b80(info.id, 6, recs);
	for (i = 0, cnt = 0; i < n; i++) {
		if (recs[i].x10 == 2) {
			cnt++;
			if (recs[i].id == h) {
				return 0;
			}
		}
	}
	if (cnt > 2) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		list[i] = fcn_00508e40(recs[i].id);
	}
	for (i = n; i < 6; i++) {
		list[i] = 0;
	}
	i = gm_RandomMod(6);
	for (t = 6; t != 0; i = (i + 1) % 6) {
		if (list[i] != 0 && h != list[i]->h && fcn_0050f980(list[i]->id, e->id, 1) < 33.0f &&
			recs[i].x10 == 1) {
			found = list[i];
			break;
		}
		t--;
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
	for (t = 6; t != 0; i = (i + 1) % 6) {
		p = list[i];
		if (p != 0 && h != p->h) {
			if (fcn_004e8b40(p->x166, &other) == 0) {
				return 0;
			}
			if (other.x8 > info.x8 && recs[i].x10 == 1) {
				d = fcn_0050f980(p->id, e->id, 1);
				if (gm_RandomMod(0x20) + 40.0f > d) {
					found = list[i];
					break;
				}
			}
		}
		t--;
	}
	if (found != 0 && e->x5c != found->h) {
		out->type = 7;
		out->h = found->h;
		return 1;
	}
	return 0;
}
