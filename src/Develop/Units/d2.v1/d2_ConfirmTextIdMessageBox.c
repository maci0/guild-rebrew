

typedef struct IdList {
	char pad0[0x28];
	int* ids;
	int count;
} IdList;

typedef struct Obj2f4 {
	char pad0[0x20];
	int kind;
	char pad24[0x2f4 - 0x24];
} Obj2f4;
// SIZE 0x2f4

extern volatile int gm_GameTicks;
extern char g_77534d;
extern int main_LoopFlags;
extern char* d2_CurrentWindow;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_68d760[];
extern char s_68d74c[];
extern char s_68d730[];
extern char s_68d714[];
extern char s_68d704[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_CreateRadioGroup(int);
void __cdecl d2_AddToRadioGroup(int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateRadioGroup(int);
void __cdecl d2_BringFormToFront(int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDDE 0x005c1410 */
int __cdecl d2_ConfirmTextIdMessageBox(int arg, unsigned int flags)
{
	int h;
	int wflags;
	int result;
	int start;
	int ctx;
	int i;
	int id;

	start = gm_GameTicks;
	result = 0;
	if (g_77534d) {
		return 0;
	}
	wflags = main_LoopFlags & ~0x38;
	if (flags & 2) {
		h = d2_LoadForm(0, 0, s_68d760);
	} else if (flags & 0x10) {
		h = d2_LoadForm(0, 0, s_68d74c);
	} else if (flags & 0x20) {
		h = d2_LoadForm(0, 0, s_68d730);
	} else if (flags & 0x100) {
		h = d2_LoadForm(0, 0, s_68d714);
		d2_SetForm(h, 1);
	} else {
		h = d2_LoadForm(0, 0, s_68d704);
	}
	if (flags & 8) {
		wflags = 0x717c6;
	}
	io_AppendText(arg);
	d2_CenterDialogWindows(h);
	g_77534d = 1;
	ctx = d2_CreateRadioGroup(0);
	for (i = 0; i < ((IdList*)d2_CurrentWindow)->count; i++) {
		id = ((IdList*)d2_CurrentWindow)->ids[i];
		if (((D2_CONTROL_TL*)d2_Controls)[id].kind != 0x40) {
			d2_AddToRadioGroup(ctx, id);
		}
	}
	while (main_RunFrameLoop(d2_ConfirmTextIdMessageBox, wflags)) {
		d2_UpdateRadioGroup(ctx);
		if (flags & 0x40) {
			d2_BringFormToFront(h);
		}
		if (d2_DialogButtonAction != 2) {
			if (d2_DialogButtonAction == 1) {
				d2_DialogCloseRequested = 1;
				result = 0;
			}
		} else {
			d2_DialogCloseRequested = 1;
			result = 1;
		}
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		}
		if ((flags & 4) && (unsigned int) gm_GameTicks > (unsigned int) (start + 500)) {
			d2_DialogCloseRequested = 1;
		}
	}
	g_77534d = 0;
	d2_ClearRadioGroup(ctx);
	d2_DestroyForm(h);
	return result;
}

