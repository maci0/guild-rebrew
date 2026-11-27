

#include <string.h>
#pragma intrinsic(memset)

#include "client_types.h"
typedef D2_RADIO_GROUP Group;
// SIZE 0x8c

// SIZE 0x2f4
typedef struct {
	char pad0[0x38];
	int shown;
	int active;
	char pad40[0x2b0];
	unsigned char* obj;
} Slot5ada;

extern D2_RADIO_GROUP g_102cbc4[8];
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern char g_6ab1e4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00476b60(void);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl d2_GetFormWindow(int k, int j);
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id);
void __cdecl d2_ClearRadioGroup(int i);
unsigned char* __cdecl fcn_00502cd0(int, int, int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_EvalEntityInventoryValue(unsigned char* o, int* out);
void __cdecl cm_RequestFreeEntity(int);
int __cdecl d2_CreateRadioGroup(int n, ...);
void __cdecl d2_AddToRadioGroup(int g, int id);
int __cdecl fcn_0046c690(int a);
int __cdecl cm_SendRemoveLinkedObject(int a1, int a2, int a3);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunDiebesgildeInfoDialog(char* p)
{
	int n;
	int i;
	int back;
	int val[2];
	unsigned char* carts[8];
	int btns[16];
	unsigned char* e;
	unsigned char* q;
	int refresh;
	int grp;
	int d;
	int j;
	int b;
	int r;

	refresh = 1;
	n = 0;
	grp = -1;
	d = fcn_00470820(0, 0, g_6ab1e4);
	d2_CenterDialogWindows(d);
	d2_SetForm(d, 1);
	io_AppendText(0x19fb);
	d2_SetOverlayAnimation(0, 0);
	fcn_00476b60();
	d2_SetForm(d, 3);
	back = d2_GetWindowListItem(d, 3, io_AppendText(0x1ba6));
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, d2_GetFormWindow(d, 2), 0x767);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (refresh != 0) {
			memset(carts, 0, sizeof(carts));
			if (grp != -1) {
				d2_ClearRadioGroup(grp);
				grp = -1;
			}
			d2_SetForm(d, 2);
			io_AppendText(g_6811b0);
			j = 0;
			for (e = fcn_00502cd0(*(int*) (p + 0x5d), 1, 0, 0xca); e != 0 && j < 8; e = gm_NextEntityQueryMatch()) {
				q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x2a));
				if (q != 0 && *(unsigned short*) (q + 0x27) != 0xffff) {
					carts[j] = e;
					j++;
				}
			}
			for (i = 0; i < 8; i++) {
				e = carts[i];
				if (e != 0) {
					q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x2a));
					if (q != 0) {
						if (*(unsigned short*) (q + 0x27) == 0xffff) {
							continue;
						}
						gm_EvalEntityInventoryValue(q, val);
						b = d2_GetWindowListItem(d, 2, io_AppendText(0x19fc, *q + 0x427, *(unsigned short*) (q + 0x27), q, e + 0x1c, val[0], val[1], e[0x37], e[0x36]));
						btns[n] = b;
						(*(unsigned char**)&((D2_CONTROL_TL*)g_1015ea0)[b].associated_object) = q;
						if (grp == -1) {
							grp = d2_CreateRadioGroup(1, b);
							(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_038) = 1;
							(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[b].value_03c) = 1;
							(*(unsigned char**)&((D2_CONTROL_TL*)g_1015ea0)[b].associated_object) = q;
							g_102cbc4[grp].sel = 0;
							n++;
						}
						else {
							d2_AddToRadioGroup(grp, b);
							n++;
						}
					}
					else {
						cm_RequestFreeEntity(*(int*) (e + 2));
					}
				}
			}
			refresh = 0;
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == back && grp != -1) {
			i = fcn_0046c690(grp);
			if (i >= 0) {
				r = cm_SendRemoveLinkedObject(*(int*) (p + 1), -1, *(int*) (carts[i] + 2));
				while (cm_GetCommandStatus(r) == 0) {
					cm_StepCommandQueue();
				}
				refresh = 1;
			}
		}
	} while (main_RunFrameLoop(d2_RunDiebesgildeInfoDialog, 0x677c7) != 0);
	if (grp != -1) {
		d2_ClearRadioGroup(grp);
	}
	d3_EndCameraAndUiMode();
	d2_DestroyForm(d);
}
