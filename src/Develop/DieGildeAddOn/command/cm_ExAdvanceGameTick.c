


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_timestamp.h"






// SIZE 0xe


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_6a3438;
extern int g_6a3434;
extern int g_6a3430;
extern int ai_DispatchedTradeCount;
extern LightState ai_MeisterDebugState;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl gm_CompareGameTime(GAME_TIMESTAMP*, GAME_TIMESTAMP*);
void __cdecl he_RunDueActions(void);
void __cdecl gm_StepCityPopulation(void);
void __cdecl gm_CollectPopulationStats(void);
void __cdecl ai_UpdateAllEntityDrives(void);
void __cdecl ai_EvaluateMeister(char*);
void __cdecl ai_StepEntityTurns(void);
void __cdecl gm_TickStampedItems(void);
void __cdecl gm_UpdateGraveyardFlags(void);

/* ADDRESS: GOLDDE 0x004b6c20 */
int __cdecl cm_ExAdvanceGameTick(char* x, char* out)
{
	int i;

	if (gm_CompareGameTime(&(*(GAME_TIMESTAMP*)&gm_GameTime), (GAME_TIMESTAMP*) (x + 0x10)) < 0) {
		(*(GAME_TIMESTAMP*)&gm_GameTime) = *(GAME_TIMESTAMP*) (x + 0x10);
		if (g_6a3438 != 0)
			he_RunDueActions();
		if (g_6a3434 != 0) {
			gm_StepCityPopulation();
			if ((*(GAME_TIMESTAMP*)&gm_GameTime).minute % 6 == 0)
				gm_CollectPopulationStats();
		}
		if (g_6a3430 != 0)
			ai_UpdateAllEntityDrives();
		memset(&ai_MeisterDebugState, 0, 0xb00);
		if (g_6a3430 != 0) {
			ai_DispatchedTradeCount = 0;
			for (i = 0; i < 0x300; i++) {
				if (*(unsigned short*) (((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i])) != 0xffff)
					ai_EvaluateMeister(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]));
			}
			ai_StepEntityTurns();
		}
		gm_TickStampedItems();
		gm_UpdateGraveyardFlags();
	}
	if (out != 0)
		*out = 1;
	return 0;
}
