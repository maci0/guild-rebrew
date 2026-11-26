/*
 * Scripted scene driver, one step per frame.
 *
 * Creates a script object, runs its state through 0x4693b0 and then drives
 * the three side objects through the 0x471af0 gate while the selected slot
 * at 0x102cbc0 + index * 0x8c reports a state. The object table at 0x777d14
 * (stride 0x18) is refreshed for every entry whose stored handle no longer
 * matches the live handle, and the frame is re-run while 0x5373e0 accepts
 * this function.
 */
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_data.h"
extern int g_777ca0;
extern int g_776c90;
extern int g_775338;
extern int g_774654;
int __cdecl d2_TutorialAllowsFlag(int); void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00533a60(int, int, int*, int, int, int, int);
int __cdecl fcn_005c8400(void);
int __cdecl d2_CreateGebaeudeListPanel(void);
int __cdecl fcn_005c89a0(void);
int __cdecl d2_CreateRadioGroup(int, int, int, int);
void __cdecl d2_SelectRadioGroup(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005a5440(int, char*, int, int, int);
void __cdecl d2_SetGroupVisibility(int, int);
void __cdecl d2_ShowBuildingStatsDetail(int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_0046ed00(int, int, int);
int __cdecl d2_GetControlValue(int);
int __cdecl fcn_0050b750(int, char);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, unsigned short, int*);
void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_0050dc90(int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_ClearRadioGroup(int); void __cdecl fcn_00471e30(int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "client_packet_builder.h"
/* ADDRESS: GOLDTL 0x005c8c40 */
void __cdecl d2_OpenPlayerStats(void)
{
	int out[3];
	int idx;
	int ofs;
	int save;
	int firstWindow;
	int v3;
	int v4;
	int i;
	int n;
	int h;
	int cur;
	int obj;
	int q;
	int t1;
	int t2;
	int delta;
	int state;

	if (d2_TutorialAllowsFlag(0x800) == 0) {
		return;
	}
	fcn_0057e880(0x13, 0, 0, 0);
	save = fcn_00470820(0, 0, (char*) 0x6ac890);
	d2_CenterDialogWindows(save);
	d2_SetForm(save, 0);
	fcn_005340f0(*(int*) &d2_CurrentWindowId);
	d2_SetForm(save, 3);
	fcn_00533a60(*(int*) &d2_CurrentWindowId, 0, out, 3, *(int*) 0x14b5294, *(int*) 0x14b5298, *(int*) 0x14b529c);
	firstWindow = fcn_005c8400();
	v3 = d2_CreateGebaeudeListPanel();
	v4 = fcn_005c89a0();
	idx = d2_CreateRadioGroup(3, out[0], out[1], out[2]);
	ofs = idx * 0x8c;
	*(int*) (ofs + (unsigned long)&g_102cbc0) = *(int*) (ofs + (unsigned long)&g_102cbc0) | 1;
	d2_SelectRadioGroup(idx, *(int*) 0x77533c);
	if (v4 == -1) {
		fcn_00472640(out[2], 0);
	}
	for (;;) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		state = *(int*) (ofs + (unsigned long)&g_102cbc8);
		if (state == 0) {
			fcn_00471af0(firstWindow, 1);
			fcn_00471af0(v3, 0);
			fcn_00471af0(v4, 0);
		} else if (state == 1) {
			fcn_00471af0(v3, 1);
			fcn_00471af0(firstWindow, 0);
			fcn_00471af0(v4, 0);
		} else if (state == 2) {
			fcn_00471af0(v4, 1);
			fcn_00471af0(v3, 0);
			fcn_00471af0(firstWindow, 0);
		}
		if (firstWindow != -1) {
			d2_SetForm(firstWindow, 1);
			fcn_005a5440(*(int*) (0x7f4e18 + (*(unsigned short*) &g_774970) * 0x21c), (char*) 0x776aa0, firstWindow, 1, 0);
		}
		if (v3 != -1 && *(int*) &g_100f1dc != -1) {
			for (i = 0; i < g_775338; i++) {
				if (d2_CurrentElementId == *(int*) (0x778900 + i * 4)) {
					d2_SetGroupVisibility(save, 0);
					d2_ShowBuildingStatsDetail(*(int*) (&((D2_CONTROL_TL*) (*(int*) &g_1015ea0))[d2_CurrentElementId].associated_object));
					d2_SetGroupVisibility(save, 1);
					break;
				}
			}
		}
		if (v4 != -1) {
			d2_SetForm(v4, 0);
			if (*(int*) &g_100f1dc != -1) {
				t1 = fcn_00472830(v4, 3);
				t2 = fcn_00472830(v4, 2);
				if (d2_CurrentElementId == g_776c90) {
					fcn_0046ed00(0, 0x3e, t1);
					fcn_0046ed00(0, 0x3e, t2);
				} else if (d2_CurrentElementId == g_777ca0) {
					fcn_0046ed00(0, -0x3e, t1);
					fcn_0046ed00(0, -0x3e, t2);
				}
			}
			i = 0x777d14;
			while (i < 0x778914) {
				h = *(int*) (i - 0x10);
				if (h != -1) {
					cur = d2_GetControlValue(h);
					if (*(int*) (i - 4) != cur) {
						n = fcn_0050b750(d2_GetControlValue(*(int*) (i - 0x10)),
							g_773d75);
						obj = *(int*) i;
						cm_BeginPacketFieldDelta(obj, *(int*) (obj + 1));
						delta = *(unsigned short*) i - *(unsigned short*) &g_aed32c + 0x39;
						cm_AppendPacketFieldDelta(4, 1, (unsigned short) delta, &n);
						fcn_004c5360();
						q = fcn_0050dc90(*(int*) i);
						n = n - *(int*) (*(int*) i + 0x39);
						cm_BeginPacketFieldDelta(q, *(int*) (q + 4));
						cm_AppendPacketFieldValue(4, 1, (q - *(int*) &g_aed32c) + 0x1b8, &n);
						fcn_004c5360();
						*(int*) (i - 4) = d2_GetControlValue(*(int*) (i - 0x10));
					}
				}
				i += 0x18;
			}
		}
		if (main_RunFrameLoop((int) d2_OpenPlayerStats, 0x657c7) != 0) {
			continue;
		}
		*(int*) 0x77533c = *(int*) (ofs + (unsigned long)&g_102cbc8);
		d2_ClearRadioGroup(idx);
		fcn_00471e30(save);
		if (firstWindow != -1) {
			fcn_00471e30(firstWindow);
		}
		if (v3 != -1) {
			fcn_00471e30(v3);
		}
		if (v4 != -1) {
			fcn_00471e30(v4);
		}
		fcn_0057e880(0x13, 0, 1, 0);
		return;
	}
}
