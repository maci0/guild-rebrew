#include "client_actions.h"
#include "client_data.h"
#include "Develop/Units/d2.v1/d2_window_view.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;
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
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_004c5620(char, unsigned char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
void __cdecl fcn_00533a60(int, int, int*, int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_CheckEntityStock(void*, int, unsigned char);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_SendCopyEntityData(void*);

/* ADDRESS: GOLDTL 0x005bf580 */
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
	q = he_StartHandlungSearch(2, 2, g_774970, 0, 0x18);
	if (q != 0) {
		for (;;) {
			if (*(int*) (q + 0xc4) == *(int*) (rec + 4)) {
				io_FormatTextBuffer(buf, 0x42c1, *(unsigned short*) rec);
				if (fcn_00526120(buf, 0x101) != 0) {
					*(pos14_7f4c00*) (q + 0x52) = gm_GameTime;
					*(int*) (q + 0x84) = fcn_004c5620(-1, (unsigned char*) q);
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
			fcn_00526120(buf, 0x104);
			return 0;
		}
	}
	h = (char*) fcn_00470820(0, 0, "locations\\wohnsitz\\spy");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows((int) h);
	d2_SetForm((int) h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm((int) h, 2);
	row = fcn_0046fac0(0, 3, g_14b5e18, d2_CurrentWindowId);
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[row].value_06c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[row].width)) = ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width;
	d2_SetElementFont(row, 0x54);
	row2 = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 0x82, d2_CurrentWindowId);
	fcn_00472380(row2, 0, 2, 0, 1);
	fcn_00468bb0(row2, 3, g_14b5e0c, g_14b5e10, g_14b5e14);
	d2_SetForm((int) h, 3);
	fcn_00533a60(d2_CurrentWindowId, 0, sel, 2, g_14b5e04, g_14b5e08);
	while (main_RunFrameLoop((void*) d2_RunSpionageDialog, 0x677c7) != 0) {
		if (g_14ce8e0 != 0 || *(unsigned short*) rec == 0xffff) {
			g_774654 = 1;
		} else {
			v = d2_GetControlValue(row2);
			f = (float) v * 0.33f + 1.0f;
			w1 = gm_WalkEntityChain(*(unsigned short*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970])));
			f2 = (float) w1 * 0.005f;
			w2 = gm_WalkEntityChain(*(unsigned short*) rec);
			n = (int) ((float) w2 * 0.005f + f2);
			n = (int) ((float) n * f);
			d2_SetForm((int) h, 1);
			io_AppendText((int) 0x6811b0);
			io_AppendText(0x42b8, n, *(unsigned short*) rec);
			if (g_100f1dc != -1) {
				if (d2_CurrentElementId == sel[0]
					&& gm_CheckEntityStock(((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), n, g_773d75) != 0) {
					pkt[4] = 0x18;
					*(int*) (pkt + 8) = *(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
					*(int*) (pkt + 0xc) = -1;
					pkt[0x36] = 2;
					*(int*) (pkt + 0x70) = *(int*) (rec + 4);
					ea = *(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].ptr_170;
					*(int*) (pkt + 0x58) = ea != 0 ? *(int*) (ea + 1) : -1;
					*(int*) (pkt + 0x90) = n;
					cm_SendLogAction("spionage");
					*(int*) (pkt + 0x94) = d2_GetControlValue(row2);
					cm_SendCopyEntityData(pkt);
					cm_SendTraceEnd("spionage");
					io_FormatTextBuffer(buf, 0x42bf, *(unsigned short*) rec);
					fcn_00526120(buf, 0x100);
					g_774654 = 1;
					ret = 1;
				} else if (d2_CurrentElementId == sel[1]) {
					g_774654 = 1;
				}
			}
		}
	}
	fcn_00471e30((int) h);
	fcn_00532ef0();
	return ret;
}
