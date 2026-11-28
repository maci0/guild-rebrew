

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

// SIZE 0x2ec
typedef struct {
	char pad0[0x4c];
	int shown;
	char pad50[0x170];
	int style;
	char pad1c4[0x124];
	House* house;
} Slot;

extern char gm_EntitySlotTable[];
extern char* g_f8f080;
extern char s_6acc18[];
extern char s_6acc08[];
extern char s_6a9680[];
extern char s_67d444[];
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"

void __cdecl gm_RankPlayers(int*, Entry*);
int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
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

void __cdecl d2_RunCompareDialog(void)
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
	d2_DispatchTutorialInput(10, 0, 0, 0);
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
			((House*)gm_EntitySlotTable)[list[i].id].f54, d2_CurrentWindowId);
		((Slot*)g_f8f080)[h].shown = 1;
		((Slot*)g_f8f080)[h].style = 3;
		((Slot*)g_f8f080)[h].house = &((House*)gm_EntitySlotTable)[list[i].id];
		sprintf(text, s_6a9680, list[i].id);
		d2_ShowCenteredText(text, 0x36, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 0x22, 0x12c, 0x56);
		v = MIN(MAX(((House*)gm_EntitySlotTable)[list[i].id].f54 - 0x59a, 0), 7);
		h = d2_AddWindowValueGauge(0x5a, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 7, 0x12c, 0, 0x64,
			cols[v], 0x42, d2_CurrentWindowId);
		d2_SetElementValue(h, 0, 0x64, fl);
		sprintf(text, s_67d444, list[i].f20);
		d2_ShowCenteredText(text, 0x1f4, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2), 0xc8, 0x55);
	}
	d2_DialogButtonAction = -1;
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop((void*) d2_RunCompareDialog, 0x657c7) != 0);
	d2_DestroyForm(dlg);
	d2_DispatchTutorialInput(10, 0, 1, 0);
}
