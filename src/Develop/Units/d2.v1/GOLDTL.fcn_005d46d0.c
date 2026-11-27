

#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0x24
typedef struct {
	unsigned short id;
	char pad2[0x1a];
	float f1c;
	int f20;
} Entry;

// SIZE 0x21c
typedef struct {
	char pad0[0x54];
	int f54;
	char pad58[0x1c4];
} House;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int shown;
	char pad60[0x170];
	int style;
	char pad1d4[0x11c];
	House* house;
} Slot;

extern char g_7f4ca0[];
extern char* g_1015ea0;
extern char s_6acc18[];
extern char s_6acc08[];
extern char s_6a9680[];
extern char s_67d444[];
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"

void __cdecl gm_RankPlayers(int*, Entry*);
int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_ShowCenteredText(char*, int, int, int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_RunPlayerRankingDialog(void)
{
	int count;
	int dlg;
	int cols[8];
	char text[0x100];
	Entry list[8];
	int i;
	int fl;
	int h;
	int v;

	cols[0] = 0x8f;
	cols[1] = 0x95;
	cols[2] = 0x9b;
	cols[3] = 0xa1;
	cols[4] = 0xa7;
	cols[5] = 0xad;
	cols[6] = 0xb3;
	cols[7] = 0xb9;
	gm_RankPlayers(&count, list);
	if (count == 0) {
		return;
	}
	if (!d2_TutorialAllowsFlag(4)) {
		return;
	}
	fcn_0057e880(10, 0, 0, 0);
	if (count <= 6) {
		dlg = d2_LoadForm(0, 0, s_6acc18);
	} else {
		dlg = d2_LoadForm(0, 0, s_6acc08);
	}
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f35);
	d2_SetForm(dlg, 2);
	for (i = 0; i < count; i++) {
		fl = (int) (list[i].f1c * 100.0f);
		h = d2_AddElementToWindow(0x28, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2),
			((House*)g_7f4ca0)[list[i].id].f54, d2_CurrentWindowId);
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_05c) = 1;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[h].flags_1d0) = 3;
		(*(House**)&((D2_CONTROL_TL*)g_1015ea0)[h].associated_object) = &((House*)g_7f4ca0)[list[i].id];
		sprintf(text, s_6a9680, list[i].id);
		d2_ShowCenteredText(text, 0x36, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 0x22, 0x12c, 0x56);
		v = MIN(MAX(((House*)g_7f4ca0)[list[i].id].f54 - 0x59a, 0), 7);
		h = d2_AddWindowValueGauge(0x5a, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 7, 0x12c, 0, 0x64,
			cols[v], 0x42, d2_CurrentWindowId);
		d2_SetElementValue(h, 0, 0x64, fl);
		sprintf(text, s_67d444, list[i].f20);
		d2_ShowCenteredText(text, 0x1f4, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2), 0xc8, 0x55);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunPlayerRankingDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	fcn_0057e880(10, 0, 1, 0);
}
