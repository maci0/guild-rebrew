


#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6aca14[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(char*, ...);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005b01a0 */
void __cdecl d2_RunGesetzbuchInfoDialog(int textId, int value)
{
	int h;

	h = d2_LoadForm(0, 0, g_6aca14);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText((char*) (textId + 1), textId, value);
	d2_SetForm(h, 2);
	io_AppendText((char*) (textId + 2));
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_RunGesetzbuchInfoDialog, 0x677c7) != 0);
	d2_DestroyForm(h);
}
