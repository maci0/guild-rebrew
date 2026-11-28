


extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl gs_ClearTargetStraftaten(int, int);
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_GetControlValue(int);
int __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl gm_HandleAbbitte(char* e, char* o)
{
	int ok;
	int cancel;
	int sl;
	char buf[0x100];
	int n;
	int r;
	int dlg;
	int id;
	int v;

	if (e[2] != 6) {
		n = *(int*) (o + 4);
		if (n < 1 || n > 9 || n > *(int*) (e + 0x194)) {
			return 0x60;
		}
		gs_ClearTargetStraftaten(*(int*) (e + 4), n);
		cm_RequestModifyHealth(*(int*) (e + 4), -*(int*) (o + 4));
	}
	if (e[2] == 6) {
		r = 0;
		dlg = d2_LoadForm(0, 0, "privillegien\\abbitte");
		d2_SetOverlayAnimation(0, 0);
		d2_CenterDialogWindows(dlg);
		d2_SetForm(dlg, 1);
		id = io_AppendText(0x1dea);
		ok = d2_GetWindowListItem(dlg, 1, id + 1);
		cancel = d2_GetWindowListItem(dlg, 1, id + 2);
		sl = d2_GetWindowListItem(dlg, 1, id);
		d2_SetElementValue(sl, 1, 9, 1);
		d2_DialogButtonAction = -1;
		do {
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == ok) {
					v = d2_GetControlValue(sl);
					if (d2_CheckActionBlocker(e, v) != 0) {
						cm_RequestModifyHealth(*(int*) (e + 4), -v);
						io_FormatTextBuffer(buf, 0x1deb, gs_ClearTargetStraftaten(*(int*) (e + 4), v));
						d2_ShowModalMessageBox(buf, 0);
						r = 1;
						d2_DialogCloseRequested = 1;
					}
				} else if (d2_CurrentElementId == cancel) {
					d2_DialogCloseRequested = 1;
				}
			}
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) gm_HandleAbbitte, 0x657c7) != 0);
		d2_DestroyForm(dlg);
		return r;
	}
	return 0;
}
