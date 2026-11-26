#include "Develop/DieGildeAddOn/game/goods_plan.h"

typedef struct Ware {
	unsigned short id;
	char pad2[0x1a];
	int unit;
} Ware;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
extern char* g_773d78;

int __cdecl gm_GetStorageSlotCapacity(char* pkt, int item_id);
int __cdecl gm_GetMsgField(char* pkt, Ware* q);
float __cdecl fcn_0050bb50(int id, unsigned char k);
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
		if ((g_100b0c0[i].flags & 0x20) == 0 && (g_100b0c0[i].flags & 0x200) == 0 && g_100b0c0[i].allocated == 0 && g_100b0c0[i].stock < gm_GetStorageSlotCapacity(pkt, g_100b0c0[i].goods_id) / 4) {
			ratio = fcn_0050bb50(g_100b0c0[i].goods_id, g_773d75) / eval_ObjektPreis2Credits(g_100b0c0[i].goods_id, 100);
			if (ratio < 0.8f) {
				g_100b0c0[i].supplier = 0;
				want = (int) ((1.0f - ratio) * g_100b0c0[i].capacity);
				g_100b0c0[i].requested = want;
				if (want >= g_100b0c0[i].capacity) {
					want = g_100b0c0[i].capacity;
				}
				g_100b0c0[i].requested = want;
				town = gm_FindCityItemHolder(g_100b0c0[i].goods_id);
				if (town != 0) {
					w = fcn_00502cd0(*(int*) (town + 0x14), 1, 0, g_100b0c0[i].goods_id);
					if (w != 0) {
						if (gm_GetMsgField(town, w) - (int) ((unsigned int) (gm_GetStorageSlotCapacity(town, w->id) * w->unit) >> 2) >= 5) {
							g_100b0c0[i].supplier = g_773d78;
						}
					}
				}
			}
		}
	}
}
