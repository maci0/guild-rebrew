#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"

extern int g_774654;
extern int g_67d370;
extern int g_14ce8e0;
extern float g_662910;

int __cdecl fcn_004f39b0(int a);
int __cdecl fcn_004f5dd0(int a);
void __cdecl fcn_004f5e20(int a, int b);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl fcn_005c6270(char*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(char*, int, int);
int __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c5150(int, int, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_005b2150(char*, char*, char*, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_0050e600(int, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005abd60(void);

/* Church indulgence ("Ablass") dialog: offers the indulgence for the current
 * player and, once bought, continues with the results screen. */
/* ADDRESS: GOLDTL 0x005ab3e0 */
void __cdecl fcn_005ab3e0(char* a0)
{
	char text[0x200];
	char* rec;
	int count;
	int kind;
	int cost;
	int dlg;
	int item;
	int sel;
	int val;
	int changed;
	float scale;
	float factor;
	double v;

	item = -1;
	cost = 0;
	count = fcn_004f39b0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4));
	kind = fcn_004f5dd0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4));
	if (kind != 0) {
		scale = (float) gm_WalkEntityChain(g_774970) * 0.005f;
		factor = 1.5f;
		if (*(unsigned short*) (a0 + 0x27) != g_774970)
			factor = (200.0f - fcn_0050f980(g_774970, *(unsigned short*) (a0 + 0x27), 1)) * g_662910;
		cost = (int) ((float) kind * factor * scale);
		v = (double) cost * 0.1;
		cost = (int) (320000.0 < (v > 3200.0 ? v : 3200.0) ? 320000.0 : (v > 3200.0 ? v : 3200.0));
		if (fcn_005c6270(g_7f4ca0 + g_774970 * 0x21c, 0x2c6) != 0)
			cost = cost / 2;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ab014);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1960);
	if (cost > 0) {
		io_AppendText(0x1962, count, cost);
		d2_SetForm(dlg, 2);
		item = fcn_00472250(dlg, 2, io_AppendText(0x1963));
	} else {
		io_AppendText(0x1961, g_774970);
	}
	g_100f1dc = -1;
	changed = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1 && g_67d370 == item
			&& fcn_00526010(g_7f4ca0 + g_774970 * 0x21c, cost, g_773d75) != 0) {
			rec = g_7f4ca0 + g_774970 * 0x21c;
			fcn_004c4510(rec, *(int*) (rec + 4));
			fcn_004c4670(4, 1, 0x1ac, &cost);
			fcn_004c5360();
			fcn_004f5e20(*(int*) (rec + 4), count);
			if (*(unsigned short*) (a0 + 0x27) != 0xffff
				&& *(unsigned short*) (a0 + 0x27) != g_774970) {
				val = (int) (cost / log10((double) cost));
				fcn_004c5150(-1, *(int*) (rec + 4), g_773d75, cost);
				sel = fcn_004c5150(*(int*) (g_7f4ca0 + *(unsigned short*) (a0 + 0x27) * 0x21c + 4),
					-1, g_773d75, val);
				fcn_005b2150(rec, g_7f4ca0 + *(unsigned short*) (a0 + 0x27) * 0x21c, a0, val, cost);
			} else {
				sel = fcn_004c5150(-1, *(int*) (rec + 4), g_773d75, cost);
			}
			while (sel != -1 && fcn_004c4450(sel) == 0)
				fcn_00535960();
			io_FormatTextBuffer(text, 0x1964, *(int*) (rec + 0x1ac), fcn_0050e600(g_774970, 0));
			fcn_00526120(text, 0x100);
			changed = 1;
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005ab3e0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	if (changed)
		fcn_005abd60();
	else
		fcn_00532ef0();
}
