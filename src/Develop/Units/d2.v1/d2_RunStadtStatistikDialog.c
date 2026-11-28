/* Float block handed to fcn_005d3d90 and filled by fcn_004fc460. */
typedef struct Gfx {
	float f[10];
} Gfx;
// SIZE 0x28

/* Draw entity: 0x2f4 bytes in the g_1015ea0 table. */
typedef struct Ent {
	char pad0[0x58];
	int x58;             /* 0x058 */
	int x5c;             /* 0x05c */
	char pad60[0x294];
} Ent;
// SIZE 0x2f4

extern char* g_1015ea0;
#include "Develop/Units/d2.v1/d2_win.h"
extern char g_1015f40[];
extern int d2_CurrentWindowId;
extern unsigned char g_773d75;
extern float g_773d4c;
extern unsigned short g_775340;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_14ce8e0;
extern int g_100f1dc;
extern double dbl_1_0;
extern double g_662cc0;
extern float g_662a98;
extern float g_662cf8;
extern double g_662c38;

int __cdecl d2_TutorialAllowsFlag(int a);
void __cdecl d2_DispatchTutorialInput(int a, int b, int c, int d);
char* __cdecl d2_LoadForm(int a, int b, char* name);
void __cdecl d2_CenterDialogWindows(char* dlg);
void __cdecl d2_SetForm(char* dlg, int page);
void __cdecl d2_SetOverlayAnimation(int a, int b);
int __cdecl io_AppendText(int id, ...);
float __cdecl gm_GetCityStatsSummary(Gfx* g);
void __cdecl d2_DrawCityHistoryCharts(unsigned short flags, Gfx g, int rec);
char* __cdecl d2_AddElementToWindow(int x, int y, int id, int layer);
void __cdecl d2_EqualizeWindowButtonWidths(int a, int y, char* text, int rec);
int __cdecl d2_CreateGuiWindow(int id, int mask);
void __cdecl d2_DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl d2_GetControlValue(int id);
int __cdecl main_RunFrameLoop(void* fn, int id);
void __cdecl d2_DestroyForm(char* dlg);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005d42e0 */
void __cdecl d2_RunStadtStatistikDialog(void)
{
	unsigned char colors[15];
	char* cp;
	char* dlg;
	int r;
	int g;
	int b;
	Gfx gfx;
	int items[5];
	char buf[256];
	int row;
	int i;
	int n;
	int j;
	int mask;

	colors[0] = 0x33;
	colors[1] = 0x33;
	colors[2] = 0x33;
	colors[3] = 0x10;
	colors[4] = 0xee;
	colors[5] = 0x10;
	colors[6] = 0xee;
	colors[7] = 0x10;
	colors[8] = 0x10;
	colors[9] = 0xee;
	colors[10] = 0xee;
	colors[11] = 0x00;
	colors[12] = 0xee;
	colors[13] = 0x10;
	colors[14] = 0xee;
	if (g_775340 == 0) {
		g_775340 = 1;
	}
	if (!d2_TutorialAllowsFlag(0x10)) {
		return;
	}
	d2_DispatchTutorialInput(0xc, 0, 0, 0);
	dlg = d2_LoadForm(0, 0, "panel\\statistik_stadt");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f0e, (int) g_773d75 * 0x2f4 + 0x868080, 0x7f4c00);
	gm_GetCityStatsSummary(&gfx);
	d2_SetForm(dlg, 2);
	io_AppendText(0x1f14, (int) g_773d4c);
	n = (int) ((gfx.f[9] + dbl_1_0) * g_662cc0);
	if (n > 4) {
		n = 4;
	}
	io_AppendText(0x1f15, n + 0x1f16);
	n = (int) (gfx.f[2] * 5.0f);
	if (n > 4) {
		n = 4;
	}
	io_AppendText(0x1f1b, n + 0x1f1c);
	io_AppendText(0x1f21, (int) (gfx.f[1] * 100.0f > 0.0 ? gfx.f[1] * 100.0f : 0.0));
	n = (int) ((gfx.f[3] > 0.0 ? gfx.f[3] : 0.0) * g_662c38);
	io_AppendText(0x1f22, n);
	d2_SetForm(dlg, 3);
	d2_DrawCityHistoryCharts((unsigned short) g_775340, gfx, d2_CurrentWindowId);
	d2_SetForm(dlg, 4);
	cp = (char*) &colors[1];
	row = 0;
	for (i = 4; i < 0x9a; i += 0x1e) {
		mask = (1 << row) & g_775340;
		mask = mask != 0;
		n = d2_AddElementToWindow(5, i + 1, 2, d2_CurrentWindowId);
		items[row] = n;
		io_FormatTextBuffer(buf, row + 0x1f25);
		d2_EqualizeWindowButtonWidths(0x19, i, buf, d2_CurrentWindowId);
		((D2_CONTROL_TL*) g_1015ea0)[n].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[n].value_058 = 1;
		d2_CreateGuiWindow(n, mask);
		*(char*) &r = cp[-1];
		*(char*) &g = cp[0];
		*(char*) &b = cp[1];
		for (j = i + 5; j < i + 15; j++) {
			d2_DrawLine(((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width - 1, j,
				((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width - 0xb, j, r, g, b);
		}
		row++;
		cp += 3;
	}
	g_100f1dc = -1; for (;;) {
		if (g_100f1dc != -1) {
			g_775340 = 0;
			for (i = 0; i < 5; i++) {
				g_775340 |= d2_GetControlValue(items[i]) ? (1 << i) : 0;
			}
			d2_SetForm(dlg, 3);
			d2_DrawCityHistoryCharts(g_775340, gfx, d2_CurrentWindowId);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (!main_RunFrameLoop(d2_RunStadtStatistikDialog, 0x657c7)) {
			break;
		}
	}
	d2_DestroyForm(dlg);
	d2_DispatchTutorialInput(0xc, 0, 1, 0);
}
