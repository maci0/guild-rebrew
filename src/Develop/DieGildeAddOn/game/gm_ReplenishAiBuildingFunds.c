


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int gm_DifficultyLevel;
extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_AccumulateTyped2(ENTITY_RECORD*);
int __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDDE 0x0052dbd0 */
void __cdecl gm_ReplenishPersonFunds(void)
{
	int cmd_handle;
	int batch_count;
	int i;
	int limit;
	int funds;

	cmd_handle = -1;
	if ((*(int*)&gm_GameTime) % ((*(int*)&gm_GameTime) / 10 + 1) == 0) {
		limit = (gm_DifficultyLevel * 5 + 20) * 1600;
		batch_count = 0;
		for (i = 0; i < 768; i++) {
			if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type == 5) {
				funds = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]));
				if (funds < limit) {
					cmd_handle = cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id, -1, (*(char*)&gm_ActiveTownIndex), limit - funds);
					batch_count++;
				}
			} else if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type == 4
				|| (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_type == 2 && (*(int*)&gm_GameTime) % 4 == (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id & 3))) {
				funds = gm_AccumulateTyped2(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]));
				if (funds < limit) {
					cmd_handle = cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id, -1, (*(char*)&gm_ActiveTownIndex), limit - funds);
					batch_count++;
				}
			}
			if (batch_count >= 32 && cmd_handle != -1) {
				do {
					if (cm_GetCommandStatus(cmd_handle) != 0) {
						break;
					}
					cm_StepCommandQueue();
				} while (1);
				cmd_handle = -1;
				batch_count = 0;
			}
		}
	}
}
