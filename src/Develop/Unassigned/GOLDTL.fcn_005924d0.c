


extern int g_7766a8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
extern int g_7e2700;
extern int tp_d2_SelectedControl;
extern int main_LoopFlags;
extern unsigned char g_7747b0;
extern int g_14a5538;

void __cdecl fcn_00592400(void);
void __cdecl fcn_005e40b0(void);
void __cdecl fcn_004c4890(void);
void __cdecl fcn_004c48c0(void);
void __cdecl fcn_005e2510(void);
void __cdecl fcn_00533a40(int);

void __cdecl fcn_005924d0(void)
{
	int lvl;

	lvl = (int) (g_7766a8 / 40 + g_6628cc);
	if (g_14cf950 == 0 || g_7e2700 == 1) {
		return;
	}
	if (g_14cf950 == 0x1f) {
		fcn_00592400();
	}
	if (g_14cf950 == 0x10 && tp_d2_SelectedControl == 0 && (main_LoopFlags & 0x10000) == 0) {
		fcn_005e40b0();
	}
	if ((g_7747b0 & 4) == 0) {
		if (g_14cf950 == 0x4e) {
			fcn_004c4890();
			if (lvl < 4) {
				lvl++;
				g_7766a8 = lvl * 40;
				fcn_005e2510();
			}
		}
		if (g_14cf950 == 0x4a) {
			fcn_004c48c0();
			if (lvl > 0) {
				g_7766a8 = (lvl - 1) * 40;
				fcn_005e2510();
			}
		}
	} else if (g_7747b0 & 0x10) {
		if (g_14cf950 == 0x4e) {
			fcn_004c4890();
		} else if (g_14cf950 == 0x4a) {
			fcn_004c48c0();
		}
	} else if (g_14cf950 == 0x4e || g_14cf950 == 0x4a) {
		fcn_00533a40(g_14a5538);
	}
}
unsigned char _dpad_14cf902[78];
unsigned char _dpad_14cf950[1744];
