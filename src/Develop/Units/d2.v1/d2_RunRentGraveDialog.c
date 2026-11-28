


extern int d2_CurrentWindowId;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6a96f4[];
extern char g_6a4078[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl io_AppendText();
void __cdecl d2_RefreshRentAGraveOptions(char* a, int dlg, int mode, int* ids, int* sel);
int __cdecl d2_UpdateRentGraveOptions(char* a1, int a2, int a3, int* a4, int* a5);
int __cdecl d2_RunFriedhofDialog(char* a1, int a2, int a3, int a4);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementEnabled(int i, int flag);
void __cdecl d2_SetFormVisibility(int k, int flag);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_RunRentGraveDialog(char* p, int a1, int a2)
{
	int sel;
	int res;
	int ids[4];
	int d;
	int back;
	int i;

	sel = 0;
	res = 0;
	d = d2_LoadForm(0, 0, g_6a96f4);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(d);
	d2_SetForm(d, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(d, 1);
	io_AppendText(0x4113, 0x4112);
	d2_RefreshRentAGraveOptions(p, d, 2, ids, &sel);
	d2_SetForm(d, 3);
	back = d2_GetWindowListItem(d, 3, io_AppendText(g_6a4078, 0x4119));
	d2_SetElementEnabled(back, d2_UpdateRentGraveOptions(p, a1, a2, ids, &sel));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (d2_CurrentElementId == back) {
				d2_SetFormVisibility(d, 0);
				if (d2_RunFriedhofDialog(p, a1, a2, sel) == 1) {
					res = 1;
					g_774654 = 1;
				}
				d2_SetFormVisibility(d, 1);
			}
			else {
				for (i = 0; i < 4; i++) {
					if (d2_CurrentElementId == ids[i] && i != sel) {
						goto found;
					}
				}
				continue;
found:
				sel = i;
				d2_RefreshRentAGraveOptions(p, d, 2, ids, &sel);
				d2_SetElementEnabled(back, d2_UpdateRentGraveOptions(p, a1, a2, ids, &sel));
			}
		}
	} while (main_RunFrameLoop(d2_RunRentGraveDialog, 0x677c7) != 0);
	d2_DestroyForm(d);
	return res;
}
