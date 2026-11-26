


extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl fcn_00470820(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_004f2a10(int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058c670(int a1, int a2, unsigned char a3)
{
	int dlg;
	int id;
	int ok;
	int cancel;
	int r;

	r = 0;
	dlg = fcn_00470820(0, 0, (int) "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x410f, 0x410e);
	d2_SetForm(dlg, 2);
	id = io_AppendText(0x4111);
	ok = d2_GetWindowListItem(dlg, 2, id);
	cancel = d2_GetWindowListItem(dlg, 2, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				fcn_004f2a10(0, a1, a2, a3);
				r = 1;
				g_774654 = 1;
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) fcn_0058c670, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
