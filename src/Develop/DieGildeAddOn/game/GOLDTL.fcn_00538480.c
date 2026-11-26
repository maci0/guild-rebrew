#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_774960;



int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl main_ExitToFrameHandler(void*);
void __cdecl fcn_005438c0(void);

void __cdecl d2_ShowEndRoundDialog(void)
{
	int h;
	int q;

	h = fcn_00470820(0, 0, "Runde beenden");
	q = 0;
	d2_CenterDialogWindows(h);
	do {
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				q = 1;
			}
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowEndRoundDialog, 0x67fff) != 0);
	d2_DestroyForm(h);
	if (q != 0) {
		g_774960 = 1;
		main_ExitToFrameHandler((void*) fcn_005438c0);
	}
}
