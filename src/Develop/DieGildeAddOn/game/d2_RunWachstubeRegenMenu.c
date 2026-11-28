


extern int d2_SelectedEntityUiFlags;
extern int sv_ClickedObjekt;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_6aa3b0[];
extern char s_6ab2a0[];

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_RunWorkerTrainingDialog(int);

void __cdecl d2_RunWachstubeRegenMenu(int building)
{
	int a;
	int b;

	a = 0;
	b = 0;
	d2_ClearStatusTextSlots();
	if (main_RunFrameLoop((void*) d2_RunWachstubeRegenMenu, 0x67fff) != 0) {
		do {
			if (d2_SelectedEntityUiFlags & 0x200) {
				a = RegisterStatusText(s_6aa3b0, g_14abc2c, 0xc);
				b = RegisterStatusText(s_6ab2a0, g_14abc30, 0xc);
			}
			if ((d2_SelectedEntityUiFlags & 0x200) && sv_ClickedObjekt != 0) {
				if (sv_ClickedObjekt == a || sv_ClickedObjekt == b) {
					d2_RunWorkerTrainingDialog(building);
				}
			}
		} while (main_RunFrameLoop((void*) d2_RunWachstubeRegenMenu, 0x67fff) != 0);
	}
}
