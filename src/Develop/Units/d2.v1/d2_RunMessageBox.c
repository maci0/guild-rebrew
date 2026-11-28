typedef struct Ctl {
	char pad0[0x20];
	int f20;
	char pad24[0x2d0];
} Ctl;
/* SIZE 0x2f4 */

typedef struct Screen {
	char pad0[0xc];
	int xc;
	int x10;
	char pad14[0x14];
	int* ids;
	int count;
} Screen;
/* SIZE 0x30 */

extern volatile int gm_GameTicks;
extern char g_77470e;
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern Screen* d2_CurrentWindow;
extern char* d2_Controls;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_BringFormToFront(int);
void __cdecl d2_SetElementValue(int, int, int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

/* Modal message box: flags pick the layout (2, 0x10, 0x20), 8 the wait
 * value, 0x80 a progress bar, 4 closes after 0x1f4 ticks of g_6b7fac,
 * 0x40 calls fcn_004707d0 each frame. Returns the 1/0 close code. */
/* ADDRESS: GOLDTL 0x00526660 */
/* ADDRESS: GOLDDE 0x0050f920 */
int __cdecl d2_RunMessageBox(int parent, int flags)
{
	int style;
	int n;
	int h;
	unsigned int saved;
	int dlg;
	int list;
	int i;
	int id;

	saved = gm_GameTicks;
	h = -1;
	n = 0;
	if (g_77470e != 0) {
		return 0;
	}
	style = main_LoopFlags & ~0x38;
	if (flags & 2) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox_VERY_BIG");
	} else {
		dlg = d2_LoadForm(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		style = 0x717c6;
	}
	io_AppendText(parent);
	d2_CenterDialogWindows(dlg);
	g_77470e = 1;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < d2_CurrentWindow->count; i++) {
		id = d2_CurrentWindow->ids[i];
		if (*(int*) (d2_Controls + id * 756 + 0x20) != 0x40) {
			d2_AddToRadioGroup(list, id);
		}
	}
	d2_SelectRadioGroup(list, 0);
	d2_SetForm(dlg, 0);
	if (flags & 0x80) {
		h = d2_AddWindowValueGauge(0x1c, d2_CurrentWindow->x10 - 0x20, d2_CurrentWindow->xc - 0x40, 0, 0x1f4, 0x83, 0x42, d2_CurrentWindowId);
	}
	while (main_RunFrameLoop((void*) d2_RunMessageBox, style) != 0) {
		d2_UpdateRadioGroup(list);
		if (flags & 0x40) {
			d2_BringFormToFront(dlg);
		}
		if (d2_DialogButtonAction != 2) {
			if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
				n = 0;
			}
		} else {
			d2_DialogCloseRequested = 1;
			n = 1;
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if ((flags & 0x80) && h != -1) {
			d2_SetElementValue(h, 0, 0x1f4, gm_GameTicks - saved);
		}
		if (flags & 4) {
			if ((unsigned int) gm_GameTicks > saved + 0x1f4u) {
				d2_DialogCloseRequested = 1;
			}
		}
	}
	g_77470e = 0;
	d2_ClearRadioGroup(list);
	d2_DestroyForm(dlg);
	return n;
}
