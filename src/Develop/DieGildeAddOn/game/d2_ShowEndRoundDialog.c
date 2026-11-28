#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_774960;



int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl main_ExitToFrameHandler(void*);
void __cdecl main_RunGameLoop(void);

void __cdecl d2_ShowEndRoundDialog(void)
{
	int h;
	int q;

	h = d2_LoadForm(0, 0, "Runde beenden");
	q = 0;
	d2_CenterDialogWindows(h);
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_DialogButtonAction == 2) {
				q = 1;
			}
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowEndRoundDialog, 0x67fff) != 0);
	d2_DestroyForm(h);
	if (q != 0) {
		g_774960 = 1;
		main_ExitToFrameHandler((void*) main_RunGameLoop);
	}
}
