#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int pad[3];
	int count;
	int pad2[5];
} Stat5da5;

typedef struct {
	int name;
	int pad[4];
} Kind5da5;

#include "client_types.h"
extern Rec2d_9a3800 g_9a3800[512];
extern Kind5da5 g_14aa314[];
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
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005c91c0(int, int, int, int, int);
int __cdecl fcn_004f4830(int, Stat5da5*);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_004fa5b0(int, unsigned short*, int*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005d9ca0(unsigned short*, unsigned short*, int, int);

/* ADDRESS: GOLDTL 0x005da560 */
int __cdecl fcn_005da560(unsigned short* a1, unsigned short* a2)
{
	struct {
		int n;
		int flag;
		int result;
		int dlg;
	} v;
	Stat5da5 st;
	int list[32];
	int q[0x88];
	Rec2d_9a3800 rows[32];
	int i;
	int k;
	int w;
	int sel;

	v.result = 0x20;
	if (*a2 == 0xffff) {
		return 0;
	}
	v.n = fcn_004f63d0(*(int*) (a2 + 2), list, *a1);
	if (v.n < 1) {
		return 0;
	}
	v.flag = 0;
	for (i = 0; i < v.n; i++) {
		rows[i] = g_9a3800[list[i]];
		v.flag |= (rows[i].x25 == 1);
	}
	if (a1 == a2) {
		v.flag = 0;
	}
	fcn_004f6780(v.n, rows);
	v.dlg = fcn_00470820(0, 0, g_6ac4c8);
	fcn_00471b60(v.dlg);
	fcn_004727a0(v.dlg, 2);
	w = g_772514;
	fcn_004727a0(v.dlg, 4);
	fcn_0046e830(-1, -1, g_772514, w, 0x767);
	fcn_00473a90(0, 0);
	fcn_004727a0(v.dlg, 1);
	fcn_00519190(0x1742, *a2);
	fcn_004727a0(v.dlg, 2);
	for (k = 0; k < v.n; k++) {
		fcn_005c91c0(g_14aa314[rows[k].x1c].name, 10, k * 0x28 + 10, 0x13b, 0x55);
		if (fcn_004f4830(rows[k].x1c, &st) != 0 && st.count != 0) {
			for (i = 0; i < st.count; i++) {
				fcn_0046f740(i * 0x10 + 0x154, k * 0x28 + 10, 0x526, g_772514);
			}
		}
	}
	memset(q, 0, sizeof(q));
	q[0] = 1;
	fcn_004727a0(v.dlg, 3);
	sel = fcn_00472250(v.dlg, 3, fcn_00519190(0x1745));
	if ((fcn_004fa5b0(0x16, a2, q) & 2) != 0) {
		fcn_00472640(sel, 0);
	} else if (v.flag == 0) {
		fcn_00472640(sel, 0);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == sel) {
				v.result = fcn_005d9ca0(a1, a2, v.n, 1);
				g_774654 = 3;
			}
		}
	} while (fcn_005373e0(fcn_005da560, 0x657c7) != 0);
	fcn_00471e30(v.dlg);
	return v.result;
}
