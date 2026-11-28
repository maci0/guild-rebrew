


#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






#include "Develop/DieGildeAddOn/game/game_player.h"
extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char g_6ac494[];

int __cdecl d2_CheckActionBlocker(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
unsigned short* __cdecl d2_OpenTargetPicker(int*, char*, int, int);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
void __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_LoadForm(int, int, void*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_RequestModifyHealth(int id, int k);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShowAnschwaerzenDialog(int selected_obj)
{
	int cancel_btn;
	int confirm_btn;
	int msg[0x14];
	char buf[0x40];
	char text[0x200];
	unsigned short* accused;
	unsigned short* judge;
	int crime_count;
	int dlg;
	int text_idx;
	int judge_id;

	if (d2_CheckActionBlocker(&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 2) == 0) {
		return;
	}
	if (selected_obj == 0) {
		return;
	}
	memset(msg, 0, sizeof(msg));
	msg[1] = 0x400;
	msg[4] = 6;
	msg[2] = (*(int*)&g_666018);
	msg[3] = g_66601c;
	io_FormatTextBuffer(buf, 0x175f);
	accused = d2_OpenTargetPicker(msg, buf, 0, 0);
	if (accused == 0) {
		return;
	}
	io_FormatTextBuffer(buf, 0x1760, *accused);
	judge = d2_OpenTargetPicker(msg, buf, 0, 0);
	if (judge == 0) {
		return;
	}
	crime_count = CountMatchingStraftatEntries(*(int*) (accused + 2), g_774970);
	if (crime_count <= 0) {
		io_FormatTextBuffer(text, 0x1756, *accused);
		d2_ShowModalMessageBox(text, 0);
		d3_EndCameraAndUiMode();
		return;
	}
	if (d2_CheckActionBlocker(&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 3) == 0) {
		d3_EndCameraAndUiMode();
		return;
	}
	dlg = d2_LoadForm(0, 0, g_6ac494);
	d2_CenterDialogWindows(dlg);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	text_idx = io_AppendText(0x1761, crime_count, (crime_count != 1) + 0x1752, *judge, *accused);
	confirm_btn = d2_GetWindowListItem(dlg, 1, text_idx);
	cancel_btn = d2_GetWindowListItem(dlg, 1, text_idx + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == confirm_btn) {
				char ev[0xf8];

				judge_id = *(int*) (judge + 2);
				*(int*) (ev + 8) = judge_id;
				*(int*) (ev + 0xc) = judge_id;
				*(int*) (ev + 0x5c) = ((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id;
				*(int*) (ev + 0x60) = judge_id;
				*(int*) (ev + 0x58) = *(int*) (accused + 2);
				ev[4] = 0x2f;
				ev[0x36] = 9;
				cm_SendCopyEntityData(ev);
				cm_RequestModifyHealth(((ENTITY_RECORD*)g_7f4ca0)[g_774970].entity_id, -3);
				io_FormatTextBuffer(text, 0x1762, *judge);
				d2_ShowModalMessageBox(text, 0);
				g_774654 = 1;
			}
			else if (d2_CurrentElementId == cancel_btn) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_ShowAnschwaerzenDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
