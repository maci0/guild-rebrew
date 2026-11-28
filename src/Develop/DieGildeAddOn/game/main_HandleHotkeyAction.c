


extern int g_7766a8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
extern int d2_InsideBuildingActive;
extern int tp_d2_SelectedControl;
extern int main_LoopFlags;
extern unsigned char gm_ClientModeFlags;
extern int g_14a5538;

void __cdecl d2_SaveScreenshot(void);
void __cdecl ls_QuickSave(void);
void __cdecl cm_RequestIncreaseGameSpeed(void);
void __cdecl cm_SendDecreaseGameSpeed(void);
void __cdecl gm_ApplyGameSettings(void);
void __cdecl d2_ShowStatusBanner(int);

/* ADDRESS: GOLDDE 0x00578180 */
void __cdecl main_HandleHotkeyAction(void)
{
	int lvl;

	lvl = (int) (g_7766a8 / 40 + g_6628cc);
	if (io_LastKeyScancode == 0 || d2_InsideBuildingActive == 1) {
		return;
	}
	if (io_LastKeyScancode == 0x1f) {
		d2_SaveScreenshot();
	}
	if (io_LastKeyScancode == 0x10 && tp_d2_SelectedControl == 0 && (main_LoopFlags & 0x10000) == 0) {
		ls_QuickSave();
	}
	if ((gm_ClientModeFlags & 4) == 0) {
		if (io_LastKeyScancode == 0x4e) {
			cm_RequestIncreaseGameSpeed();
			if (lvl < 4) {
				lvl++;
				g_7766a8 = lvl * 40;
				gm_ApplyGameSettings();
			}
		}
		if (io_LastKeyScancode == 0x4a) {
			cm_SendDecreaseGameSpeed();
			if (lvl > 0) {
				g_7766a8 = (lvl - 1) * 40;
				gm_ApplyGameSettings();
			}
		}
	} else if (gm_ClientModeFlags & 0x10) {
		if (io_LastKeyScancode == 0x4e) {
			cm_RequestIncreaseGameSpeed();
		} else if (io_LastKeyScancode == 0x4a) {
			cm_SendDecreaseGameSpeed();
		}
	} else if (io_LastKeyScancode == 0x4e || io_LastKeyScancode == 0x4a) {
		d2_ShowStatusBanner(g_14a5538);
	}
}
unsigned char _dpad_14cf902[78];
unsigned char _dpad_14cf950[1744];
