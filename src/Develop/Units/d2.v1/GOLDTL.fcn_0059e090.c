

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

#include "client_types.h"

extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int d2_CurrentWindowId;
extern int g_14a566c;
extern volatile int g_6b7fac;
extern Win_1015f40 g_1015f40[0x60];
extern D2_FORM_RECORD g_1038140[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern char g_868060[];
extern int g_100f1dc;
extern int d2_CurrentElementId;

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d2_SetBackgroundTexture(char*, int);
void __cdecl fcn_00533a60(int, int, Pick*, int, int, char*, char*);
void __cdecl d2_SetSlotVisibility(int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00594340(void);
void __cdecl d2_SyncProduktionSlotGrid(char*, int);
void __cdecl fcn_00597940(int, int, int, char*, int);

/* Transport dialog: shows the export/import pick for building b and
 * redraws whenever the direction changes. */
void __cdecl fcn_0059e090(char* b)
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
	while (main_RunFrameLoop(fcn_0059e090, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (sel != shown) {
			if (h != -1) {
				d2_DestroyForm(h);
			}
			h = fcn_00470820(0, 0, "Handel\\Handel_Transport");
			d2_CenterDialogWindows(h);
			d2_SetForm(h, 0);
			d2_DrawPanelFrame(d2_CurrentWindowId, 0x70b, 0x73f);
			slot = (D2_WIN*) &g_1015f40[((Dlg*)g_1038140)[h].slot];
			fcn_0064d41a(buf, "ief_Wappen%li", *(int*) (b + 0x65));
			d2_SetBackgroundTexture(buf, slot->pad0);
			slot->alpha = 0.0f;
			t0 = *(unsigned int*)&g_6b7fac;
			d2_SetForm(h, 4);
			fcn_00533a60(d2_CurrentWindowId, 0, &pick, 3, g_14a566c, "Import", "Export");
			d2_SetSlotVisibility(pick.x0, 0);
			a = pick.a;
			c = pick.b;
			if (sel != 0) {
				grp = fcn_00502cd0(*(int*) (b + 0x5d), 2, 0, 0x1db, 6);
				if (grp == 0) {
					return;
				}
				d2_SetForm(h, 3);
				io_AppendText(0x1c47, g_868060 + *(int*) (b + 0x65) * 0x2f4);
			}
			else {
				grp = fcn_00502cd0(*(int*) (b + 0x5d), 2, 0, 0x1dc, 6);
				if (grp == 0) {
					return;
				}
				d2_SetForm(h, 3);
				io_AppendText(0x1c48, g_868060 + *(int*) (b + 0x65) * 0x2f4);
			}
			((D2_CONTROL_TL*)g_1015ea0)[a].disabled = sel;
			((D2_CONTROL_TL*)g_1015ea0)[a].value_060 = sel;
			((D2_CONTROL_TL*)g_1015ea0)[c].disabled = sel == 0;
			((D2_CONTROL_TL*)g_1015ea0)[c].value_060 = sel == 0;
			fcn_00594340();
			shown = sel;
		}
		d = (*(unsigned int*)&g_6b7fac - t0) * 0.0013333333333333333;
		if (!(d < 0.25)) {
			d = 0.25;
		}
		slot->alpha = (float) d;
		d2_SyncProduktionSlotGrid(b, grp);
		fcn_00597940(h, 1, 0, b, grp);
		if (g_100f1dc == 2) {
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
