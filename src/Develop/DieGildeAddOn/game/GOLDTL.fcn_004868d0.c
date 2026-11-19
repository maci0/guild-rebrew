#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"

#include "Develop/DieGildeAddOn/game/goods_plan.h"

#include "Develop/DieGildeAddOn/game/ai_supply_candidate.h"







#include "Develop/DieGildeAddOn/game/production_goods.h"
























 

extern int g_86805c;

int __cdecl fcn_00503a70(int type);
int __cdecl fcn_004868d0(char* a0, int* a1);

/* ADDRESS: GOLDTL 0x004868d0 */
int __cdecl fcn_004868d0(char* actor, int* a1)
{
	int* p;
	int off;
	int t;
	int idx;
	int n;
	int w;
	int limit;
	int scale;
	float fl;
	float ratio;
	GOODS_PLAN_ENTRY* seg;
	AI_SUPPLY_CANDIDATE* rec;
	PRODUCTION_GOODS_RECORD* rp;

	off = 0x26;
	p = a1 + 1;
	do {
		if (*p < 0) {
			goto next;
		}
		seg = &g_100b0c0[*p];
		seg->state_30 = seg->state_30 < a1[18] ? seg->state_30 : a1[18];
		seg->flags |= 2;
		if (seg->goods_id == 0x1c7 || seg->goods_id == 0x1c4
		    || seg->goods_id == 0x1c5 || seg->goods_id == 0x1c6
		    || seg->goods_id == 0x2af || seg->goods_id == 0x2b0
		    || seg->goods_id == 0x1c1 || seg->goods_id == 0x1c2
		    || seg->goods_id == 0x1c3 || seg->goods_id == 0x225
		    || seg->goods_id == 0x226 || seg->goods_id == 0x227
		    || seg->goods_id == 0x293 || seg->goods_id == 0x294
		    || seg->goods_id == 0x295) {
			rp = &g_100d0c0[seg->parent_index];
			if ((rp->amount + rp->unk_3c) * 4 < rp->unk_40) {
				w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
				if (seg->stock + seg->allocated < w * 4) {
					seg->flags |= 0x10;
				}
			}
		} else if (seg->parent_index != -1) {
			rp = &g_100d0c0[seg->parent_index];
			rp->unk_48 = rp->unk_48 < a1[18] ? rp->unk_48 : a1[18];
			rp->flags |= 2;
			if ((rp->amount + rp->unk_3c) * 4 < rp->unk_40) {
				if (rp->unk_40 > *(unsigned short*) (g_item_def_table + rp->goods_id * 0x41 + 0x36)) {
					rp->flags |= 8;
				}
				fcn_004868d0(actor, (int*) rp);
			}
		} else {
			w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
			if (seg->stock + seg->allocated < w * 4) {
				fcn_00503a70(seg->goods_id);
				for (idx = 0, rec = g_868c40; idx < g_86805c; idx++, rec++) {
					if (rec->entity != *(char**) (actor + 0x16c)
					    && gm_GetBuildingTypeCategory((unsigned char) *rec->entity) != 2
					    && rec->unk_08 != 0) {
						limit = rec->limit;
						w = *(unsigned short*) (g_item_def_table + a1[0] * 0x41 + off);
						if (limit >= w) {
							seg->supplier = rec->entity;
							if (*(short*) (rec->entity + 0x27) == *(short*) (*(int*) (actor + 0x16c) + 0x27)) {
								seg->requested = seg->capacity;
								continue;
							}
							scale = *(int*) ((char*) a1 + 0x40) >> 1;
							if (scale < 1) {
								scale = 1;
							}
							t = w * scale - seg->allocated - seg->stock;
							n = (seg->capacity >> 1) - seg->allocated;
							if (t < n) {
								t = n;
							}
							n = seg->capacity - seg->allocated - 1;
							if (t > n) {
								t = n;
							}
							ratio = (float) *(int*) (actor + 0x1b8) / seg->price;
							fl = (float) t;
							n = (int) (ratio < fl ? ratio : fl);
							if (n > limit) {
								n = limit;
							}
							if (n >= w) {
								seg->requested = n >= seg->requested ? n : seg->requested;
							}
						}
					}
				}
			}
		}
next:
		p++;
		off += 2;
	} while (off < 0x2e);
	return 1;
}
