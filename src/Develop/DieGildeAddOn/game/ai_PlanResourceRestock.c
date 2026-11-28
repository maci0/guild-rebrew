#include "Develop/DieGildeAddOn/game/goods_plan.h"

typedef struct Ware {
	unsigned short id;
	char pad2[0x1a];
	int unit;
} Ware;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;
extern char* gm_MarketEntity;

int __cdecl gm_GetStorageSlotCapacity(char* pkt, int item_id);
int __cdecl gm_GetMsgField(char* pkt, Ware* q);
float __cdecl gm_GetSeasonPrice(int id, unsigned char k);
float __cdecl eval_ObjektPreis2Credits(int id, int pct);
char* __cdecl gm_FindCityItemHolder(int id);
Ware* __cdecl fcn_00502cd0(int, int, int, int);

/* ADDRESS: GOLDTL 0x0047e0e0 */
void __cdecl ai_PlanResourceRestock(int building, char* pkt)
{
	float ratio;
	char* town;
	Ware* w;
	int want;
	int i;

	for (i = 0; i < ai_ResourceCount; i++) {
		if ((ai_ResourceRequests[i].flags & 0x20) == 0 && (ai_ResourceRequests[i].flags & 0x200) == 0 && ai_ResourceRequests[i].allocated == 0 &&
			ai_ResourceRequests[i].stock < gm_GetStorageSlotCapacity(pkt, ai_ResourceRequests[i].goods_id) / 4) {
			ratio = gm_GetSeasonPrice(ai_ResourceRequests[i].goods_id, gm_ActiveTownIndex) / eval_ObjektPreis2Credits(ai_ResourceRequests[i].goods_id, 100);
			if (ratio < 0.8f) {
				ai_ResourceRequests[i].supplier = 0;
				want = (int) ((1.0f - ratio) * ai_ResourceRequests[i].capacity);
				ai_ResourceRequests[i].requested = want;
				if (want >= ai_ResourceRequests[i].capacity) {
					want = ai_ResourceRequests[i].capacity;
				}
				ai_ResourceRequests[i].requested = want;
				town = gm_FindCityItemHolder(ai_ResourceRequests[i].goods_id);
				if (town != 0) {
					w = fcn_00502cd0(*(int*) (town + 0x14), 1, 0, ai_ResourceRequests[i].goods_id);
					if (w != 0) {
						if (gm_GetMsgField(town, w) - (int) ((unsigned int) (gm_GetStorageSlotCapacity(town, w->id) * w->unit) >> 2) >= 5) {
							ai_ResourceRequests[i].supplier = gm_MarketEntity;
						}
					}
				}
			}
		}
	}
}
