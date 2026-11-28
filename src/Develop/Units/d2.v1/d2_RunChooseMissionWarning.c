extern unsigned int g_7e1f60;
extern signed char gm_SelectedMissionIndex;
extern unsigned char gm_PlayerCount;
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7e242c;



__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
int __cdecl gm_PickRandomMissionEntry(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_ShowMissionSpecDialog(int, int);

int __cdecl d2_RunChooseMissionWarning(void)
{
	int r;
	int h;

	g_7e1f60 = timeGetTime();
	r = gm_PickRandomMissionEntry(gm_SelectedMissionIndex);
	if (gm_PlayerCount > 1) {
		h = d2_LoadForm(0, 0, "Menu\\GET_MISSION_WARNING");
		d2_CenterDialogWindows(h);
		d2_SetForm(h, 0);
		io_AppendText(0x1adc);
		io_AppendText(0x1add);
		while (main_RunFrameLoop((void*) d2_RunChooseMissionWarning, 0xc6) != 0) {
			if (d2_DialogButtonAction == 2) {
				d2_DialogCloseRequested = 1;
			} else if (d2_DialogButtonAction == 1) {
				r = 0;
				d2_DialogCloseRequested = 1;
			}
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
				r = 0;
			}
		}
		if (h != -1) {
			d2_DestroyForm(h);
		}
	}
	if (r != 0) {
		d2_ShowMissionSpecDialog(r, 0xc6);
	}
	g_7e242c = r;
	return r;
}
