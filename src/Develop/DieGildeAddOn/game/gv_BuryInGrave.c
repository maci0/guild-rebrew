#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char* lpGebaeudePROT;
extern char* gm_CityEntity;
extern int g_6652f8[];
extern int gm_GameTime;
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
void __cdecl gm_ResolveEntityById(void**, void**, void**, int);
int __cdecl gv_CheckSlotActive(int, int);
void* __cdecl gv_GetSlotEntry(int, int, char);

#pragma pack(push, 1)
typedef struct PoolEntry5 {
	int a;
	char b;
} PoolEntry5;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x004f2350 */
/* ADDRESS: GOLDDE 0x004de410 */
int __cdecl gv_BuryInGrave(int e)
{
	char* p;
	char* q;
	char* ent;
	char* slot;
	int* base;
	int* cur;
	int* best;
	int i;
	int n;
	int kind;
	int slot_index;

	gm_ResolveEntityById((void**) &p, 0, 0, *(int*) (e + 8));
	if (p == 0 || *(unsigned short*) (p + 0x27) == 0xffff
		|| ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (p + 0x27)]) == gm_CityEntity) {
		return -1;
	}
	kind = *(unsigned char*) p;
	if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[kind].category)) != 0x1d) {
		return -2;
	}
	ent = *(char**) (p + 0x65);
	if (ent == 0) {
		return -3;
	}
	if (gv_CheckSlotActive((int) ent, *(int*) (e + 0xc)) == 0) {
		return -4;
	}
	gm_ResolveEntityById(0, 0, (void**) &q, *(int*) (e + 4));
	if (q == 0) {
		return -6;
	}
	slot_index = *(int*) (e + 0xc);
	slot = (char*) gv_GetSlotEntry((int) ent, slot_index, *(char*) (e + 0x10));
	if (slot == 0 || *(short*) (slot + 8) != *(short*) (q + 0x50)) {
		return -7;
	}
	base = *(int**) (slot + 0x10);
	n = g_6652f8[slot_index];
	best = base;
	cur = base;
	for (i = 0; i < n; i++, cur += 0x11) {
		if (*best == -1) {
			break;
		}
		if (*cur == -1) {
			best = base + i * 0x11;
			break;
		}
		if (best[0x10] > cur[0x10]) {
			best = cur;
		}

	}
	*best = *(int*) (q + 4);
	strcpy((char*) best + 4, q + 0x30);
	strcpy((char*) best + 0x14, q + 0x40);
	*(PoolEntry5*) ((char*) best + 0x24) = *(PoolEntry5*) (q + 0x80);
	*(int*) ((char*) best + 0x2c) = *(unsigned char*) (q + 0x167);
	*(int*) ((char*) best + 0x30) = *(unsigned char*) (q + 0xd);
	*(int*) ((char*) best + 0x34) = *(unsigned char*) (q + 0x164);
	*(int*) ((char*) best + 0x38) = *(unsigned char*) (q + 9);
	*(int*) ((char*) best + 0x40) = gm_GameTime;
	*(int*) ((char*) best + 0x3c) = *(int*) (q + 0x18c);
	return 0;
}
