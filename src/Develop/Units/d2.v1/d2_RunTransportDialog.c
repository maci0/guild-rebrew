

#include "Develop/Units/d2.v1/d2_win.h"






// SIZE 0x3cc

typedef struct {
	char pad0[0xc];
	int slot;
	char pad10[0x2ac];
} Dlg;
// SIZE 0x2bc

typedef struct {
	char pad0[0x4c];
	int x4c;
	char pad50[0x10];
	int x60;
	char pad64[0x290];
} City;
// SIZE 0x2f4

typedef struct {
	int x0;
	int a;
	int b;
	char padc[0x14];
} Pick;
// SIZE 0x20

#include "Develop/client_types.h"

extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int d2_CurrentWindowId;
extern int g_14a566c;
extern volatile int gm_GameTicks;
extern Win_1015f40 d2_Windows[0x60];
extern D2_FORM_RECORD d2_Forms[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern char gm_TownTable[];
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d2_SetBackgroundTexture(char*, int);
void __cdecl d2_CreateButtonRow(int, int, Pick*, int, int, char*, char*);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ResetBuildingUiSlots(void);
void __cdecl d2_SyncProduktionSlotGrid(char*, int);
void __cdecl d2_DrawProduktionSlotGrid(int, int, int, char*, int);

/* Transport dialog: shows the export/import pick for building b and
 * redraws whenever the direction changes. */
void __cdecl d2_RunTransportDialog(char* b)
{
	int grp;
	int a;
	int c;
	int shown;
	int t0;
	int h;
	int sel;
	double d;
	D2_WIN* slot;
	Pick pick;
	char buf[0x104];

	slot = 0;
	a = 0;
	c = 0;
	t0 = 0;
	grp = 0;
	if (b[0] != 'G') {
		return;
	}
	h = -1;
	sel = 1;
	shown = -1;
	while (main_RunFrameLoop(d2_RunTransportDialog, 0x677c7) != 0) {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (sel != shown) {
			if (h != -1) {
				d2_DestroyForm(h);
			}
			h = d2_LoadForm(0, 0, "Handel\\Handel_Transport");
			d2_CenterDialogWindows(h);
			d2_SetForm(h, 0);
			d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x73f);
			slot = (D2_WIN*) &d2_Windows[((Dlg*)d2_Forms)[h].slot];
			fcn_0064d41a(buf, "ief_Wappen%li", *(int*) (b + 0x65));
			d2_SetBackgroundTexture(buf, slot->pad0);
			slot->alpha = 0.0f;
			t0 = *(unsigned int*)&gm_GameTicks;
			d2_SetForm(h, 4);
			d2_CreateButtonRow(d2_CurrentWindowId, 0, &pick, 3, g_14a566c, "Import", "Export");
			d2_SetSlotVisibility(pick.x0, 0);
			a = pick.a;
			c = pick.b;
			if (sel != 0) {
				grp = gm_QueryEntities(*(int*) (b + 0x5d), 2, 0, 0x1db, 6);
				if (grp == 0) {
					return;
				}
				d2_SetForm(h, 3);
				io_AppendText(0x1c47, gm_TownTable + *(int*) (b + 0x65) * 0x2f4);
			}
			else {
				grp = gm_QueryEntities(*(int*) (b + 0x5d), 2, 0, 0x1dc, 6);
				if (grp == 0) {
					return;
				}
				d2_SetForm(h, 3);
				io_AppendText(0x1c48, gm_TownTable + *(int*) (b + 0x65) * 0x2f4);
			}
			((D2_CONTROL_TL*)d2_Controls)[a].disabled = sel;
			((D2_CONTROL_TL*)d2_Controls)[a].value_060 = sel;
			((D2_CONTROL_TL*)d2_Controls)[c].disabled = sel == 0;
			((D2_CONTROL_TL*)d2_Controls)[c].value_060 = sel == 0;
			d2_ResetBuildingUiSlots();
			shown = sel;
		}
		d = (*(unsigned int*)&gm_GameTicks - t0) * 0.0013333333333333333;
		if (!(d < 0.25)) {
			d = 0.25;
		}
		slot->alpha = (float) d;
		d2_SyncProduktionSlotGrid(b, grp);
		d2_DrawProduktionSlotGrid(h, 1, 0, b, grp);
		if (d2_DialogButtonAction == 2) {
			if (d2_CurrentElementId == a) {
				sel = 1;
			}
			else if (d2_CurrentElementId == c) {
				sel = 0;
			}
		}
	}
	if (h != -1) {
		d2_DestroyForm(h);
	}
}
