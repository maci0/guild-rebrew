extern char gm_EntitySlotTable[];
extern char gm_EntitySlotTable[];
extern int gm_AllEntitiesControllable;
extern int gm_AllEntitiesControllable;
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLD 0x004ce170 */
/* ADDRESS: GOLDTL 0x004cef70 */
/* ADDRESS: GOLDDE 0x004bc4d0 */
int __cdecl gm_GetEntityControlMask(int entityIndex, char* entityRecord)
{
	int r;

	r = 0;
	if (*(int*) (entityRecord + 0x16c) == (int) (((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[entityIndex]))) {
		r = 0x800;
	}
	if (*(int*) ((char*)&gm_AllEntitiesControllable) != 0) {
		r = 0x800;
	}
	return r;
}
