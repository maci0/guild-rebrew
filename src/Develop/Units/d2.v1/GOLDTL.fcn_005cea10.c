

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6aca6c[];
extern int d2_CurrentWindowId;
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
/* ADDRESS: GOLD 0x5c27f0 */

void __cdecl fcn_005cea10(void)
{
	int h;

	h = fcn_00470820(0, 0, g_6aca6c);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_CenterDialogWindows(h);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(h, 1);
	io_AppendText((char*) 0x1949);
	io_AppendText((char*) 0x194e);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(fcn_005cea10, 0x677c7) != 0);
	fcn_00471e30(h);
}
