#include "Develop/Units/d2.v1/client_dialog_helpers.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLDTL 0x0050fe80 */
int __cdecl gm_FindLowestRelationSlot(char *base)
{
	float best;
	int best_index;
	int i;
	int value;

	best = 1.0e10f;
	best_index = -1;
	for (i = 0; i < 768; i++) {
		if (*(unsigned short *) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[i])) != 0xffff) {
			value = (signed char) base[0x869480 + i * 0x300];
			if (value < best) {
				best = value;
				best_index = i;
			}
		}
	}
	return best_index;
}
