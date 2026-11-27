int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl gm_AmountToUnits(int, unsigned char);
int __cdecl fcn_0050b750(int, int);
int __cdecl gm_CheckEntityStock(void*, int, int);
void __cdecl cm_RequestMoveCredits(int, int, int, int);
void __cdecl cm_BeginPacketFieldDelta(void*, int);
int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
int __cdecl d2_GetControlValue(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
extern int g_14ce8e0, d2_CurrentElementId, g_774654;
#define SHP_REC (((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970]))
#define SHP_ID (*(unsigned short*) SHP_REC)
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005d2470 */
int __cdecl d2_ShowGiftDialog(int* arg2, unsigned short* arg3)
{
	int v14 = -1;
	float v4;
	float selected;
	int flags;
	int v8;
	int ebp;
	int flag;
	int dlg;
	int confirm = -1;
	int vc = -1;
	int r;
	int hv;
	int uv;
	int slider;
#include "Develop/DieGildeAddOn/game/entity_record.h"
	v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	if (v14 < 0x640) {
		v14 = 0x640;
	} else {
		v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	}
	v4 = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
	v8 = gm_AccumulateTyped2(SHP_REC);
	if ((float) v8 > v4) {
		selected = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
	} else {
		selected = (float) gm_AccumulateTyped2(SHP_REC);
	}
	if ((int) selected <= 0xc7f) {
		ebp = 0xc80;
	} else {
		v4 = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
		v8 = gm_AccumulateTyped2(SHP_REC);
		if (!((float) v8 > v4)) {
			selected = (float) gm_AccumulateTyped2(SHP_REC);
		} else {
			selected = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
		}
		ebp = (int) selected;
		if (ebp <= 0) return 0;
	}
	flag = (*(unsigned int*) ((char*) arg2 + 0x1c8) >> 5) & 1;
	dlg = d2_LoadForm(0, 0, (char*) 0x6acbac);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f4c);
	if (flag != 0) {
		io_AppendText(0x1f4f);
	} else {
		slider = d2_GetWindowListItem(dlg, 1,
		    io_AppendText(0x1f4d, *arg3, *(unsigned char*) &g_773d75));
		hv = io_AppendText(0x1f4e);
		confirm = d2_GetWindowListItem(dlg, 1, hv);
		vc = d2_GetWindowListItem(dlg, 1, hv + 1);
		fcn_00472380(slider,
		    gm_AmountToUnits(v14, *(unsigned char*) &g_773d75),
		    gm_AmountToUnits(ebp, *(unsigned char*) &g_773d75),
		    gm_AmountToUnits(v14, *(unsigned char*) &g_773d75));
	}
	*(int*) &g_100f1dc = -1;
	r = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (*(int*) &g_100f1dc == -1 || flag != 0) {
			continue;
		}
		if (d2_CurrentElementId == confirm) {
			hv = d2_GetControlValue(slider);
			uv = fcn_0050b750(hv, *(unsigned char*) &g_773d75);
			if (gm_CheckEntityStock((void*) ((unsigned long)((char*)&((ENTITY_RECORD*)g_7f4ca0)[
*(unsigned short*) &g_774970])), uv,
				*(unsigned char*) &g_773d75) != 0) {
				flags = *(unsigned int*) ((char*) arg2 + 0x1c8) | 0x20;
				cm_SendLogAction((char*) 0x6acba4);
				cm_RequestMoveCredits(*(int*) ((char*) arg3 + 4),
				    *(int*) ((char*) arg2 + 4),
				    *(unsigned char*) &g_773d75, uv);
				cm_BeginPacketFieldDelta(arg2, *(int*) ((char*) arg2 + 4));
				cm_AppendPacketFieldDelta(4, 1, 0x1c8, (char*) &flags);
				cm_RequestChangeAttribute();
				cm_SendTraceEnd((char*) 0x6acba4);
			}
			r = 1;
			g_774654 = 1;
		} else if (d2_CurrentElementId == vc) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_ShowGiftDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	return r;
}
