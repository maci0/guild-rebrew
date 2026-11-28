#include "Develop/DieGildeAddOn/game/client_actions.h"
#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/Units/d2.v1/d2_window_view.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int g_14b5e04;
extern int g_14b5e08;
extern int g_14b5e0c;
extern int g_14b5e10;
extern int g_14b5e14;
extern int g_14b5e18;

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl cm_SendSetHE(char, unsigned char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_EqualizeWindowButtonWidths(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int, int);
void __cdecl d2_SetValueGaugeStepLabels(int, int, int, int, int);
void __cdecl d2_CreateButtonRow(int, int, int*, int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_CalcPersonWealth(unsigned short);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_CheckEntityStock(void*, int, unsigned char);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDTL 0x005bf580 */
/* ADDRESS: GOLDDE 0x005a19c0 */
int __cdecl d2_RunSpionageDialog(char* rec)
{
	char* q;
	char* h;
	int tries;
	int sel[2];
	int ret;
	int row;
	unsigned char pkt[0xf8];
	char buf[0x400];
	int row2;
	int v;
	int w1;
	int w2;
	int n;
	int ea;
	float f;
	float f2;

	ret = 0; tries = 0;
	q = he_StartHandlungSearch(2, 2, gm_LocalPlayerSlot, 0, 0x18);
	if (q != 0) {
		for (;;) {
			if (*(int*) (q + 0xc4) == *(int*) (rec + 4)) {
				io_FormatTextBuffer(buf, 0x42c1, *(unsigned short*) rec);
				if (d2_ShowModalMessageBox(buf, 0x101) != 0) {
					*(pos14_7f4c00*) (q + 0x52) = gm_GameTime;
					*(int*) (q + 0x84) = cm_SendSetHE(-1, (unsigned char*) q);
				}
				return 0;
			}
			tries++;
			q = he_fn_Handlung();
			if (q != 0)
				continue;
			break;
		}
		if (tries >= 5) {
			io_FormatTextBuffer(buf, 0x42c0, 5);
			d2_ShowModalMessageBox(buf, 0x104);
			return 0;
		}
	}
	h = (char*) d2_LoadForm(0, 0, "locations\\wohnsitz\\spy");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows((int) h);
	d2_SetForm((int) h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm((int) h, 2);
	row = d2_EqualizeWindowButtonWidths(0, 3, g_14b5e18, d2_CurrentWindowId);
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[row].value_06c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[row].width)) = ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width;
	d2_SetElementFont(row, 0x54);
	row2 = d2_AddWindowValueGauge(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 0x82, d2_CurrentWindowId);
	d2_CreateGuiWindow(row2, 0, 2, 0, 1);
	d2_SetValueGaugeStepLabels(row2, 3, g_14b5e0c, g_14b5e10, g_14b5e14);
	d2_SetForm((int) h, 3);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, sel, 2, g_14b5e04, g_14b5e08);
	while (main_RunFrameLoop((void*) d2_RunSpionageDialog, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0 || *(unsigned short*) rec == 0xffff) {
			d2_DialogCloseRequested = 1;
		} else {
			v = d2_GetControlValue(row2);
			f = (float) v * 0.33f + 1.0f;
			w1 = gm_CalcPersonWealth(*(unsigned short*) (((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot])));
			f2 = (float) w1 * 0.005f;
			w2 = gm_CalcPersonWealth(*(unsigned short*) rec);
			n = (int) ((float) w2 * 0.005f + f2);
			n = (int) ((float) n * f);
			d2_SetForm((int) h, 1);
			io_AppendText((int) 0x6811b0);
			io_AppendText(0x42b8, n, *(unsigned short*) rec);
			if (d2_DialogButtonAction != -1) {
				if (d2_CurrentElementId == sel[0]
					&& gm_CheckEntityStock(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), n, gm_ActiveTownIndex) != 0) {
					pkt[4] = 0x18;
					*(int*) (pkt + 8) = *(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
					*(int*) (pkt + 0xc) = -1;
					pkt[0x36] = 2;
					*(int*) (pkt + 0x70) = *(int*) (rec + 4);
					ea = *(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].ptr_170;
					*(int*) (pkt + 0x58) = ea != 0 ? *(int*) (ea + 1) : -1;
					*(int*) (pkt + 0x90) = n;
					cm_SendLogAction("spionage");
					*(int*) (pkt + 0x94) = d2_GetControlValue(row2);
					cm_SendCopyEntityData(pkt);
					cm_SendTraceEnd("spionage");
					io_FormatTextBuffer(buf, 0x42bf, *(unsigned short*) rec);
					d2_ShowModalMessageBox(buf, 0x100);
					d2_DialogCloseRequested = 1;
					ret = 1;
				} else if (d2_CurrentElementId == sel[1]) {
					d2_DialogCloseRequested = 1;
				}
			}
		}
	}
	d2_DestroyForm((int) h);
	d3_EndCameraAndUiMode();
	return ret;
}
