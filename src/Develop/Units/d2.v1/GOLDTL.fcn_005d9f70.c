#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int pad[3];
	int count;
	int pad2[5];
} Stat5d9f;

typedef struct {
	int name;
	int pad[4];
} Kind5d9f;

#include "client_types.h"
extern Rec2d_9a3800 g_9a3800[512];
#include "GOLDTL.fcn_005d9f70_gconf.h"
extern char g_6ac4c8[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_004f63d0(int, int*, unsigned short);
void __cdecl fcn_004f6780(int n, Rec2d_9a3800* arr);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005c91c0(int, int, int, int, int);
int __cdecl fcn_004f4830(int, Stat5d9f*);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_004fa5b0(int, unsigned short*, int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005d9ca0(unsigned short*, unsigned short*, int, int);

/* ADDRESS: GOLDTL 0x005d9f70 */
int __cdecl fcn_005d9f70(unsigned short* a1, unsigned short* a2)
{
	int flag;
	int sel;
	int n;
	int dlg;
	Stat5d9f st;
	int list[32];
	int q[0x88];
	Rec2d_9a3800 rows[32];
	int i;
	int k;
	int w;

	flag = 0;
	sel = -1;
	if (*a2 == 0xffff) {
		return 0;
	}
	n = fcn_004f63d0(*(int*) (a2 + 2), list, *a1);
	if (n < 1) {
		return 0x60;
	}
	for (i = 0; i < n; i++) {
		rows[i] = g_9a3800[list[i]];
		flag |= (rows[i].x25 == 1);
	}
	if (a1 == a2) {
		flag = 0;
	}
	fcn_004f6780(n, rows);
	dlg = fcn_00470820(0, 0, g_6ac4c8);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 2);
	w = g_772514;
	d2_SetForm(dlg, 4);
	fcn_0046e830(-1, -1, g_772514, w, 0x767);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1742, *a2);
	d2_SetForm(dlg, 2);
	for (k = 0; k < n; k++) {
		fcn_005c91c0(g_14aa314[rows[k].x1c].name, 10, k * 0x28 + 10, 0x13b, 0x55);
		if (fcn_004f4830(rows[k].x1c, &st) != 0 && st.count != 0) {
			for (i = 0; i < st.count; i++) {
				fcn_0046f740(i * 0x10 + 0x154, k * 0x28 + 10, 0x526, g_772514);
			}
		}
	}
	memset(q, 0, sizeof(q));
	q[0] = 1;
	d2_SetForm(dlg, 3);
	if (fcn_004fa5b0(0x16, a2, q) & 2) {
		io_AppendText(0x174a);
	} else {
		sel = fcn_00472250(dlg, 3, io_AppendText(0x1745));
		if (flag == 0) {
			fcn_00472640(sel, 0);
		}
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == sel) {
				fcn_005d9ca0(a1, a2, n, 0);
				g_774654 = 3;
			}
		}
	} while (fcn_005373e0(fcn_005d9f70, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return 0;
}
