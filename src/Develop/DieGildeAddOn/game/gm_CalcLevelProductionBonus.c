extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLDTL 0x0050bbb0 */
/* ADDRESS: GOLDDE 0x004f6bf0 */
float __cdecl gm_CalcLevelProductionBonus(int idx)
{
	char* p;
	float v;

	p = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[idx]);
	if (p == 0) {
		return 1.0f;
	}
	v = *(unsigned char*)&((ENTITY_RECORD_VIEW*)p)->levels[0];
	if (v <= 42.0f) {
		return 1.0f;
	}
	return (float) (v * (1.0 / 1008.0) + 1.0);
}
