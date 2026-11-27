

typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x14];
	int *ids;
	int count;
} Screen;
// SIZE 0x30

typedef struct {
	char pad0[0x20];
	int kind;
	char pad24[0x2d0];
} Obj2f4;
// SIZE 0x2f4

#include "client_types.h"
typedef List8c_102cbc8 List8c;
// SIZE 0x8c

extern volatile int g_6b7fac;
extern char g_77470d;
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern List8c_102cbc8 g_102cbc8[];
extern char g_14cf950;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl d2_LoadForm(int, int, char *);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl io_AppendText(char *);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl d2_AddToRadioGroup(int, int);
void __cdecl d2_SelectRadioGroup(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl main_RunFrameLoop(void *, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_BringFormToFront(int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ShowGreenMessageBox(char *title, char *text, unsigned int flags)
{
	int mode;
	int h;
	int result;
	unsigned int start;
	int id;
	int f80;
	int list;
	int i;
	int k;

	start = (*(unsigned int*)&g_6b7fac);
	id = -1;
	result = 0;
	if (g_77470d != 0) {
		return 0;
	}
	mode = main_LoopFlags & ~0x38;
	h = d2_LoadForm(0, 0, "misc\\MessageBoxGreen");
	if (flags & 8) {
		mode = 0x717c6;
	}
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(h, 1);
	if (title != 0) {
		io_AppendText(title);
	}
	d2_SetForm(h, 2);
	io_AppendText(text);
	d2_CenterDialogWindows(h);
	g_77470d = 1;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < ((Screen*)g_77255c)->count; i++) {
		k = ((Screen*)g_77255c)->ids[i];
		if (((D2_CONTROL_TL*)g_1015ea0)[k].kind != 0x40) {
			d2_AddToRadioGroup(list, k);
		}
	}
	d2_SelectRadioGroup(list, 0);
	d2_SetForm(h, 0);
	f80 = flags & 0x80;
	if (f80) {
		id = d2_AddWindowValueGauge(0x1c, ((Screen*)g_77255c)->h - 0x18, ((Screen*)g_77255c)->w - 0x40, 0, 500, 0x83, 0x42, d2_CurrentWindowId);
	}
	while (main_RunFrameLoop(d2_ShowGreenMessageBox, mode) != 0) {
		d2_UpdateRadioGroup(list);
		if (flags & 0x40) {
			d2_BringFormToFront(h);
		}
		if (g_100f1dc != 2) {
			if (g_100f1dc == 1 || g_14cf950 == 1) {
				g_774654 = 1;
				result = 0;
			}
		} else {
			g_774654 = 1;
			result = g_102cbc8[list].n + 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (f80 && id != -1) {
			d2_SetElementValue(id, 0, 500, (int) ((*(unsigned int*)&g_6b7fac) - start));
		}
		if ((flags & 4) && (*(unsigned int*)&g_6b7fac) > start + 500) {
			g_774654 = 1;
		}
	}
	g_77470d = 0;
	d2_ClearRadioGroup(list);
	d2_DestroyForm(h);
	return result;
}
