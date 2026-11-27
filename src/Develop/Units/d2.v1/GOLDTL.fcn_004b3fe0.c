extern char g_68114c[];
extern char g_681140[];
extern int d2_CurrentWindowId;
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern int main_LoopFlags;

struct list_4b3fe0 {
	int sel;
	int items[34];
};
// SIZE 0x8c

#include "client_types.h"
extern List8c_102cbc8 g_102cbc8[];

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
int __cdecl fcn_004b3ec0(int, int);
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
		*(int**) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[k].associated_object)) = it;
		d2_AddToRadioGroup(lst, k);
	}
	while (main_RunFrameLoop(d2_ChooseMission, 0x1c6) != 0) {
		d2_UpdateRadioGroup(lst);
		if (g_14ce8e0 != 0 || g_14cf950 == 1 || g_100f1dc == 1)
			g_774654 = 1;
		if (g_100f1dc != -1 && ((struct list_4b3fe0*)g_102cbc8)[lst].sel != -1
		    && d2_CurrentElementId == ((struct list_4b3fe0*)g_102cbc8)[lst].items[((struct list_4b3fe0*)g_102cbc8)[lst].sel]) {
			e = *(int**) (&((D2_CONTROL_TL*)g_1015ea0)[((struct list_4b3fe0*)g_102cbc8)[lst].items[((struct list_4b3fe0*)g_102cbc8)[lst].sel]].associated_object);
			if (fcn_004b3ec0(*e, main_LoopFlags) != 0) {
				result = *e;
				g_774654 = 1;
			}
		}
	}
	d2_ClearRadioGroup(lst);
	d2_DestroyForm(h);
	return result;
}
unsigned char _dpad_102cbc8[46456];
