#define MAX(a, b) ((a) > (b) ? (a) : (b))
extern volatile int gm_GameTicks;
extern unsigned int g_772f70;
extern int g_68bfcc;
void __cdecl d2_SetElementEnabled(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x14];
	int *ids;
	int count;
} Screen;
typedef struct {
	char pad0[0x20];
	int kind;
	char pad24[0x2d0];
} Obj2f4;
#include "Develop/client_types.h"
typedef List8c_102cbc8 List8c;

extern char g_772f74;
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern char* d2_CurrentWindow;
extern char* d2_Controls;
extern int d2_DialogButtonAction;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern List8c_102cbc8 d2_RadioGroupItems[];
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(char *);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_BringFormToFront(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLD 0x004e53e0 */
/* ADDRESS: GOLDTL 0x004e6e20 */
/* ADDRESS: GOLDDE 0x004d35c0 */
int __cdecl d2_UpdateProgressBar(int h, int total, int reset)
{
	int pct;
	int v;

	pct = 100;
	if (reset != 0) {
		g_772f70 = (*(unsigned int*)&gm_GameTicks);
		g_68bfcc = total;
		d2_SetElementEnabled(h, 0);
	} else {
		v = (int) ((1.0f - (float) ((*(unsigned int*)&gm_GameTicks) - g_772f70) / g_68bfcc) * 100.0f);
		pct = MAX(v, 0);
	}
	d2_SetElementValue(h, 0, 100, pct);
	return pct;
}

/* ADDRESS: GOLDTL 0x004e6eb0 */
/* ADDRESS: GOLDDE 0x004d3650 */
int __cdecl d2_ShowMessageBox(char *text, unsigned int flags)
{
	int mode;
	int result;
	unsigned int start;
	int id;
	int f80;
	int h;
	int me;
	int list;
	int i;
	int k;

	start = (*(unsigned int*)&gm_GameTicks);
	id = -1;
	result = 0;
	if (g_772f74 != 0) {
		return 0;
	}
	mode = main_LoopFlags & ~0x38;
	if (flags & 2) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_VERY_BIG");
	} else if (flags & 0x100) {
		h = d2_LoadForm(0, 0, "misc\\Messagebox_NONE_PERGA");
		d2_SetForm(h, 1);
	} else {
		h = d2_LoadForm(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		mode = 0x717c6;
	}
	io_AppendText(text);
	me = d2_CurrentWindowId;
	d2_CenterDialogWindows(h);
	g_772f74 = 1;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < ((Screen*)d2_CurrentWindow)->count; i++) {
		k = ((Screen*)d2_CurrentWindow)->ids[i];
#if defined(REBREW_GOLD)
		if (((Obj2f4*)d2_Controls)[k].kind != 0x40) {
#else
		if (((D2_CONTROL_TL*)d2_Controls)[k].kind != 0x40) {
#endif
			d2_AddToRadioGroup(list, k);
		}
	}
	d2_SelectRadioGroup(list, 0);
	d2_SetForm(h, 0);
	f80 = flags & 0x80;
	if (f80) {
		id = d2_AddWindowValueGauge(0x1c, ((Screen*)d2_CurrentWindow)->h - 0x18, ((Screen*)d2_CurrentWindow)->w - 0x40, 0, 500, 0x83, 0x42, d2_CurrentWindowId);
	}
	while (main_RunFrameLoop(d2_ShowMessageBox, mode) != 0) {
		d2_UpdateRadioGroup(list);
		if (flags & 0x40) {
			d2_BringFormToFront(h);
		}
		if (d2_DialogButtonAction == 2 && d2_HoveredWindow == me) {
			result = d2_RadioGroupItems[list].n + 1;
			d2_DialogCloseRequested = 1;
		} else if ((d2_DialogButtonAction == 1 && d2_HoveredWindow == me) || io_LastKeyScancode == 1) {
			result = 0;
			d2_DialogCloseRequested = 1;
		}
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
		if (f80 && id != -1) {
			d2_SetElementValue(id, 0, 500, (int) ((*(unsigned int*)&gm_GameTicks) - start));
		}
		if ((flags & 4) && (*(unsigned int*)&gm_GameTicks) > start + 500) {
			d2_DialogCloseRequested = 1;
		}
	}
	g_772f74 = 0;
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
