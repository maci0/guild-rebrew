#include "Develop/DieGildeAddOn/game/goods_plan.h"

#include "Develop/DieGildeAddOn/game/ai_supply_candidate.h"








#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100e720[];
extern int g_100e760[];
extern int g_86805c;


/* 768 building records of 540 bytes; g_7f4ca4 points four bytes into the first. */
extern char g_7f4ca4[];
#define PROP_COUNT 768
#define PROP(n) (g_7f4ca4 + (n) * 540)

char* __cdecl fcn_00502cd0(int id, int a, int b, int c);
int __cdecl fcn_00503a70(int id);

/* ADDRESS: GOLDTL 0x00486c40 */
void __cdecl fcn_00486c40(char* a0, unsigned int a1, int a2)
{
	GOODS_PLAN_ENTRY* seg;
	AI_SUPPLY_CANDIDATE* rec;
	int* lp;
	char* p;
	char* q;
	int n;
	int i;
	int k;
	int found;
	int sum;
	int v;

	(void) a1;
	for (i = 0; i < PROP_COUNT; i++) {
		p = PROP(i);
		if (*(unsigned short*) (p - 4) == 0xffff) {
			continue;
		}
		if (*(int*) (p + 0x168) != *(int*) (a0 + 0x16c)) {
			continue;
		}
		if (*(char*) (p + 0x161) == 0) {
			continue;
		}
		q = fcn_00502cd0(*(int*) (p + 0x174), 1, 4, 0xc);
		n = ai_ResourceCount;
		if (q != 0) {
			found = 0;
			for (lp = &g_100e760[1]; lp[-1] != 0 && lp[0] != 0 && found == 0; lp++) {
				lp[-1] = *(unsigned short*) q;
				if (lp[-1] != 0) {
					for (k = 0; k < n; k++) {
						if (g_100b0c0[k].goods_id == lp[0]) {
							g_100b0c0[k].requested++;
							g_100b0c0[k].flags |= 2;
							found = 1;
							break;
						}
					}
				}
			}
			if (found == 0) {
				for (lp = &g_100e720[1]; lp[-1] != 0 && lp[0] != 0 && found == 0; lp++) {
					lp[-1] = *(unsigned short*) q;
					if (lp[-1] != 0) {
						for (k = 0; k < n; k++) {
							if (g_100b0c0[k].goods_id == lp[0]) {
								g_100b0c0[k].requested++;
								g_100b0c0[k].flags |= 2;
								found = 1;
								break;
							}
						}
					}
				}
			}
		} else if (n >= 1) {
			for (k = 0; k < n; k++) {
				if (g_100b0c0[k].goods_id == g_100e760[0]) {
					g_100b0c0[k].requested++;
					g_100b0c0[k].flags |= 2;
					break;
				}
			}
		}
	}
	n = ai_ResourceCount;
	for (i = 0; i < n; i++) {
		seg = &g_100b0c0[i];
		if (seg->requested != 0) {
			found = 0;
			for (k = 0; g_100e760[k] != 0; k++) {
				if (seg->goods_id == g_100e760[k]) {
					v = seg->requested - (seg->allocated + seg->stock);
					seg->requested = v;
					if (seg->requested < 0) {
						seg->requested = 0;
					}
					found = 1;
					break;
				}
			}
			if (found == 0) {
				for (k = 0; g_100e720[k] != 0; k++) {
					if (seg->goods_id == g_100e720[k]) {
						v = seg->requested - (seg->allocated + seg->stock);
						seg->requested = v;
						if (seg->requested < 0) {
							seg->requested = 0;
						}
						found = 1;
						break;
					}
				}
			}
			if (seg->requested != 0) {
				fcn_00503a70(seg->goods_id);
				for (k = 0; k < g_86805c; k++) {
					rec = &g_868c40[k];
					if (rec->unk_08 != 0 && rec->limit >= 1) {
						seg->supplier = rec->entity;
					}
				}
				n = ai_ResourceCount;
			}
		}
		if (seg->supplier == 0) {
			seg->requested = 0;
		}
	}
	sum = 0;
	if (g_100e760[0] != 0) {
		for (k = 0; g_100e760[k] != 0; k++) {
			for (i = 0; i < ai_ResourceCount; i++) {
				seg = &g_100b0c0[i];
				if (g_100e760[k] == seg->goods_id && seg->requested != 0) {
					while (seg->requested > 0) {
						if (!((double) seg->requested * seg->price + (float) sum > (float) a2)) {
							break;
						}
						seg->requested--;
					}
					sum = (int) ((double) seg->requested * seg->price + sum);
				}
			}
		}
	}
	if (g_100e720[0] == 0) {
		return;
	}
	for (k = 0; g_100e720[k] != 0; k++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			seg = &g_100b0c0[i];
			if (g_100e720[k] == seg->goods_id && seg->requested != 0) {
				while (seg->requested > 0) {
					if (!((double) seg->requested * seg->price + (float) sum > (float) a2)) {
						break;
					}
					seg->requested--;
				}
				sum = (int) ((double) seg->requested * seg->price + sum);
			}
		}
	}
}
unsigned char _dpad_100df20[2048];
