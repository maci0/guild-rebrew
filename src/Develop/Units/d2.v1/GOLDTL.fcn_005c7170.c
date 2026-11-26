

#include "client_types.h"
#include "Develop/Units/d2.v1/d2_training_rows.h"
// SIZE 0x40

 
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_ResetTrainingRows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_UpdateTrainingRows(int, int);

int __cdecl d2_GetControlValue(int);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_005c7170(int a1)
{
	int dlg;
	int i;

	dlg = fcn_00470820(0, 0, "locations\\diebesgilde\\diebesgilde_trainieren");
	d2_CenterDialogWindows(dlg);
	d2_ResetTrainingRows(a1);
	d2_SetOverlayAnimation(0, 0);
	do {
		d2_UpdateTrainingRows(dlg, 2);
		if (g_14ce8e0 != 0) {
			if (CountDisplayCounters() == 0) {
				g_774654 = 1;
			} else {
				for (i = 0; i < 32; i++) {
					if (g_7774a0[i].row_element != -1 && d2_GetControlValue(g_7774a0[i].row_element) != 0) {
						d2_SetElementValue(g_7774a0[i].row_element, 0);
					}
				}
				ResetDisplayCounters();
			}
		}
		if (g_100f1dc != -1 && g_100f1dc == 0x113) {
			for (i = 0; i < 32; i++) {
				if (g_7774a0[i].row_element != -1 && d2_GetControlValue(g_7774a0[i].row_element) != 0) {
					d2_SetElementValue(g_7774a0[i].row_element, 0);
				}
			}
			ResetDisplayCounters();
		}
	} while (main_RunFrameLoop((void*) fcn_005c7170, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
