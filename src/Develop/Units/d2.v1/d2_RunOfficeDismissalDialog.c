

typedef struct
{
	int x0;
	int x4;
	char pad8[0xc];
} Req;
// SIZE 0x14

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern char s_6aaf90[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText(int, ...);
void __cdecl amt_HandleOfficeAction(char*, Req*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x0058f370 */
int __cdecl d2_RunOfficeDismissalDialog(unsigned short* target)
{
	Req s;
	int r;
	int dlg;
	int v;

	r = 0;
	dlg = d2_LoadForm(0, 0, s_6aaf90);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x167c);
	d2_SetForm(dlg, 2);
	if (gm_EntitySlotTable[gm_LocalPlayerSlot * 540 + 9] == 0) {
		v = (unsigned char) gm_EntitySlotTable[gm_LocalPlayerSlot * 540 + 0x169] + 0x253;
	} else {
		v = (unsigned char) gm_EntitySlotTable[gm_LocalPlayerSlot * 540 + 0x169] + 0x27b;
	}
	io_AppendText(0x167f, v, 8, *target);
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (d2_DialogButtonAction == 2) {
			s.x4 = *(int*) (target + 2);
			s.x0 = 1;
			amt_HandleOfficeAction(gm_EntitySlotTable + gm_LocalPlayerSlot * 540, &s);
			d2_DialogCloseRequested = 3;
			r = 1;
		} else if (d2_DialogButtonAction == 1) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunOfficeDismissalDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
