extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity.h"

void __cdecl amt_TriggerOfficeActionByType(int);
int __cdecl amt_SelectOfficeCandidates(EntityStruct* slot, int mode, int* out);
void __cdecl amt_ApplyForOffice(EntityStruct* slot, int value);

/* ADDRESS: GOLDTL 0x0057fea0 */
/* ADDRESS: GOLDDE 0x00565c40 */
void __cdecl d2_RunTutorialOfficeStep(int action)
{
	unsigned char* p;
	EntityStruct* slot;
	int index;
	int value[3];

	if (action == 0) {
		amt_TriggerOfficeActionByType(1);
		return;
	}
	if (action != 1) {
		return;
	}
	for (index = 0, p = (unsigned char*) ((int) &gm_EntitySlotTable + 0x2); (int) p < ((int) &gm_EntitySlotTable + 0x65402); p += 0x21c, index++) {
		if (*p == 5) {
			slot = (EntityStruct*) ((int) &gm_EntitySlotTable + index * 0x21c);
			if (amt_SelectOfficeCandidates(slot, 1, value) > 0) {
				amt_ApplyForOffice(slot, value[0]);
			}
			break;
		}
	}
}
