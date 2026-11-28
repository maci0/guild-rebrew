#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char gm_EntitySlotTable[];
extern char* gm_CityEntity;
extern unsigned char* lpGebaeudePROT;
extern int g_6652f8[];
extern float g_6652d8[];
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, void* d, int e);
int __cdecl gv_IsGraveSlotFree(void*, int*);
void __cdecl gm_SubObjectNoKill(int, int, int);
void __cdecl gm_AddObjekt(int, int, int);
void __cdecl he_NotifyFriedhofEvent08(char*, void*, void*, int, int, int);

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))
#define MINV(a, b) (((a) < (b)) ? (a) : (b))

double __cdecl log10(double x);
int __cdecl gm_AmountToUnits(int a, unsigned char k);
int __cdecl gm_ConvertUnitsToAmount(int a, unsigned char k);

/* ADDRESS: GOLDTL 0x004f25a0 */
/* ADDRESS: GOLDDE 0x004de660 */
int __cdecl gv_RentGravePlot(char* req)
{
	void* entity1;
	void* entity2;
	void* workers;
	char* slot;
	char* player;
	int type;
	int j;
	int off;

	gm_ResolveEntityById((void**) (&entity1), 0, 0, *(int*) (req + 8));
	if (entity1 == 0 || *(unsigned short*) ((char*) entity1 + 0x27) == 0xffff ||
	    (char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) ((char*) entity1 + 0x27)] == gm_CityEntity) {
		return -1;
	}
	type = *(unsigned char*) entity1;
	if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[type].category != 0x1d) {
		return -2;
	}
	workers = *(void**) ((char*) entity1 + 0x65);
	if (workers == 0) {
		return -3;
	}
	if (!gv_CheckSlotActive(workers, *(int*) (req + 0xc))) {
		return -4;
	}
	gm_ResolveEntityById(0, 0, (void**) (&entity2), *(int*) (req + 4));
	if (entity2 == 0) {
		return -6;
	}
	if (*(int*) (req + 0xc) < 0 || *(int*) (req + 0xc) > 3) {
		return -5;
	}
	slot = FindSlotEntryFiltered(entity2, entity1, 0, (void*) gv_IsGraveSlotFree, *(int*) (req + 0xc));
	if (slot == 0) {
		return -7;
	}
	*(int*) (slot + 4) = *(int*) ((char*) entity2 + 4);
	*(unsigned short*) (slot + 8) = *(unsigned short*) ((char*) entity2 + 0x50);
	*(unsigned short*) (slot + 0xa) = *(unsigned short*) (req + 0x11) + (unsigned short) gm_GameTime.a;
	*(unsigned char*) (slot + 0xc) = 0xff;
	for (j = 0; j < g_6652f8[*(int*) (req + 0xc)]; j++) {
		*(int*) (*(char**) (slot + 0x10) + j * 0x44) = -1;
	}
	if (*(int*) (req + 0x13) > 0) {
		gm_SubObjectNoKill(*(int*) ((char*) entity2 + 4), (unsigned short) ((int*)g_8680b4)[gm_ActiveTownIndex * 189],
			*(int*) (req + 0x13));
		gm_AddObjekt(*(int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) ((char*) entity1 + 0x27)] + 4),
			(unsigned short) ((int*)g_8680b4)[gm_ActiveTownIndex * 189],
			(int) (*(int*) (req + 0x13) * g_6652d8[*(int*) (req + 0xc)]));
		off = *(unsigned short*) ((char*) entity1 + 0x27) * (int)sizeof(ENTITY_RECORD);
		player = gm_EntitySlotTable + off;
		if ((char*) entity2 != player && gm_EntitySlotTable[off + 2] == 6) {
			he_NotifyFriedhofEvent08(player, entity2, entity1, *(int*) (req + 0xc), *(int*) (req + 0x13),
				(int) (*(int*) (req + 0x13) * g_6652d8[*(int*) (req + 0xc)]));
		}
	}
	return 0;
}

/* ADDRESS: GOLD 0x4f24a0 */

/* ADDRESS: GOLDTL 0x004f45b0 */
/* ADDRESS: GOLDDE 0x004e0670 */
int __cdecl gm_CalcScaledWealthValue(unsigned short* e)
{
	double x;
	int pr;

	pr = gm_AmountToUnits(gm_CalcPersonWealth(*e), gm_ActiveTownIndex);
	x = pr;
	x = MAXV(MINV(100000.0, x), 10000.0);
	x = x / (log10(x) + 1.0) * 0.1f;
	return gm_ConvertUnitsToAmount((int) x, gm_ActiveTownIndex);
}
