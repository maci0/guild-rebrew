


#include <stdlib.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;
extern char s_6acc44[];
extern char s_679060[];
#include "Develop/Units/d2.v1/client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl cm_RequestModifyHealth(int, int);
int __cdecl cm_RequestChangeBits(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
int __cdecl gm_CureRandomAffliction(unsigned char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_CheckActionBlocker(unsigned char*, int);
int __cdecl gm_CheckEntityStock(unsigned char*, int, char);
void __cdecl io_FormatTextBuffer(char*, ...);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ShowMedicusDialog(unsigned char* e)
{
	int money;
	int result;
	int dlg;
	char tmp[0x100];
	char text[0x400];
	int half;
	int id;
	int ok;
	int cancel;
	int h;

	result = 2;
	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 2) {
			return 0;
		}
		half = abs(*(int*) (e + 0x24)) / 2;
		money = (int) (gm_WalkEntityChain(*(unsigned short*) e) * 0.02f);
		cm_RequestModifyHealth(*(int*) (e + 4), -2);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x40, 0);
		if (gm_RandomMod(2)) {
			cm_RequestMoveCredits(-1, *(int*) (e + 4), gm_ActiveTownIndex, money);
			gm_ApplyEntityHealthDelta(*(unsigned short*) e, half);
			gm_CureRandomAffliction(e);
		}
		return 0x11;
	}
	money = (int) (gm_WalkEntityChain(*(unsigned short*) e) * 0.02f);
	dlg = d2_LoadForm(0, 0, s_6acc44);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	id = io_AppendText(0x1d3b, 2, money);
	ok = d2_GetWindowListItem(dlg, 1, id);
	cancel = d2_GetWindowListItem(dlg, 1, id + 1);
	d2_DialogButtonAction = -1;
	do {
		if (d2_DialogButtonAction != -1) {
			if (d2_CurrentElementId == ok) {
				if (d2_CheckActionBlocker(e, 2) && gm_CheckEntityStock(e, money, gm_ActiveTownIndex)) {
					cm_RequestModifyHealth(*(int*) (e + 4), -2);
					io_FormatTextBuffer(text, 0x1d3c);
					if (gm_RandomMod(2)) {
						io_FormatTextBuffer(tmp, s_679060, 0x1d3d);
						strcat(text, tmp);
						cm_RequestMoveCredits(-1, *(int*) (e + 4), gm_ActiveTownIndex, money);
						gm_CureRandomAffliction(e);
					} else {
						io_FormatTextBuffer(tmp, s_679060, 0x1d3e);
						strcat(text, tmp);
					}
					ok = -1;
					cancel = -1;
					result = 0x81;
					h = cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x40, 0);
					while (cm_GetCommandStatus(h) == 0) {
						cm_StepCommandQueue();
					}
					d2_ShowModalMessageBox(text, 0);
					d2_DialogCloseRequested = 1;
				}
			} else if (d2_CurrentElementId == cancel) {
				d2_DialogCloseRequested = 1;
			}
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowMedicusDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return result;
}
