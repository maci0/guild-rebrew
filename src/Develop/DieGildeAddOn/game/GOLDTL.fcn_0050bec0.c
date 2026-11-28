#pragma pack(push, 1)
typedef struct BUILDING_SLOT_PROTO {
	char pad0[0x22];
	unsigned char cnt;
	unsigned short slot[0x40];
	char pad[0x24d - 0xa3];
} BUILDING_SLOT_PROTO;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct {
	char kind;
	char pad[0x40];
} Obj50bec0;
#pragma pack(pop)
// SIZE 0x24d, 0x41

extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;

/* ADDRESS: GOLDTL 0x0050bec0 */
int __cdecl gm_CollectBuildingSlotObjects(unsigned char* s, int* out)
{
	BUILDING_SLOT_PROTO* k;
	int n;
	int i;
	int w;

	n = 0;
	k = &((BUILDING_SLOT_PROTO*)lpGebaeudePROT)[*s];
	for (i = 0; i < 0x40; i++) {
		if (k->slot[i] == 0) {
			break;
		}
		w = k->slot[i] & 0x7fff;
		if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[w].kind) != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = w;
		}
	}
	return n;
}

/* ADDRESS: GOLD 0x00508cf0 */
/* ADDRESS: GOLDTL 0x0050bf30 */
/* ADDRESS: GOLDDE 0x004f6e90 */
int __cdecl gm_CollectBuildingSubObjects(unsigned char* s, unsigned short* key, int* out)
{
	BUILDING_SLOT_PROTO* k;
	OBJECT_PROTOTYPE* o;
	int n;
	int i;
	int w;

	n = 0;
	k = &((BUILDING_SLOT_PROTO*)lpGebaeudePROT)[*s];
	for (i = 0; i < k->cnt; i++) {
		if ((unsigned short) (k->slot[i] & 0x7fff) == *key) {
			break;
		}
	}
	if (i >= k->cnt) {
		return 0;
	}
	for (i++; i < 0x40; i++) {
		if (k->slot[i] == 0) {
			break;
		}
		w = k->slot[i] & 0x7fff;
		o = &((OBJECT_PROTOTYPE*)lpObjektePROT)[w];
		if ((*(char *)&o->kind) == 2 || (*(char *)&o->kind) == 6) {
			break;
		}
		if ((*(char *)&o->kind) != 0x21) {
			n++;
		}
		if (out != 0) {
			out[n] = w;
		}
	}
	return n;
}
