extern char g_68114c[];
extern char g_681140[];
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int main_LoopFlags;

struct list_4b3fe0 {
	int sel;
	int items[34];
};
// SIZE 0x8c

#include "Develop/client_types.h"
extern List8c_102cbc8 d2_RadioGroupItems[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl d2_CreateRadioGroup(int);
int* __cdecl gm_FindNextMissionSpec(int, int*);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_AddToRadioGroup(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
int __cdecl d2_ShowMissionBriefingDialog(int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);


/* ADDRESS: GOLDTL 0x004b3fe0 */
int __cdecl d2_ChooseMission(int missionKey)
{
	int result;
	int h;
	int lst;
	int prev;
	int k;
	int* it;
	int* e;

	result = 0xff;
	h = d2_LoadForm(0, 0, g_68114c);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1ace);
	d2_SetForm(h, 2);
	prev = d2_CurrentWindowId;
	d2_SetForm(h, 0);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, prev, 0x767);
	d2_SetForm(h, 2);
	lst = d2_CreateRadioGroup(0);
	for (it = gm_FindNextMissionSpec(missionKey, 0); it != 0; it = gm_FindNextMissionSpec(missionKey, it)) {
		k = d2_GetWindowListItem(h, 2, io_AppendText((int) g_681140, it[2]));
		*(int**) (((char*)&((D2_CONTROL_TL*)d2_Controls)[k].associated_object)) = it;
		d2_AddToRadioGroup(lst, k);
	}
	while (main_RunFrameLoop(d2_ChooseMission, 0x1c6) != 0) {
		d2_UpdateRadioGroup(lst);
		if (io_RightButtonReleased != 0 || io_LastKeyScancode == 1 || d2_DialogButtonAction == 1)
			d2_DialogCloseRequested = 1;
		if (d2_DialogButtonAction != -1 && ((struct list_4b3fe0*)d2_RadioGroupItems)[lst].sel != -1
		    && d2_CurrentElementId == ((struct list_4b3fe0*)d2_RadioGroupItems)[lst].items[((struct list_4b3fe0*)d2_RadioGroupItems)[lst].sel]) {
			e = *(int**) (&((D2_CONTROL_TL*)d2_Controls)[((struct list_4b3fe0*)d2_RadioGroupItems)[lst].items[((struct list_4b3fe0*)d2_RadioGroupItems)[lst].sel]].associated_object);
			if (d2_ShowMissionBriefingDialog(*e, main_LoopFlags) != 0) {
				result = *e;
				d2_DialogCloseRequested = 1;
			}
		}
	}
	d2_ClearRadioGroup(lst);
	d2_DestroyForm(h);
	return result;
}
unsigned char _dpad_102cbc8[46456];
