


extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6aa8d0[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005857e0 */
void __cdecl d2_ShowWirtshausRules(void)
{
	int h;
	int a;

	h = d2_LoadForm(0, 0, g_6aa8d0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 2);
	a = d2_CurrentWindowId;
	d2_SetForm(h, 3);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, a, 0x767);
	d2_SetForm(h, 1);
	io_AppendText(0x1889);
	d2_SetForm(h, 2);
	io_AppendText(0x188a);
	while (main_RunFrameLoop(d2_ShowWirtshausRules, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_DestroyForm(h);
}
