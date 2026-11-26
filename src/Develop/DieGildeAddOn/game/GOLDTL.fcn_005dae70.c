


typedef struct
{
	int x0;
	char pad4[0x14];
} Law;
// SIZE 0x18

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern unsigned short g_7f4c04;

int __cdecl amt_FindOfficeSlotByType(int, Law*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl d2_ShowExpelWorkersDialog(char* e)
{
	Law x;
	int r;
	int dlg;
	int id;
	int ok;
	int cancel;

	r = 0x22;
	if (e[2] != 6 && e[2] != 7) {
		return 0x20;
	}
	if (amt_FindOfficeSlotByType(*(unsigned char*) (e + 0x166), &x) == 0) {
		return 0x40;
	}
	dlg = fcn_00470820(0, 0, "privillegien\\arbeiter_ausweisen");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1e24, (e[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (e + 0x166));
	id = io_AppendText(0x1e25);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == ok) {
				fcn_004e8240(x.x0, 0, 0, g_7f4c04 > 13 ? 0xff : 3, 0xff);
				r = 0x90;
				g_774654 = 1;
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowExpelWorkersDialog, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
