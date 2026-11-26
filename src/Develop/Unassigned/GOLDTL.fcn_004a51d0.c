typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;
// SIZE 0x41
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;

typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

typedef struct Def {
	char pad0[0x10];
	int mask;
} Def;

extern char* lpObjektePROT;

Def* __cdecl fcn_005c61e0(int id);
int __cdecl fcn_005c6270(char* e, int id);

/* ADDRESS: GOLDTL 0x004a51d0 */
void __cdecl gm_CheckEntityObjectSlots(char* entity, int slotCount, Slot* slots, Counts* counts)
{
	char* it;
	Def* d;
	int i;

	for (i = 0; i < slotCount; i++) {
		slots[i].b = -1;
		slots[i].a = 0;
	}
	counts->blocked = 0;
	counts->free = 0;
	counts->total = 0;
	for (it = *(char**) (entity + 0x178); it != 0; it = *(char**) (it + 0x3f)) {
		if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[*(unsigned short*) it].kind) == 9) {
			continue;
		}
		counts->total++;
		for (i = 0; i < slotCount; i++) {
			if (*(unsigned short*) it == slots[i].id) {
				d = fcn_005c61e0(*(unsigned short*) it);
				if (d == 0) {
					slots[i].a = -1;
					counts->blocked++;
					slots[i].item = 0;
					slots[i].b = -1;
				} else if ((d->mask & *(int*) (entity + 0x1ec)) == 0 && fcn_005c6270(entity, *(unsigned short*) it) == 0) {
					counts->free++;
					slots[i].a = *(int*) (it + 0xe);
					slots[i].b = *(int*) (it + 2);
					slots[i].item = it;
				} else {
					slots[i].a = -1;
					counts->blocked++;
					slots[i].b = *(int*) (it + 2);
					slots[i].item = it;
				}
				break;
			}
		}
	}
	for (i = 0; i < slotCount; i++) {
		if (slots[i].b == -1) {
			d = fcn_005c61e0(slots[i].id);
			if (d != 0 && (d->mask & *(int*) (entity + 0x1ec)) != 0) {
				counts->blocked++;
			}
		}
	}
}
