


extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl gv_SendSetGraveOwner(int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ShowGraveyardConfirm(int building, int itemId, unsigned char slotIndex)
{
	int dlg;
	int id;
	int ok;
	int cancel;
	int r;

	r = 0;
	dlg = d2_LoadForm(0, 0, (int) "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
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
				gv_SendSetGraveOwner(0, building, itemId, slotIndex);
				r = 1;
				g_774654 = 1;
			} else if (d2_CurrentElementId == cancel) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowGraveyardConfirm, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
