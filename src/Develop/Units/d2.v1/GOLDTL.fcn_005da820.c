
// SIZE 0x38
typedef struct Row {
	char* who;
	int id;
	char pad8[8];
	int x;
	int y;
	char pad18[0x14];
	int a;
	int shown;
	int b;
} Row;

// SIZE 0x3cc
struct s_1015f4c {
	int x;
	int y;
	char pad[0x3c4];
};

#include "client_types.h"

extern s_1015f4c g_1015f4c[];
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gs_CollectEvidenceIndicesForTarget(int id, int* ids, short kind);
int __cdecl gs_StartCourtTrial(char* e, char* who, int n, int a4);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl fcn_004f61c0(int* ids, int* b, int* c, short kind);
int __cdecl d2_BuildPersonStatusDesc(Row* r);
void __cdecl fcn_005ca740(int, int, int, int, Row*, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl d2_CreateRightAlignedText(char*, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_005d9f70(char* e, char* who);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl fcn_005da250(char*, char*);

/* ADDRESS: GOLDTL 0x005da820 */
int __cdecl fcn_005da820(char* e, char* request)
{
	int result;
	int count;
	int n;
	int dlg;
	char text[0x40];
	int b[32];
	int ids[32];
	int c[32];
	Row rows[32];
	char* who;
	int win;
	int i;
	int sel;

	result = 0x20;
	if (e[2] != 6 && e[2] != 7) {
		if (e[0x166] == 0xd) {
			return 0x60;
		}
		who = gm_LookupEntityRecordById(*(int*) (request + 0x214));
		if (who == 0 || who[0x166] == 0xd) {
			return 0x60;
		}
		b[0] = gs_CollectEvidenceIndicesForTarget(*(int*) (request + 0x214), ids, *(short*) e);
		if (b[0] == 0) {
			return 0x60;
		}
		return gs_StartCourtTrial(e, who, b[0], 1);
	}
	dlg = d2_LoadForm(0, 0, "privillegien\\Beweise_Sichten");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x173f);
	d2_SetForm(dlg, 2);
	win = d2_CurrentWindowId;
	d2_SetForm(dlg, 3);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, win, 0x767);
	n = fcn_004f61c0(ids, b, c, *(short*) e);
	for (i = 0, count = 0; i < n; i++) {
		who = gm_LookupEntityRecordById(ids[i]);
		if (who != 0) {
			rows[count].who = who;
			rows[count].a = c[i];
			rows[count].b = b[i];
			d2_BuildPersonStatusDesc(&rows[count]);
			rows[count].shown = 1;
			count++;
		}
	}
	d2_SetForm(dlg, 2);
	if (count != 0) {
		for (i = 0; i < count; i++) {
			io_FormatTextBuffer(text, "%i (%i) %s", rows[i].a, rows[i].b, (rows[i].a != 1) + 0x1748);
			rows[i].x = 0x32;
			rows[i].y = i * 0x69 + 10;
			fcn_005ca740(0x32, i * 0x69 + 10, d2_CurrentWindowId, 0x56, &rows[i], 1);
			d2_CreateRightAlignedText(text, ((struct s_1015f4c*) g_1015f4c)[d2_CurrentWindowId].x - 0xf, i * 0x69 + 10 + 0x2d, 0xc8, 0x55);
		}
	} else {
		io_AppendText(0x1741, g_774970);
	}
	d2_SetOverlayAnimation(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < count; i++) {
				if (d2_CurrentElementId == rows[i].id) {
					sel = i;
					break;
				}
			}
			if (sel > -1) {
				result = fcn_005d9f70(e, rows[sel].who);
			}
		}
	} while (main_RunFrameLoop(fcn_005da250, 0x657c7));
	d2_DestroyForm(dlg);
	return result;
}
