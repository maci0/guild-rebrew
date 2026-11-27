extern signed char g_6a3440;

int __cdecl d2_RunActiveHistoryMissionDialog(void);
int __cdecl d2_RunMissionDialog(void);

int __cdecl d2_WaitHistoryMissionDialog(void);
int __cdecl d2_ShowMissionDialog(void);
extern int g_14cbca0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_6a3760;
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl fcn_004b60c0(void);
int __cdecl fcn_004b62c0(void);
int __cdecl d2_FinishHistoryMissionDialog(void);

/* ADDRESS: GOLDTL 0x004b60c0 */
int __cdecl fcn_004b60c0(void)
{
	if (g_6a3440 == 5)
		return d2_RunActiveHistoryMissionDialog();
	return d2_RunMissionDialog();
}

/* ADDRESS: GOLDTL 0x004b62c0 */
int __cdecl fcn_004b62c0(void)
{
	if (g_6a3440 == 5)
		return d2_WaitHistoryMissionDialog();
	return d2_ShowMissionDialog();
}

/* ADDRESS: GOLDTL 0x004b6470 */
int __cdecl fcn_004b6470(void)
{
	if (g_14cbca0 != -1) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id == g_6a3760)
			return fcn_004b60c0();
		return fcn_004b62c0();
	}
	return d2_FinishHistoryMissionDialog();
}
