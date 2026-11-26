extern int g_7e2468;
extern char g_7e2430[5];
extern char g_7e23e3;
extern int g_14abee0[];
extern int g_774654;
extern int g_1040494;
extern int d2_ScreenHeight;
int __cdecl d3_SelectSceneContext();
int __cdecl d2_CreateRadioGroup();
int __cdecl d2_AddToRadioGroup();
int __cdecl d2_ClearRadioGroup();
int __cdecl d2_SelectRadioGroup();
int __cdecl d2_UpdateRadioGroup();
int __cdecl fcn_00470820();
int __cdecl fcn_00471af0();
int __cdecl d2_CenterDialogWindows();
int __cdecl fcn_00471e30();
int __cdecl d2_GetWindowListItem();
int __cdecl d2_SetForm();
int __cdecl fcn_004730c0();
int __cdecl fcn_00473150();
int __cdecl fcn_004e4470();
int __cdecl fcn_004e44f0();
typedef struct {
	short w[3];
} Name6_53e020;
typedef struct {
	char b[5];
} Name5_53e020;

int __cdecl gm_FindHeadIconIndex();
Name6_53e020 __cdecl fcn_00506d50(int);
int __cdecl io_AppendText();
int __cdecl d2_OpenMessageBox();
int __cdecl main_RunFrameLoop();
int __cdecl d2_RunParentProfessionSelection();
int __cdecl d2_ShowChooseProfessionDialog();
int __cdecl d2_RunChoosePlayerDialog();
int __cdecl fcn_0053e8a0();


#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x0053e020 */
int __cdecl d2_RunChooseHistoryMenu(void)
{
	int v12;
	int v13;
	int v1;
	int dialog;
	int v3;
	int v4;
	int v5;
	int v6;
	int group;
	int r;
	Name6_53e020 v11;

	v12 = 0;
	v1 = 0;
	v13 = -1;
	dialog = fcn_00470820(0, 0, 0x68116c);
	d2_CenterDialogWindows(dialog);
	d2_SetForm(dialog, 0);
	v3 = io_AppendText(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca);
	v4 = d2_GetWindowListItem(dialog, 0, v3);
	v5 = d2_GetWindowListItem(dialog, 0, v3 + 1);
	v6 = d2_GetWindowListItem(dialog, 0, v3 + 2);
	v3 = d2_GetWindowListItem(dialog, 0, v3 + 3);
	if (*(unsigned char*) &g_6a375c > 1) {
		v13 = d2_GetWindowListItem(dialog, 0, io_AppendText(0x681164, 2, 0x1acb));
	}
	if (*(int*) 0x776700 <= -1) {
		*(int*) 0x776700 = -1;
	}
	group = d2_CreateRadioGroup(4, v4, v5, v6, v3);
	r = *(int*) 0x776700;
	if (r != -1) {
		d2_SelectRadioGroup(group, r + 1);
	} else {
		d2_SelectRadioGroup(group, 0);
	}
	d2_AddToRadioGroup(group, d2_GetWindowListItem(dialog, 0, io_AppendText(0x7e)));
	for (;;) {
		if (main_RunFrameLoop((int)d2_RunChooseHistoryMenu, 0xc6) == 0) {
			break;
		}
		d2_UpdateRadioGroup(group);
		if (g_14ce8e0 || *(unsigned char*) &g_14cf950 == 1 || *(int*) &g_100f1dc == 1) {
			g_774654 = 1;
		}
		r = *(int*) &g_100f1dc;
		if (r == 2 || v1) {
			v1 = 0;
			if (d2_CurrentElementId == v4) {
				*(unsigned char*) &g_6a3440 = 0xff;
			} else if (d2_CurrentElementId == v5) {
				*(unsigned char*) &g_6a3440 = 1;
			} else if (d2_CurrentElementId == v6) {
				*(unsigned char*) &g_6a3440 = 2;
			} else if (d2_CurrentElementId == v3) {
				*(unsigned char*) &g_6a3440 = 3;
			} else if (d2_CurrentElementId == v13) {
				*(unsigned char*) &g_6a3440 = 5;
			}
			r = *(signed char*) &g_6a3440;
			*(int*) 0x776700 = r;
			if (r != -1) {
				d2_SelectRadioGroup(group, r + 1);
			} else {
				d2_SelectRadioGroup(group, 0);
			}
			fcn_00471af0(dialog, 0);
			*(int*) &main_LoopFlags = 0x12d6;
			cut_EventLoopFlags = 0x12d6;
			fcn_004e44f0(fcn_004e4470(0x6a4040));
			v12 = d2_RunChoosePlayerDialog(0xc6, 0);
			if (v12 == 0) {
				*(int*) &main_LoopFlags = 0x12d6;
				cut_EventLoopFlags = 0x12d6;
				fcn_004e44f0(fcn_004e4470(0x6a4024));
			} else {
				r = fcn_0053e8a0(0);
				if (r == 1) {
					d2_SuppressOverlay = r;
					*(int*) 0x6a37f8 = d2_OpenMessageBox(g_14abee0[9], 0);
					if (d2_RunParentProfessionSelection(0) == 0) {
						d3_SelectSceneContext(0, 0);
						v1 = 1;
					}
				} else if (r == 0) {
					if (d2_ShowChooseProfessionDialog(0xc6) != 0) {
						v11 = fcn_00506d50((unsigned char) g_7e23e3);
						*(Name5_53e020*) g_7e2430 = *(Name5_53e020*) &v11;
						g_7e2468 = gm_FindHeadIconIndex(0x6a3db4) + 0x639;
					} else {
						d3_SelectSceneContext(0, 0);
						v12 = 0;
						v1 = 1;
					}
				} else if (r == -1) {
					v12 = 0;
					v1 = 1;
				}
			}
			fcn_00471af0(dialog, 1);
			if (v12 != 0) {
				if (*(unsigned char*) &g_6a375c >= 1) {
					*(int*) &g_7747b0 |= 8;
				}
				g_774654 = 1;
				v12 = 1;
			}
		} else {
			v1 = 0;
			if (r == 1) {
				g_774654 = r;
			}
		}
	}
	d2_ClearRadioGroup(group);
	fcn_00471e30(dialog);
	if (v12 != 0) {
		v3 = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, 0x67d67c, 100, 1);
		*(int*) &main_LoopFlags = 0x12d6;
		cut_EventLoopFlags = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4060));
		if (v3 != 0) {
			fcn_00473150(v3);
			return v12;
		}
	} else {
		*(int*) &main_LoopFlags = 0x12d6;
		cut_EventLoopFlags = 0x12d6;
		fcn_004e44f0(fcn_004e4470(0x6a4024));
	}
	return v12;
}
