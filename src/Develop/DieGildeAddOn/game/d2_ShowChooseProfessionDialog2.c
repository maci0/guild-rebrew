#include "client_types.h"


// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x26];
	char b36;
	char pad37[0x21];
	int f58;
	char b5c;
	char pad5d[3];
	int f60;
	char pad64[0x94];
};

typedef struct Ent {
	unsigned short id;
	short pad2;
	int handle;
} Ent;

typedef struct Req {
	unsigned short id;
	short pad2;
	int handle;
	char pad8;
	unsigned char female;
} Req;

#include "Develop/Units/d2.v1/d2_window_view.h"





// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x5c];
	int shown;
	char pad60[0xcc - 0x60];
	char text[0x100];
	int color;
	int style;
	char pad1d4[0x2f4 - 0x1d4];
} Slot;
// SIZE 0x2f4

typedef struct Font {
	char pad0[0x1d978];
	short w;
} Font;


#include "Develop/Units/d2.v1/d2_gui.h"
extern char* g_772500;
extern int d2_CurrentWindowId;
extern char* g_14a5adc[15];
extern int main_LoopFlags;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ce8d8;
#include "client_dialog_state.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
int __cdecl main_RunFrameLoop(void*, int);
char __cdecl gm_GetRangeStatId(int, int);
void __cdecl cm_SendCopyEntityData(struct msg*);
void __cdecl d2_DestroyForm(int);

int __cdecl d2_ShowChooseProfessionDialog2(Ent* e, Req* p)
{
	int colw;
	int n;
	int dlg;
	int rowh;
	struct msg m;
	int x0;
	int id;
	char* d;
	char* s;
	int result;
	char c;
	int i;

	n = (int)(gm_WalkEntityChain(e->id) * 0.015f);
	dlg = d2_LoadForm(0, 0, "privillegien\\CHOOSEPROFESSION2");
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	colw = (((D2_WIN*) g_1015f40)[d2_CurrentWindowId].width - 0x40) / 5;
	rowh = (((D2_WIN*) g_1015f40)[d2_CurrentWindowId].height - 0x84) / 3;
	x0 = (colw - ((Font*) g_772500)->w) / 2;
	io_AppendText(0x1a9a, (p->female != 0) + 0x1aa0, p->id, n);
	for (i = 1; i <= 15; i++) {
		id = d2_AddElementToWindow((i - 1) % 5 * colw + x0 + 0x20, (i - 1) / 5 * rowh + x0 + 0x64, i - 1 + 0x5a2, d2_CurrentWindowId);
		((D2_CONTROL_TL*)g_1015ea0)[id].value_05c = 1;
		((D2_CONTROL_TL*)g_1015ea0)[id].flags_1d0 = 3;
		s = g_14a5adc[i - 1];
		d = ((char*)&((D2_CONTROL_TL*)g_1015ea0)[id] + 0xcc);
		do {
			c = *s++;
			*d++ = c;
		} while (c != 0);
		((D2_CONTROL_TL*)g_1015ea0)[id].value_1cc = 0x56;
	}
	result = 0;
	while (main_RunFrameLoop(d2_ShowChooseProfessionDialog2, main_LoopFlags) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_14ce8d8 != 0) {
			result = 1;
			for (i = 0; i <= 15; i++) {
				if (g_100f1dc == i + 0x5a2) {
					m.b36 = 0x12;
					m.b4 = 0x5e;
					m.f58 = e->handle;
					m.f8 = p->handle;
					m.fc = -1;
					m.b5c = gm_GetRangeStatId(i + 1, result);
					m.f60 = n;
					cm_SendCopyEntityData(&m);
					g_774654 = result;
					break;
				}
			}
		}
	}
	d2_DestroyForm(dlg);
	return result;
}
