#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/goods_plan.h"

#include "Develop/DieGildeAddOn/game/ai_supply_candidate.h"







#include "Develop/DieGildeAddOn/game/production_goods.h"

extern int g_86805c;

int __cdecl fcn_00503a70(int type);
int __cdecl fcn_00486640(char* a0, int* a1, int a2);

/* ADDRESS: GOLDTL 0x00486640 */
int __cdecl fcn_00486640(char* a0, int* goodsPlan, int a2)
{
	int* p;
	int ingredient;
	int found;
	int idx;
	int i;
	int scale;
	int word;
	int clamp;
	int lim;
	int t;
	int sc;
	int w;
	int n;
	float fl;
	float ratio;
	AI_SUPPLY_CANDIDATE* rec;
	GOODS_PLAN_ENTRY* seg;

	ingredient = 0;
	p = goodsPlan + 1;
	do {
		if (*p < 0) {
			goto next;
		}
		seg = &g_100b0c0[*p];
		word = ((OBJECT_PROTOTYPE*) lpObjektePROT)[goodsPlan[0]].ingredient_amounts[ingredient];
		if (seg->stock < word) {
			if (a2 != 0) {
				return 0;
			}
			if (seg->capacity == 0) {
				return 0;
			}
			if (seg->allocated == 0
			    && seg->goods_id != 0x1c7 && seg->goods_id != 0x1c4
			    && seg->goods_id != 0x1c5 && seg->goods_id != 0x1c6
			    && seg->goods_id != 0x2af && seg->goods_id != 0x2b0
			    && seg->goods_id != 0x1c1 && seg->goods_id != 0x1c2
			    && seg->goods_id != 0x1c3) {
				if (seg->parent_index != -1) {
					if (!fcn_00486640(a0, (int*) &g_100d0c0[seg->parent_index], 0)) {
						return 0;
					}
				} else {
					fcn_00503a70(seg->goods_id);
					found = 0;
					idx = 0;
					i = 0x26;
					rec = g_868c40;
					do {
						if (idx >= g_86805c) {
							return 0;
						}
						if (rec->entity != *(char**) (a0 + 0x16c)
						    && gm_GetBuildingTypeCategory((unsigned char) *rec->entity) != 2
						    && rec->unk_08 != 0) {
							lim = rec->limit;
							w = ((OBJECT_PROTOTYPE*) lpObjektePROT)[goodsPlan[0]].ingredient_amounts[ingredient];
							if (lim >= w) {
								if (*(short*) (rec->entity + 0x27) == *(short*) (*(int*) (a0 + 0x16c) + 0x27)) {
									found = 1;
								} else {
									sc = *(int*) ((char*) goodsPlan + 0x40) >> 1;
									if (sc < 1) {
										sc = 1;
									}
									w = *(unsigned short*) ((char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[goodsPlan[0]] + i);
									t = w * sc - seg->stock - seg->allocated;
									n = (seg->capacity >> 1) - seg->allocated;
									if (t <= n) {
										t = n;
									}
									n = seg->capacity - seg->allocated - 1;
									if (t > n) {
										t = n;
									}
									ratio = (float) *(int*) (a0 + 0x1b8) / seg->price;
									fl = (float) t;
									n = (int) (ratio < fl ? ratio : fl);
									if (n > lim) {
										n = lim;
									}
									if (n >= w) {
										found = 1;
									}
								}
							}
						}
						idx++;
						i += 2;
						rec++;
					} while (!found);
				}
			}
		}
next:
		p++;
		ingredient++;
	} while (ingredient < 4);
	return 1;
}
