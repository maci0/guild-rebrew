


extern char g_69059c[];
extern char g_690584[];
extern char g_690568[];
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int a, int b, char* s);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetForm(int h, int b);
void __cdecl io_AppendText(char* x);
int __cdecl main_RunFrameLoop(void* fn, int y);
void __cdecl d2_DestroyForm(int h);

void __cdecl d2_ShowPrivilegMessage(char* x, int mode, int y)
{
	int h;

	if (mode == 0) {
		h = d2_LoadForm(0, 0, g_69059c);
	} else if (mode == 1) {
		h = d2_LoadForm(0, 0, g_690584);
	} else {
		h = d2_LoadForm(0, 0, g_690568);
	}
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(x);
	d2_DialogButtonAction = -1;
	while (main_RunFrameLoop((void*) d2_ShowPrivilegMessage, y)) {
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_DestroyForm(h);
}
