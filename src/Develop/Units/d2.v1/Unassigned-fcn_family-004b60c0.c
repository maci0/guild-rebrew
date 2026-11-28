extern signed char gm_SelectedMissionIndex;

int __cdecl d2_RunActiveHistoryMissionDialog(void);
int __cdecl d2_RunMissionDialog(void);

int __cdecl d2_WaitHistoryMissionDialog(void);
int __cdecl d2_ShowMissionDialog(void);
extern int nt_ClientSocket;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_6a3760;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl d2_DispatchMissionDialog(void);
int __cdecl d2_DispatchMissionBriefing(void);
int __cdecl d2_FinishHistoryMissionDialog(void);

/* ADDRESS: GOLDTL 0x004b60c0 */
/* ADDRESS: GOLDDE 0x004a4350 */
int __cdecl d2_DispatchMissionDialog(void)
{
	if (gm_SelectedMissionIndex == 5)
		return d2_RunActiveHistoryMissionDialog();
	return d2_RunMissionDialog();
}

/* ADDRESS: GOLDTL 0x004b62c0 */
/* ADDRESS: GOLDDE 0x004a4550 */
int __cdecl d2_DispatchMissionBriefing(void)
{
	if (gm_SelectedMissionIndex == 5)
		return d2_WaitHistoryMissionDialog();
	return d2_ShowMissionDialog();
}

/* ADDRESS: GOLDTL 0x004b6470 */
/* ADDRESS: GOLDDE 0x004a4700 */
int __cdecl d2_HandleMissionTurnEnd(void)
{
	if (nt_ClientSocket != -1) {
		if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id == g_6a3760)
			return d2_DispatchMissionDialog();
		return d2_DispatchMissionBriefing();
	}
	return d2_FinishHistoryMissionDialog();
}
