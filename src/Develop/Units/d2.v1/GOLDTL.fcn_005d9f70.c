#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int pad[3];
	int count;
	int pad2[5];
} Stat5d9f;

typedef struct {
	int name;
	int pad[4];
} Kind5d9f;

#include "client_types.h"
extern Rec2d_9a3800 g_9a3800[512];
#include "GOLDTL.fcn_005d9f70_gconf.h"
extern char g_6ac4c8[];
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentElementId;

int __cdecl gs_CollectEvidenceIndicesForTarget(int, int*, unsigned short);
void __cdecl d2_SortCrimeRecordsByKind(int n, Rec2d_9a3800* arr);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005c91c0(int, int, int, int, int);
int __cdecl gm_GetLawEntry(int, Stat5d9f*);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
int __cdecl gm_CheckPrivilege(int, unsigned short*, int*);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_SetElementEnabled(int, int);
int __cdecl gs_StartCourtTrial(unsigned short*, unsigned short*, int, int);

/* ADDRESS: GOLDTL 0x005d9f70 */
int __cdecl fcn_005d9f70(unsigned short* entity, unsigned short* other)
{
	int flag;
	int sel;
	int n;
	int dlg;
	Stat5d9f st;
	int list[32];
	int q[0x88];
	Rec2d_9a3800 rows[32];
	int i;
	int k;
	int w;

	flag = 0;
	sel = -1;
	if (*other == 0xffff) {
		return 0;
	}
	n = gs_CollectEvidenceIndicesForTarget(*(int*) (other + 2), list, *entity);
	if (n < 1) {
		return 0x60;
	}
	for (i = 0; i < n; i++) {
		rows[i] = g_9a3800[list[i]];
		flag |= (rows[i].x25 == 1);
	}
	if (entity == other) {
		flag = 0;
	}
	d2_SortCrimeRecordsByKind(n, rows);
	dlg = fcn_00470820(0, 0, g_6ac4c8);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 2);
	w = d2_CurrentWindowId;
	d2_SetForm(dlg, 4);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, w, 0x767);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1742, *other);
	d2_SetForm(dlg, 2);
	for (k = 0; k < n; k++) {
		fcn_005c91c0(g_14aa314[rows[k].x1c].name, 10, k * 0x28 + 10, 0x13b, 0x55);
		if (gm_GetLawEntry(rows[k].x1c, &st) != 0 && st.count != 0) {
			for (i = 0; i < st.count; i++) {
				d2_AddElementToWindow(i * 0x10 + 0x154, k * 0x28 + 10, 0x526, d2_CurrentWindowId);
			}
		}
	}
	memset(q, 0, sizeof(q));
	q[0] = 1;
	d2_SetForm(dlg, 3);
	if (gm_CheckPrivilege(0x16, other, q) & 2) {
		io_AppendText(0x174a);
	} else {
		sel = d2_GetWindowListItem(dlg, 3, io_AppendText(0x1745));
		if (flag == 0) {
			d2_SetElementEnabled(sel, 0);
		}
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == sel) {
				gs_StartCourtTrial(entity, other, n, 0);
				g_774654 = 3;
			}
		}
	} while (main_RunFrameLoop(fcn_005d9f70, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	return 0;
}
