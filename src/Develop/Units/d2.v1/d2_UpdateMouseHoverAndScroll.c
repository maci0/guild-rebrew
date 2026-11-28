

typedef struct Win {
	int id;
	char pad4[0x14 - 4];
	int style;
	char pad18[0x260 - 0x18];
	int scroll;
	char pad264[0x270 - 0x264];
	unsigned char scroll_max;
	char pad271[3];
	int step;
	char pad278[0x28c - 0x278];
	int tip;
	int tip_on;
	char pad294[0x3b8 - 0x294];
	int down_btn;
	int up_btn;
	char pad3c0[0x3cc - 0x3c0];
} Win;
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x1f0];
	int win;
	char pad1f4[0x2f4 - 0x1f4];
} Slot;
// SIZE 0x2f4

extern int g_100f890;
extern int g_100f944;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d8e0;
extern int g_67d8e4;
extern volatile int g_6b7fb0;
extern int g_100f888;
extern int g_100f1c8;
extern int g_7725d8;
extern int g_100f1c0;
extern int g_100f1c4;
#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int tp_d2_SelectedControl;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_67d38c;
extern int g_14ce900;
extern int g_14ce904;

void __cdecl io_ClearInputButtonFlags(unsigned char mask);
char* __cdecl d2_SelectFont(int idx);
void __cdecl d2_ScrollWindow(int delta, int step, int k);

void __cdecl d2_UpdateMouseHoverAndScroll(void)
{
	int sel;
	int btn;
	Win* w;
	int d;
	int i;

	btn = g_14ce8e8;
	sel = -1;
	if (g_100f890 != g_100f944 || d2_MouseX < g_67d8e0 - 5 || d2_MouseY < g_67d8e4 - 5 || d2_MouseX > g_67d8e0 + 5 || d2_MouseY > g_67d8e4 + 5 || g_14ce8d0 != 0) {
		g_100f888 = -1;
		g_100f1c8 = (*(int*)&g_6b7fb0);
		g_67d8e0 = d2_MouseX;
		g_67d8e4 = d2_MouseY;
		g_7725d8 = 0;
	}
	if (g_100f888 == -1) {
		if (g_100f890 == -1 || btn == 0) {
			goto done;
		}
		g_100f888 = g_100f890;
		g_67d8e0 = d2_MouseX;
		g_67d8e4 = d2_MouseY;
		g_7725d8 = 1;
	} else if (g_7725d8 == 0) {
		goto done;
	}
	if (btn == 0) {
		g_100f888 = -1;
		g_100f1c8 = (*(int*)&g_6b7fb0);
		g_67d8e0 = d2_MouseX;
		g_67d8e4 = d2_MouseY;
		g_7725d8 = btn;
		io_ClearInputButtonFlags(0x10);
	}
done:
	g_100f1c0 = d2_MouseX;
	g_100f944 = g_100f890;
	g_100f1c4 = d2_MouseY;
	if (d2_CurrentFont != -1) {
		sel = d2_CurrentFont;
	}
	for (i = 0; i < 0x60; i++) {
		if ((((Win*)d2_Windows)[i].style & 0x200) != 0 && ((Win*)d2_Windows)[i].tip_on == 1 && ((Win*)d2_Windows)[i].tip != 0) {
			d2_SelectFont(((Win*)d2_Windows)[i].tip);
		}
	}
	if (d2_HoveredWindow != -1 && (w = &((Win*)d2_Windows)[d2_HoveredWindow]) != 0 && g_14ce8d0 != 0 && w->up_btn != -1 && w->down_btn != -1 && tp_d2_SelectedControl == 0) {
		if (d2_CurrentElementId == w->up_btn) {
			w = &((Win*)d2_Windows)[(*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->up_btn].value_1f0)];
			if (w->scroll == w->scroll_max || w->scroll == 0) {
				d = w->step;
				d2_ScrollWindow(0, d, w->id);
			}
		} else if (d2_CurrentElementId == w->down_btn) {
			w = &((Win*)d2_Windows)[(*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->down_btn].value_1f0)];
			if (w->scroll == w->scroll_max || w->scroll == 0) {
				d = -w->step;
				d2_ScrollWindow(0, d, w->id);
			}
		}
	}
	if (g_67d38c != -1 && (w = &((Win*)d2_Windows)[g_67d38c]) != 0 && g_14ce904 - g_14ce900 != 0 && (d = w->step) != 0 && tp_d2_SelectedControl == 0) {
		if (g_14ce904 != 0) {
			d2_ScrollWindow(0, -d, w->id);
		} else if (g_14ce900 != 0) {
			d2_ScrollWindow(0, d, w->id);
		}
	}
	if (sel != -1) {
		d2_SelectFont(sel);
	}
}
