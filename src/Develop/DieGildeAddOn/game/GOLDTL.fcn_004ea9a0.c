


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
#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "client_types.h"
extern Rec18_68da68 amt_OfficeSlots[42];


char* __cdecl gm_StartFilteredEntitySearch(int mode, int kind, int type);
char* __cdecl gm_AddObjekt(void);
ENTITY_RECORD* __cdecl gm_LookupEntityRecordById(int id);
#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/aemter.h"
void __cdecl amt_NotifyOfficeLost(ENTITY_RECORD* o, int v);
void __cdecl amt_NotifyOfficeAppointed(ENTITY_RECORD* o, int v);

void __cdecl amt_FillOffice0x22FromRichest(void)
{
	int k;
	ENTITY_RECORD* cur;
	Rec rec;
	ENTITY_RECORD* list[16];
	char* e;
	ENTITY_RECORD* o;
	ENTITY_RECORD* best;
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
	for (e = gm_StartFilteredEntitySearch(1, 5, 7); e != 0 && k < 16; e = gm_FindNextFilteredEntity()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff && !(e[0x5a] & 1)) {
			total++;
			o = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (e + 0x27)];
			if (o->unk_164 >= 0xd && o->unk_164 <= 0x12) {
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
		if (((Rec*)amt_OfficeSlots)[i].c == 0x22) {
			rec = ((Rec*)amt_OfficeSlots)[i];
			found--;
		}
	}
	cur = 0;
	if (rec.b != -1 && (cur = gm_LookupEntityRecordById(rec.b)) != 0) {
		best_v = gm_WalkEntityChain(cur->entity_index);
	} else {
		best_v = 0;
	}
	best = 0;
	for (j = 0; j < k; j++) {
		v = gm_WalkEntityChain(list[j]->entity_index);
		if (v > best_v) {
			best = list[j];
			best_v = v;
		}
	}
	if (best != 0 && best != cur) {
		if (cur != 0) {
			amt_SendOfficeCommand(rec.a, (unsigned char*) best, 0, 1, 0xff);
			amt_NotifyOfficeLost(cur, 0x22);
			amt_NotifyOfficeAppointed(best, 0x22);
		} else {
			amt_SendOfficeCommand(rec.a, (unsigned char*) best, 0, 1, 0xff);
			amt_NotifyOfficeAppointed(best, 0x22);
		}
	}
}
