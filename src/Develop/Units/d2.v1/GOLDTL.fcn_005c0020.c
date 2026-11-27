
#include <stdio.h>

extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern char g_7f4ca0[];

typedef struct {
	int x0;
	int x4;
	char pad8[8];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	int x30;
	int x34;
} Rec38;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
int __cdecl fcn_004f61c0(int*, int*, int*, unsigned short);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl d2_BuildPersonStatusDesc(Rec38*);
int __cdecl fcn_005ca740(int, int, int, int, Rec38*, int);
void __cdecl d2_CreateRightAlignedText(char*, int, int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl d2_ShowBeweiseDetails(char*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x005c0020 */
void __cdecl fcn_005c0020(void)
{
	int ids[32];
	int v11[32];
	int v10[32];
	Rec38 recs[32];
	char buf[64];
	char* ent;
	char* p;
	Rec38* rec;
	int dlg;
	int i;
	int n;
	int count;
	int selected;
	int sum;
	int y;
	int h2;

	ent = (char*) 0x7f4ca0 + g_774970 * 0x21c;
	dlg = d2_LoadForm(0, 0, (char*) 0x6ac4f4);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x173f);
	d2_SetForm(dlg, 2);
	h2 = d2_CurrentWindowId;
	d2_SetForm(dlg, 3);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, h2, 0x767);
	n = fcn_004f61c0(ids, v11, v10, *(unsigned short*) ent);
	count = 0;
	for (i = 0; i < n; i++) {
		p = gm_LookupEntityRecordById(ids[i]);
		if (p != 0) {

			recs[count].x0 = (int) p;
			recs[count].x2c = v10[i];
			recs[count].x34 = v11[i];
			d2_BuildPersonStatusDesc(&recs[count]);
			recs[count].x30 = 1;
			count++;
		}
	}
	d2_SetForm(dlg, 2);
	if (count != 0) {


		for (i = 0; i < count; i++) {
			rec = &recs[i];
			y = 10 + i * 0x69;
			sprintf(buf, (char*) 0x6ac4e8, rec->x2c, rec->x34,
			    (rec->x2c != 1) + 0x1748);
			rec->x10 = 0x32;
			rec->x14 = y;
			fcn_005ca740(0x32, y, d2_CurrentWindowId, 0x56, rec, 1);
			d2_CreateRightAlignedText(buf,
			    *(int*) (0x1015f4c + d2_CurrentWindowId * 0x3cc) - 0xf,
			    y + 0x2d, 200, 0x55);

		}

	}
	else {
		io_AppendText(0x1741, g_774970);
	}
	d2_SetOverlayAnimation(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			selected = -1;
			for (i = 0; i < count; i++) {
				if (d2_CurrentElementId == recs[i].x4) { selected = i; break; }
			}
			if (selected > -1)
				d2_ShowBeweiseDetails((char*) 0x7f4ca0 + g_774970 * 0x21c,
				    recs[selected].x0);
		}
	} while (main_RunFrameLoop((void*) fcn_005c0020, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
