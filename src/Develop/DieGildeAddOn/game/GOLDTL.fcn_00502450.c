#include "Develop/DieGildeAddOn/game/season_slots.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#pragma pack(push, 1)
typedef struct {
	char kind;
	char pad[0x40];
} SEASON_SLOT_KIND_HDR;
#pragma pack(pop)
// SIZE 0x41

extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_665b80;
extern double g_665b78;

/* ADDRESS: GOLDTL 0x00502450 */
int __cdecl gm_CalcTownSlotTargetStock(int a, int b)
{
	unsigned short w;
	OBJECT_PROTOTYPE* o;

	w = g_85ab80[a].slots[b].objekt_id;
	o = &((OBJECT_PROTOTYPE*)lpObjektePROT)[w];
	if ((*(char *)&o->kind) == 0x17 || (*(char *)&o->kind) == 0x25) {
		return 0;
	}
	if (a == 0) {
		return (int) (gm_CityPopulation * g_85ab80[0].slots[b].unk_08 * g_665b80 + 0.5);
	}
	return (int) (g_85ab80[a].unk_00 * g_85ab80[a].slots[b].unk_08 * g_665b78);
}

extern float flt_0_0;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

/* ADDRESS: GOLDTL 0x005024e0 */
int __cdecl gm_CalcTownSlotProductionSupply(int a, int b)
{
	char* c;
	int sum;
	int j;
	unsigned char* e;

	sum = 0;
	c = (char*) &g_85ab80[a].slots[b].objekt_id;
	if (c[0x40] == 0) {
		return 0;
	}
	for (j = 0; j < 4; j++) {
		if (c[0x40 + j * 8] != 0) {
			for (e = gm_StartFilteredEntitySearch(1, 5, *(unsigned char*) (c + 0x40 + j * 8)); e != 0; e = gm_FindNextFilteredEntity()) {
				sum = (int) (sum + *(float*) (c + 0x44 + j * 8));
			}
		}
	}
	sum = (int) (sum * 0.5);
	if (*(float*) (c + 0x24) != flt_0_0) {
		sum = (int) (*(float*) (c + 0x24) / *(float*) (c + 0x20) * sum);
	}
	return sum;
}
