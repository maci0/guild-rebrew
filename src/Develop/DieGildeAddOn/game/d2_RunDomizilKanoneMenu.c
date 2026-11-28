extern int d2_SelectedEntityUiFlags;
extern char* g_14b5494;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char* sv_ClickedObjekt;

void __cdecl d2_ClearStatusTextSlots(void);
char* __cdecl RegisterStatusText(char* name, char* path, int arg);
int __cdecl main_RunFrameLoop(void* p, int mask);
void __cdecl d2_RunDomizilKabinettDialog(int unused, char* p);
void __cdecl d2_RunKanoneUI(int h);
void __cdecl d2_RunDomizilKanoneMenu(int dlg, char* msg);

/* ADDRESS: GOLDTL 0x0058ae60 */
/* ADDRESS: GOLDDE 0x00570b20 */
void __cdecl d2_RunDomizilKanoneMenu(int dlg, char* msg)
{
	char* control;

	control = 0;
	d2_ClearStatusTextSlots();
	if (!main_RunFrameLoop((void*) d2_RunDomizilKanoneMenu, 0x67fff)) {
		return;
	}
	do {
		if (d2_SelectedEntityUiFlags & 0x400) {
			control = RegisterStatusText("contact_KANONE", g_14b5494, 0x16);
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (sv_ClickedObjekt != 0) {
			if (*(int*) (msg + 0x1c) != 0) {
				d2_RunDomizilKabinettDialog(dlg, msg);
			} else if (sv_ClickedObjekt == control) {
				d2_RunKanoneUI(dlg);
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunDomizilKanoneMenu, 0x67fff));
}
