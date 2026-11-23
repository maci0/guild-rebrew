#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/ai_supply_candidate.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))
extern int g_100e720[];
extern int g_100e760[];
extern int g_86805c;

char* __cdecl fcn_00502cd0(void* id, int a, int b, int c);
int __cdecl fcn_00503a70(int id);

/* ADDRESS: GOLDTL 0x00486c40 */
void __cdecl fcn_00486c40(ENTITY_RECORD* a0, unsigned int a1, int budget)
{
	char* q;
	int i;
	int j;
	int k;
	int found;
	int sum;

	(void) a1;
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*) g_7f4ca0)[i].entity_index != 0xffff &&
		    ((ENTITY_RECORD*) g_7f4ca0)[i].unk_16c == a0->unk_16c &&
		    ((ENTITY_RECORD*) g_7f4ca0)[i].unk_165[0] != 0) {
			q = fcn_00502cd0(((ENTITY_RECORD*) g_7f4ca0)[i].object_list, 1, 4, 0xc);
			if (q == 0) {
				for (k = 0; k < ai_ResourceCount; k++) {
					if (g_100b0c0[k].goods_id == g_100e760[0]) {
						g_100b0c0[k].requested++;
						g_100b0c0[k].flags |= 2;
						break;
					}
				}
			} else {
				found = 0;
				j = 0;
				while (!found) {
					if (g_100e760[j] == 0 || g_100e760[j + 1] == 0) {
						break;
					}
					g_100e760[j] = *(unsigned short*) q;
					if (g_100e760[j] != 0) {
						for (k = 0; !found && k < ai_ResourceCount; k++) {
							if (g_100b0c0[k].goods_id == g_100e760[j + 1]) {
								g_100b0c0[k].requested++;
								g_100b0c0[k].flags |= 2;
								found = 1;
							}
						}
					}
					j++;
				}
				if (!found) {
					j = 0;
					while (!found) {
						if (g_100e720[j] == 0 || g_100e720[j + 1] == 0) {
							break;
						}
						g_100e720[j] = *(unsigned short*) q;
						if (g_100e720[j] != 0) {
							for (k = 0; !found && k < ai_ResourceCount; k++) {
								if (g_100b0c0[k].goods_id == g_100e720[j + 1]) {
									g_100b0c0[k].requested++;
									g_100b0c0[k].flags |= 2;
									found = 1;
								}
							}
						}
						j++;
					}
				}
			}
		}
	}
	for (i = 0; i < ai_ResourceCount; i++) {
		if (g_100b0c0[i].requested != 0) {
			found = 0;
			k = 0;
			while (!found) {
				if (g_100e760[k] == 0) {
					break;
				}
				if (g_100b0c0[i].goods_id == g_100e760[k]) {
					g_100b0c0[i].requested -= g_100b0c0[i].stock + g_100b0c0[i].allocated;
					g_100b0c0[i].requested = MAX(g_100b0c0[i].requested, 0);
					found = 1;
				}
				k++;
			}
			if (!found) {
				k = 0;
				while (!found) {
					if (g_100e720[k] == 0) {
						break;
					}
					if (g_100b0c0[i].goods_id == g_100e720[k]) {
						g_100b0c0[i].requested -= g_100b0c0[i].stock + g_100b0c0[i].allocated;
						g_100b0c0[i].requested = MAX(g_100b0c0[i].requested, 0);
						found = 1;
					}
					k++;
				}
			}
			if (g_100b0c0[i].requested != 0) {
				fcn_00503a70(g_100b0c0[i].goods_id);
				found = 0;
				for (k = 0; !found && k < g_86805c; k++) {
					if (g_868c40[k].unk_08 != 0 && g_868c40[k].limit >= 1) {
						g_100b0c0[i].supplier = g_868c40[k].entity;
					}
				}
			}
			if (g_100b0c0[i].supplier == 0) {
				g_100b0c0[i].requested = 0;
			}
		}
	}
	sum = 0;
	for (k = 0; g_100e760[k] != 0; k++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (g_100e760[k] == g_100b0c0[i].goods_id && g_100b0c0[i].requested != 0) {
				while (g_100b0c0[i].requested > 0 &&
				       g_100b0c0[i].requested * g_100b0c0[i].price + (float) sum > (float) budget) {
					g_100b0c0[i].requested--;
				}
				sum = (int) (g_100b0c0[i].requested * g_100b0c0[i].price + sum);
			}
		}
	}
	for (k = 0; g_100e720[k] != 0; k++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (g_100e720[k] == g_100b0c0[i].goods_id && g_100b0c0[i].requested != 0) {
				while (g_100b0c0[i].requested > 0 &&
				       g_100b0c0[i].requested * g_100b0c0[i].price + (float) sum > (float) budget) {
					g_100b0c0[i].requested--;
				}
				sum = (int) (g_100b0c0[i].requested * g_100b0c0[i].price + sum);
			}
		}
	}
}
unsigned char _dpad_100df20[2048];
