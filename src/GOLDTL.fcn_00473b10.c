

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
extern int g_100f1e8;
extern int g_100f1ec;
extern int g_14ce8e8;
extern int g_67d8e0;
extern int g_67d8e4;
extern int g_14ce8d0;
extern volatile int g_6b7fb0;
extern int g_100f888;
extern int g_100f1c8;
extern int g_7725d8;
extern int g_100f1c0;
extern int g_100f1c4;
extern int g_67d378;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_100f894;
extern int g_7725d0;
extern int g_67d370;
extern char* g_1015ea0;
extern int g_67d38c;
extern int g_14ce900;
extern int g_14ce904;

void __cdecl fcn_00412830(unsigned char mask);
char* __cdecl fcn_00472880(int idx);
void __cdecl fcn_0046ed00(int delta, int step, int k);

void __cdecl fcn_00473b10(void)
{
	int sel;
	int btn;
	Win* w;
	int d;
	int i;

	btn = g_14ce8e8;
	sel = -1;
	if (g_100f890 != g_100f944 || g_100f1e8 < g_67d8e0 - 5 || g_100f1ec < g_67d8e4 - 5 || g_100f1e8 > g_67d8e0 + 5 || g_100f1ec > g_67d8e4 + 5 || g_14ce8d0 != 0) {
		g_100f888 = -1;
		g_100f1c8 = (*(int*)&g_6b7fb0);
		g_67d8e0 = g_100f1e8;
		g_67d8e4 = g_100f1ec;
		g_7725d8 = 0;
	}
	if (g_100f888 == -1) {
		if (g_100f890 == -1 || btn == 0) {
			goto done;
		}
		g_100f888 = g_100f890;
		g_67d8e0 = g_100f1e8;
		g_67d8e4 = g_100f1ec;
		g_7725d8 = 1;
	} else if (g_7725d8 == 0) {
		goto done;
	}
	if (btn == 0) {
		g_100f888 = -1;
		g_100f1c8 = (*(int*)&g_6b7fb0);
		g_67d8e0 = g_100f1e8;
		g_67d8e4 = g_100f1ec;
		g_7725d8 = btn;
		fcn_00412830(0x10);
	}
done:
	g_100f1c0 = g_100f1e8;
	g_100f944 = g_100f890;
	g_100f1c4 = g_100f1ec;
	if (g_67d378 != -1) {
		sel = g_67d378;
	}
	for (i = 0; i < 0x60; i++) {
		if ((((Win*)g_1015f40)[i].style & 0x200) != 0 && ((Win*)g_1015f40)[i].tip_on == 1 && ((Win*)g_1015f40)[i].tip != 0) {
			fcn_00472880(((Win*)g_1015f40)[i].tip);
		}
	}
	if (g_100f894 != -1 && (w = &((Win*)g_1015f40)[g_100f894]) != 0 && g_14ce8d0 != 0 && w->up_btn != -1 && w->down_btn != -1 && g_7725d0 == 0) {
		if (g_67d370 == w->up_btn) {
			w = &((Win*)g_1015f40)[((Slot*)g_1015ea0)[w->up_btn].win];
			if (w->scroll == w->scroll_max || w->scroll == 0) {
				d = w->step;
				fcn_0046ed00(0, d, w->id);
			}
		} else if (g_67d370 == w->down_btn) {
			w = &((Win*)g_1015f40)[((Slot*)g_1015ea0)[w->down_btn].win];
			if (w->scroll == w->scroll_max || w->scroll == 0) {
				d = -w->step;
				fcn_0046ed00(0, d, w->id);
			}
		}
	}
	if (g_67d38c != -1 && (w = &((Win*)g_1015f40)[g_67d38c]) != 0 && g_14ce904 - g_14ce900 != 0 && (d = w->step) != 0 && g_7725d0 == 0) {
		if (g_14ce904 != 0) {
			fcn_0046ed00(0, -d, w->id);
		} else if (g_14ce900 != 0) {
			fcn_0046ed00(0, d, w->id);
		}
	}
	if (sel != -1) {
		fcn_00472880(sel);
	}
}
