#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern char* d2_Controls;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char s_6ac994[];
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_ShowCenteredText(int, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl amt_HasOccupiedOfficeType7(void);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_RunOfficeListDialog(int, char*, char*, int, void*);
int __cdecl d2_ShowTabbedSelectionDialog(char*, char*, int, void*);

/* ADDRESS: GOLDTL 0x005cd440 */
/* ADDRESS: GOLDDE 0x005aeed0 */
int __cdecl d2_OpenTargetPicker(char* query, int titleTextId, int unused, void* callback)
{
	int btn[9];
	int order[9];
	int dlg;
	int i;
	int id;
	int result;
	int scale;
	int e;
	int occupied;

	order[0] = 0;
	order[1] = 8;
	order[2] = 6;
	order[3] = 4;
	order[4] = 5;
	order[5] = 1;
	order[6] = 2;
	order[7] = 3;
	order[8] = 7;
	dlg = d2_LoadForm(0, 0, s_6ac994);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 2);
	if (titleTextId) {
		io_AppendText(titleTextId);
	} else {
		io_AppendText(0xa1);
	}
	d2_SetForm(dlg, 3);
	id = d2_GetWindowListItem(dlg, 3, io_AppendText(0x1687));
	d2_SetForm(dlg, 1);
	btn[0] = d2_AddElementToWindow(0x45, 0x3c, 0x589, d2_CurrentWindowId);
	btn[1] = d2_AddElementToWindow(0x10f, 0x25, 0x599, d2_CurrentWindowId);
	btn[2] = d2_AddElementToWindow(0x10f, 0x93, 0x58d, d2_CurrentWindowId);
	btn[3] = d2_AddElementToWindow(0x69, 0xab, 0x590, d2_CurrentWindowId);
	btn[4] = d2_AddElementToWindow(0x1b5, 0xab, 0x58c, d2_CurrentWindowId);
	btn[5] = d2_AddElementToWindow(0x45, 0x125, 0x58a, d2_CurrentWindowId);
	btn[6] = d2_AddElementToWindow(0x10f, 0x125, 0x58f, d2_CurrentWindowId);
	btn[7] = d2_AddElementToWindow(0x1d9, 0x125, 0x58b, d2_CurrentWindowId);
	btn[8] = d2_AddElementToWindow(0x1d9, 0x3c, 0x58e, d2_CurrentWindowId);
	for (i = 0; i < 9; i++) {
		if (i != 1 || *(int*) (query + 0x18) == 0) {
			e = btn[i];
			((D2_CONTROL_TL*)d2_Controls)[e].value_05c = 1;
			((D2_CONTROL_TL*)d2_Controls)[e].flags_1d0 = 3;
		}
		e = btn[i];
		((D2_CONTROL_TL*)d2_Controls)[e].font = 0x55;
		d2_ShowCenteredText(*(int*) (0x14a9de8 + order[i] * 4),
			     ((D2_CONTROL_TL*)d2_Controls)[e].x
				 - *(int*) (d2_CurrentWindow + 4) + 0x20,
			     ((D2_CONTROL_TL*)d2_Controls)[e].y
				 - *(int*) (d2_CurrentWindow + 8) - 0x19,
			     200, 0x55);
	}
	result = 0;
	d2_SetOverlayAnimation(0, 0);
	d2_DialogButtonAction = -1;
	scale = btn[8] * (int)sizeof(D2_CONTROL_TL);
	do {
		result = 0;
		occupied = amt_HasOccupiedOfficeType7() != 0;
		*(int*) (d2_Controls + scale + 0x5c) = occupied;
		*(int*) (d2_Controls + scale + 0x1d0) = occupied * 3;
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			for (i = 0; i < 9; i++) {
				if (btn[i] == d2_CurrentElementId) {
					break;
				}
			}
			if (i < 9 && i > -1) {
				d2_SetFormVisibility(dlg, 0);
				result = d2_RunOfficeListDialog(order[i], query, (char*) titleTextId, 0, callback);
				d2_SetFormVisibility(dlg, 1);
			} else if (d2_CurrentElementId == id) {
				d2_SetFormVisibility(dlg, 0);
				result = d2_ShowTabbedSelectionDialog(query, (char*) titleTextId, -1, callback);
				d2_SetFormVisibility(dlg, 1);
			}
			if (result && callback == 0 && (*(unsigned char*) (query + 0x14) & 4) == 0) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_OpenTargetPicker, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
