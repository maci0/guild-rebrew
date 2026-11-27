#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int g_774654;
extern char g_67728c[];

typedef struct {
	int d;
	int pad4;
	unsigned char f8;
	char rest[0x213];
} Entry5aa;

int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_DestroyForm(int);
int __cdecl d2_GetControlValue(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl d2_CreateGuiWindow(int, int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_InitWindowBounds(int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl gm_AmountToUnits(int, unsigned char);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl gm_CheckEntityStock(void*, int, unsigned char);
void __cdecl d2_ClampAmountToRange(int, int, int, int*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl d2_ShowModalMessageBox(char*, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x005aaf60 */
void __cdecl d2_RunKircheSpendenDialog(char* gebaeude)
{
	char buf[512];
	int dlg;
	int ok;
	int h;
	int c;
	int a;
	int b;
	float total;
	float frac;
	int m;
	int n;
	int cnt;
	int v;
	int d;
	int i;
	int off;
	float scale;

	ok = 0;
	c = -1;
	a = -1;
	b = -1;
	if (gebaeude == 0) {
		return;
	}
	if (*(unsigned short*) (gebaeude + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (gebaeude + 0x27) == g_774970) {
		return;
	}
	h = fcn_00502cd0(*(int*) (gebaeude + 0x5d), 2, 6, 0, 0xe8);
	if (h == 0) {
		return;
	}
	m = gm_WalkEntityChain(g_774970) > 1 ? gm_WalkEntityChain(g_774970) : 1;
	n = gm_WalkEntityChain(*(unsigned short*) (gebaeude + 0x27)) > 1
		? gm_WalkEntityChain(*(unsigned short*) (gebaeude + 0x27)) : 1;
	cnt = (int) ((total = (float) (m + n)) * 0.01f);
	v = gm_AccumulateTyped2((char*) (g_774970 * 0x21c + (int) g_7f4ca0));
	if (v >= cnt) {
		ok = 1;
	}
	dlg = d2_LoadForm(0, 0, "Locations\\Kirche\\Spenden");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(dlg);
	d2_SetForm(dlg, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1986);
	if (!ok) {
		io_AppendText(0x1987, g_774970,
			*(unsigned short*) (g_8680b4 + (unsigned char) g_773d75 * 0x2f4) * 2 + 0x9a8);
	} else {
		c = io_AppendText(0x1988, g_774970, *(unsigned short*) (gebaeude + 0x27), 0x48c,
			*(unsigned short*) (g_8680b4 + (unsigned char) g_773d75 * 0x2f4) * 2 + 0x9a8);
		d2_ClampAmountToRange(cnt, v, 0x20, &b);
		c = d2_GetWindowListItem(dlg, 1, c);
		d2_CreateGuiWindow(c, gm_AmountToUnits(cnt, g_773d75), gm_AmountToUnits(b, g_773d75),
			gm_AmountToUnits(cnt, g_773d75));
		d2_SetForm(dlg, 2);
		n = io_AppendText(0x1989);
		a = d2_GetWindowListItem(dlg, 2, n);
		b = d2_GetWindowListItem(dlg, 2, n + 1);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == a) {
				d = d2_GetControlValue(c);
				d = fcn_0050b750(d, g_773d75);
				if (gm_CheckEntityStock((char*) (g_774970 * 0x21c + (int) g_7f4ca0), d,
					g_773d75) != 0) {
					cm_RequestMoveCredits(*(int*) (h + 2), *(int*) (g_774970 * 0x21c + (int) g_7f4ca4),
						g_773d75, d);
					frac = (float) (d * 255) / total;
					cm_RequestCopyEntityData(*(int*) (g_774970 * 0x21c + (int) g_7f4ca4),
						*(int*) (*(unsigned short*) (gebaeude + 0x27) * 0x21c + (int) g_7f4ca4), (int) frac, 1);
					scale = frac * 0.2f;
					for (i = 0; i < 0x300; i++) {
						Entry5aa* ent;
						if (i == g_774970) {
							continue;
						}
						ent = (Entry5aa*) g_7f4ca4;
						d = ent[i].d;
						if (d == -1) {
							continue;
						}
						off = *(unsigned short*) (gebaeude + 0x27) * 0x21c;
						if (d == *(int*) (g_7f4ca4 + off)) {
							continue;
						}
						if (*(unsigned char*) (g_7f4ca4 + off + 8) != ent[i].f8) {
							continue;
						}
						cm_RequestCopyEntityData(*(int*) (g_7f4ca4 + g_774970 * 0x21c), d, (int) scale, 1);
					}
					io_FormatTextBuffer(buf, g_67728c, 0x1986, 0x198a);
					d2_ShowModalMessageBox(buf, 0);
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == b) {
				g_774654 = 1;
			}
		}
	} while (main_RunFrameLoop((void*) d2_RunKircheSpendenDialog, 0x677c7) != 0);
	d2_DestroyForm(dlg);
	d3_EndCameraAndUiMode();
}
