


typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3;
	int x4;
	char pad8[0x1a4];
	int x1ac;
	char pad1b0[0x6c];
} Ent21c;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/entity_record.h"

/* ADDRESS: GOLDDE 0x004f93b0 */
void __cdecl gm_GetKircheTop5(int* ids, int* vals)
{
	int i;
	int j;

	for (i = 0; i < 5; i++) {
		ids[i] = 0xffff;
		vals[i] = 0;
	}
	for (i = 0; i < 768; i++) {
		if ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id) != -1 && (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type) < 10 &&
			(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].value_1ac) > vals[4]) {
			vals[4] = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].value_1ac);
			ids[4] = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index);
			for (j = 3; j > -1; j--) {
				if ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].value_1ac) <= vals[j] || (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type) >= 10) {
					break;
				}
				vals[j + 1] = vals[j];
				ids[j + 1] = ids[j];
				vals[j] = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].value_1ac);
				ids[j] = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index);
			}
		}
	}
}
