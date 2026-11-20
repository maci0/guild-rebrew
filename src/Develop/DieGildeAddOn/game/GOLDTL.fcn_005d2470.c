int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c4510(void*, int);
int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
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
	dlg = fcn_00470820(0, 0, (char*) 0x6acbac);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f4c);
	if (flag != 0) {
		io_AppendText(0x1f4f);
	} else {
		slider = fcn_00472250(dlg, 1,
		    io_AppendText(0x1f4d, *arg3, *(unsigned char*) &g_773d75));
		hv = io_AppendText(0x1f4e);
		confirm = fcn_00472250(dlg, 1, hv);
		vc = fcn_00472250(dlg, 1, hv + 1);
		fcn_00472380(slider,
		    fcn_0050b710(v14, *(unsigned char*) &g_773d75),
		    fcn_0050b710(ebp, *(unsigned char*) &g_773d75),
		    fcn_0050b710(v14, *(unsigned char*) &g_773d75));
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
			hv = fcn_00471f80(slider);
			uv = fcn_0050b750(hv, *(unsigned char*) &g_773d75);
			if (fcn_00526010((void*) ((unsigned long)((char*)&((ENTITY_RECORD*)g_7f4ca0)[
*(unsigned short*) &g_774970])), uv,
				*(unsigned char*) &g_773d75) != 0) {
				flags = *(unsigned int*) ((char*) arg2 + 0x1c8) | 0x20;
				fcn_004c4eb0((char*) 0x6acba4);
				fcn_004c5150(*(int*) ((char*) arg3 + 4),
				    *(int*) ((char*) arg2 + 4),
				    *(unsigned char*) &g_773d75, uv);
				fcn_004c4510(arg2, *(int*) ((char*) arg2 + 4));
				cm_AppendPacketFieldDelta(4, 1, 0x1c8, (char*) &flags);
				fcn_004c5360();
				fcn_004c4ef0((char*) 0x6acba4);
			}
			r = 1;
			g_774654 = 1;
		} else if (d2_CurrentElementId == vc) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) d2_ShowGiftDialog, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
