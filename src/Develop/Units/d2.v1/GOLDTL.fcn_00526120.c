typedef struct Ctl {
	char pad0[0x20];
	int f20;
	char pad24[0x2d0];
} Ctl;
// SIZE 0x2f4

typedef struct Screen {
	char pad0[0xc];
	int xc;
	int x10;
	char pad14[0x14];
	int* ids;
	int count;
} Screen;
// SIZE 0x30

extern volatile int g_6b7fac;
extern char g_77470c;
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern List8c_102cbc8 g_102cbc8[];
extern char g_14cf950;
#include "client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_BringFormToFront(int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);


/* Modal message box: flags pick the layout (2, 0x10, 0x20, 0x100), 8 the
 * wait value, 0x80 a progress bar, 4 closes after 0x1f4 ticks of g_6b7fac,
 * 0x40 calls fcn_004707d0 each frame.
 * Returns the chosen entry + 1, or 0. */
/* ADDRESS: GOLDTL 0x00526120 */
int __cdecl fcn_00526120(char* text, int flags)
{
	int wait;
	int result;
	unsigned int start;
	int timer;
	int bar;
	int dlg;
	int list;
	int screen;
	int i;
	int id;

	start = (*(unsigned int*)&g_6b7fac);
	timer = -1;
	result = 0;
	if (g_77470c != 0) {
		return 0;
	}
	wait = main_LoopFlags & ~0x38;
	if (flags & 2) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_VERY_BIG");
	} else if (flags & 0x100) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_NONE_PERGA");
		d2_SetForm(dlg, 1);
	} else {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		wait = 0x717c6;
	}
	io_AppendText(text);
	screen = d2_CurrentWindowId;
	d2_CenterDialogWindows(dlg);
	g_77470c = 1;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < ((Screen*)g_77255c)->count; i++) {
		id = ((Screen*)g_77255c)->ids[i];
		if (((D2_CONTROL_TL*) g_1015ea0)[id].kind != 0x40) {
			d2_AddToRadioGroup(list, id);
		}
	}
	d2_SelectRadioGroup(list, 0);
	d2_SetForm(dlg, 0);
	bar = flags & 0x80;
	if (bar) {
		timer = d2_AddWindowValueGauge(0x1c, ((Screen*)g_77255c)->x10 - 0x18, ((Screen*)g_77255c)->xc - 0x40, 0, 0x1f4, 0x83, 0x42, d2_CurrentWindowId);
	}
	while (main_RunFrameLoop((void*) fcn_00526120, wait) != 0) {
		d2_UpdateRadioGroup(list);
		if (flags & 0x40) {
			d2_BringFormToFront(dlg);
		}
		if (g_100f1dc == 2 && d2_HoveredWindow == screen) {
			result = ((int*)g_102cbc8)[list * 35] + 1;
			g_774654 = 1;
		} else if ((g_100f1dc == 1 && d2_HoveredWindow == screen) || g_14cf950 == 1) {
			result = 0;
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (bar && timer != -1) {
			d2_SetElementValue(timer, 0, 0x1f4, (int) ((*(unsigned int*)&g_6b7fac) - start));
		}
		if ((flags & 4) && (*(unsigned int*)&g_6b7fac) > start + 0x1f4) {
			g_774654 = 1;
		}
	}
	g_77470c = 0;
	d2_ClearRadioGroup(list);
	d2_DestroyForm(dlg);
	return result;
}
