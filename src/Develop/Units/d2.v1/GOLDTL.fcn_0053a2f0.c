#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
#include "client_dialog_state.h"




int __cdecl fcn_0046e940(int, int, int, int, int);
int __cdecl io_AppendText(char*);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_0046f280(int);

void __cdecl d2_ShowAmountDialog(void)
{
	int w;
	int t;

	g_1040488 = 0;
	g_1040480 = 1;
	g_1040484 = 1;
	g_104048c = 2;
	w = fcn_0046e940(0x20, 0x60, 0x26c, 0x190, 0x15);
	t = d2_GetWindowListItem(-1, w, io_AppendText("$3ABetrag:%m"));
	d2_SetElementValue(t, 0, 0x2710, 0);
	while (main_RunFrameLoop((void*) d2_ShowAmountDialog, 0x24087) != 0) {
		if (g_14cf950 == 1) {
			g_774654 = 1;
		}
	}
	fcn_0046f280(w);
}
