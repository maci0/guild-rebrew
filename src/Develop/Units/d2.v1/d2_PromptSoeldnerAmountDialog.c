#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct
{
	char pad[0x21c];
} Player;
// SIZE 0x21c

extern int main_LoopFlags;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char io_LastKeyScancode;
extern int g_14abbf4;
extern int io_RightButtonReleased;
extern char s_68d704[];

int __cdecl gm_CheckEntityStock(Player*, int, char);
int __cdecl d2_LoadForm(int, int, char*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl gm_AccumulateTyped2(Player*);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_CenterDialogWindows(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_PromptSoeldnerAmountDialog(void)
{
	int timer;
	int r;
	int dlg;
	int ctl;
	int v;

	r = 0;
	timer = main_LoopFlags;
	if (gm_CheckEntityStock(((Player *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 0x140, (*(char*)&gm_ActiveTownIndex)) == 0) {
		return 0;
	}
	dlg = d2_LoadForm(0, 0, s_68d704);
	ctl = d2_GetWindowListItem(dlg, 0, io_AppendText(0x1a34, (unsigned char) (*(char*)&gm_ActiveTownIndex)));
	v = gm_AccumulateTyped2(((Player *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
	if (v >= 0x12c0) {
		v = 0x12c0;
	}
	d2_SetElementValue(ctl, 0xa, v / 32, 0xa);
	d2_CenterDialogWindows(dlg);
	if (main_RunFrameLoop((void*) d2_PromptSoeldnerAmountDialog, timer) != 0) {
		do {
			if (d2_DialogButtonAction != 2) {
				if (d2_DialogButtonAction == 1 || io_LastKeyScancode == 1) {
					d2_DialogCloseRequested = 1;
					r = 0;
				}
			}
			else {
				d2_ShowModalMessageBox(g_14abbf4, 4);
				d2_DialogCloseRequested = 1;
				r = d2_GetControlValue(ctl);
			}
			if (io_RightButtonReleased != 0) {
				d2_DialogCloseRequested = 1;
			}
		} while (main_RunFrameLoop((void*) d2_PromptSoeldnerAmountDialog, timer) != 0);
	}
	d2_DestroyForm(dlg);
	return r;
}
