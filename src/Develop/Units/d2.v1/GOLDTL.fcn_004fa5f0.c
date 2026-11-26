


extern char g_69059c[];
extern char g_690584[];
extern char g_690568[];
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl d2_CenterDialogWindows(int h);
void __cdecl d2_SetForm(int h, int b);
void __cdecl io_AppendText(char* x);
int __cdecl main_RunFrameLoop(void* fn, int y);
void __cdecl fcn_00471e30(int h);

void __cdecl d2_ShowPrivilegMessage(char* x, int mode, int y)
{
	int h;

	if (mode == 0) {
		h = fcn_00470820(0, 0, g_69059c);
	} else if (mode == 1) {
		h = fcn_00470820(0, 0, g_690584);
	} else {
		h = fcn_00470820(0, 0, g_690568);
	}
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(x);
	g_100f1dc = -1;
	while (main_RunFrameLoop((void*) d2_ShowPrivilegMessage, y)) {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}
