

extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6ac76c[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
/* ADDRESS: GOLD 0x5cf970 */

void __cdecl d2_ShowUseObjDialog(char* text)
{
	int h;

	h = d2_LoadForm(0, 0, g_6ac76c);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText("%s", text);
	d2_SetOverlayAnimation(0, 0);
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_ShowUseObjDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
}
