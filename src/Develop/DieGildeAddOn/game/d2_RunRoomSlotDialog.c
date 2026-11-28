extern char* lpGebaeudePROT;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int io_RightButtonReleased;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005bdfc0 */
/* ADDRESS: GOLDDE 0x005a0420 */
int __cdecl d2_RunRoomSlotDialog(unsigned short* room, unsigned char* building, int slotCountA, int slotCountB)
{
	int btn;
	BUILDING_PROTOTYPE *info;
	int dlg;
	int x_dlg = -1;
	int y_dlg = -1;
	int handled = 0;
	int r;

	info = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*building];
	dlg = d2_LoadForm(0, 0, "Handel\\Handel_Lager_Neuer_Slot");
	d2_CenterDialogWindows(dlg);
	io_AppendText(0x10b);
	if (*room != 0x116) {
		if (slotCountA >= (int) (unsigned char) ((char) info->dimension_240)) {
			io_AppendText(0x110);
		} else {
			btn = io_AppendText(0x10c, 0x1f40);
			x_dlg = d2_GetWindowListItem(dlg, 0, btn);
		}
		if (slotCountB >= (int) (unsigned char) ((char) info->dimension_241)) {
			io_AppendText(0x111);
		} else {
			y_dlg = d2_GetWindowListItem(dlg, 0, io_AppendText(0x10d, 0x1f40));
		}
	} else if (slotCountA >= (int) (unsigned char) ((char) info->dimension_242)) {
		io_AppendText(0x111);
	} else {
		x_dlg = d2_GetWindowListItem(dlg, 0, io_AppendText(0x10e, 0x1f40));
	}
	io_AppendText(0x10f, 1);
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == x_dlg) {
				handled = 1;
				d2_DialogCloseRequested = 1;
			} else if (d2_CurrentElementId == y_dlg) {
				handled = 2;
				d2_DialogCloseRequested = 1;
			} else if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		r = main_RunFrameLoop(d2_RunRoomSlotDialog, 0x677c7);
	} while (r != 0);
	d2_DestroyForm(dlg);
	return handled;
}