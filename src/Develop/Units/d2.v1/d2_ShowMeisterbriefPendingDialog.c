

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6aca6c[];
extern int d2_CurrentWindowId;
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
/* ADDRESS: GOLD 0x5c27f0 */

/* ADDRESS: GOLDDE 0x005b0430 */
void __cdecl d2_ShowMeisterbriefPendingDialog(void)
{
	int h;

	h = d2_LoadForm(0, 0, g_6aca6c);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	io_AppendText((char*) 0x1949);
	io_AppendText((char*) 0x194e);
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_ShowMeisterbriefPendingDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
}
