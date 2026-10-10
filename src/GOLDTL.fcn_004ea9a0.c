// FUNCTION: GOLD 0x004e8c20
// FUNCTION: GOLDTL 0x004ea9a0

#include <string.h>

// SIZE 0x18
typedef struct {
	unsigned char a;
	int b;
	char c;
	int d;
	char e;
	int f;
} Rec;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad2[0x164 - 2];
	unsigned char group;
	char pad165[0x21c - 0x165];
} Obj;

#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];
extern char g_7f4ca0[];

char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int type);
char* __cdecl gm_AddObjekt(void);
Obj* __cdecl fcn_00508e40(int id);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004e8240(unsigned char a, Obj* o, int b, int c, int d);
void __cdecl fcn_004ea560(Obj* o, int v);
void __cdecl fcn_004ea4b0(Obj* o, int v);

void __cdecl fcn_004ea9a0(void)
{
	int k;
	Obj* cur;
	Rec rec;
	Obj* list[16];
	char* e;
	Obj* o;
	Obj* best;
	int total;
	int found;
	int best_v;
	int v;
	int i;
	int j;

	memset(&rec, 0, sizeof(rec));
	memset(list, 0, sizeof(list));
	rec.b = -1;
	k = 0;
	total = 0;
	for (e = gm_StartFilteredEntitySearch(1, 5, 7); e != 0 && k < 16; e = gm_AddObjekt()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff && !(e[0x5a] & 1)) {
			total++;
			o = &((Obj*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			if (o->group >= 0xd && o->group <= 0x12) {
				for (j = 0; j < 16; j++) {
					if (list[j] == o) {
						break;
					}
				}
				if (j == 16) {
					list[k++] = o;
				}
			}
		}
	}
	if (total < 3 || k == 0) {
		return;
	}
	found = 1;
	for (i = 36; i >= 0 && found != 0; i--) {
		if (((Rec*)g_9a9220)[i].c == 0x22) {
			rec = ((Rec*)g_9a9220)[i];
			found--;
		}
	}
	cur = 0;
	if (rec.b != -1 && (cur = fcn_00508e40(rec.b)) != 0) {
		best_v = gm_WalkEntityChain(cur->id);
	} else {
		best_v = 0;
	}
	best = 0;
	for (j = 0; j < k; j++) {
		v = gm_WalkEntityChain(list[j]->id);
		if (v > best_v) {
			best = list[j];
			best_v = v;
		}
	}
	if (best != 0 && best != cur) {
		if (cur != 0) {
			fcn_004e8240(rec.a, best, 0, 1, 0xff);
			fcn_004ea560(cur, 0x22);
			fcn_004ea4b0(best, 0x22);
		} else {
			fcn_004e8240(rec.a, best, 0, 1, 0xff);
			fcn_004ea4b0(best, 0x22);
		}
	}
}
