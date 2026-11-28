#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char gm_EntitySlotTable[];

void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);

/* ADDRESS: GOLDDE 0x004fab80 */
void __cdecl gm_AdjustOfficeHoldersFavor(unsigned short entityId, int delta)
{
	int i;

	for (i = 0; i < 768; i++) {
		if (((unsigned char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[i])[0x166] != 0) {
			cm_RequestCopyEntityData(entityId, i, delta, 1);
		}
	}
}
