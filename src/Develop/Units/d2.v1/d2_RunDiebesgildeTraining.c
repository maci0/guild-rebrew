

#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_training_rows.h"
// SIZE 0x40

 
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_ResetTrainingRows(char*);
int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_UpdateTrainingRows(int, int);

int __cdecl d2_GetControlValue(int);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl d2_RunDiebesgildeTraining(char* e)
{
	int dlg;
	int i;

	if (d2_CheckOwnerBlocked(e) == 0) {
		dlg = d2_LoadForm(0, 0, "locations\\diebesgilde\\diebesgilde_trainieren");
		d2_ResetTrainingRows(e);
		d2_SetOverlayAnimation(0, 0);
		do {
			d2_UpdateTrainingRows(dlg, 2);
			if (io_RightButtonReleased != 0) {
				if (CountDisplayCounters() == 0) {
					d2_DialogCloseRequested = 1;
				} else {
					for (i = 0; i < 32; i++) {
						if (d2_TrainingRows[i].row_element != -1 && d2_GetControlValue(d2_TrainingRows[i].row_element) != 0) {
							d2_SetElementValue(d2_TrainingRows[i].row_element, 0);
						}
					}
					ResetDisplayCounters();
				}
			}
			if (d2_DialogButtonAction != -1 && d2_DialogButtonAction == 0x113) {
				for (i = 0; i < 32; i++) {
					if (d2_TrainingRows[i].row_element != -1 && d2_GetControlValue(d2_TrainingRows[i].row_element) != 0) {
						d2_SetElementValue(d2_TrainingRows[i].row_element, 0);
					}
				}
				ResetDisplayCounters();
			}
		} while (main_RunFrameLoop((void*) d2_RunDiebesgildeTraining, 0x677c7) != 0);
		d2_DestroyForm(dlg);
		d3_EndCameraAndUiMode();
	}
}
