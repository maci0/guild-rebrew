// FUNCTION: GOLDTL 0x0059e090
// SIZE: 764

typedef struct {
	int x0;
	char pad4[0x3a0];
	float x3a4;
	char pad3a8[0x24];
} Slot;
// SIZE 0x3cc

typedef struct {
	char pad0[0xc];
	int slot;
	char pad10[0x2ac];
} Dlg;
// SIZE 0x2bc

typedef struct {
	char pad0[0x4c];
	int x4c;
	char pad50[0x10];
	int x60;
	char pad64[0x290];
} City;
// SIZE 0x2f4

typedef struct {
	int x0;
	int a;
	int b;
	char padc[0x14];
} Pick;
// SIZE 0x20

#include "client_types.h"

extern int g_14ce8e0;
extern int g_774654;
extern int g_772514;
extern int g_14a566c;
extern int g_6b7fac;
extern Win_1015f40 g_1015f40[0x60];
extern Obj_1038140 g_1038140[];
extern char* g_1015ea0;
extern char g_868060[];
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00533dc0(int, int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0046e7a0(char*, int);
void __cdecl fcn_00533a60(int, int, Pick*, int, int, char*, char*);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_00594340(void);
void __cdecl fcn_005974e0(char*, int);
void __cdecl fcn_00597940(int, int, int, char*, int);

/* Transport dialog: shows the export/import pick for building b and
 * redraws whenever the direction changes. */
void __cdecl fcn_0059e090(char* b)
{
	int grp;
	int a;
	int c;
	int shown;
	int t0;
	int h;
	int sel;
	double d;
	Slot* slot;
	Pick pick;
	char buf[0x104];

	slot = 0;
	a = 0;
	c = 0;
	t0 = 0;
	grp = 0;
	if (b[0] != 'G') {
		return;
	}
	h = -1;
	sel = 1;
	shown = -1;
	while (fcn_005373e0(fcn_0059e090, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (sel != shown) {
			if (h != -1) {
				fcn_00471e30(h);
			}
			h = fcn_00470820(0, 0, "Handel\\Handel_Transport");
			fcn_00471b60(h);
			fcn_004727a0(h, 0);
			fcn_00533dc0(g_772514, 0x70b, 0x73f);
			slot = (Slot*) &g_1015f40[((Dlg*)g_1038140)[h].slot];
			fcn_0064d41a(buf, "ief_Wappen%li", *(int*) (b + 0x65));
			fcn_0046e7a0(buf, slot->x0);
			slot->x3a4 = 0.0f;
			t0 = *(volatile unsigned int*)&g_6b7fac;
			fcn_004727a0(h, 4);
			fcn_00533a60(g_772514, 0, &pick, 3, g_14a566c, "Import", "Export");
			fcn_00472170(pick.x0, 0);
			a = pick.a;
			c = pick.b;
			if (sel != 0) {
				grp = fcn_00502cd0(*(int*) (b + 0x5d), 2, 0, 0x1db, 6);
				if (grp == 0) {
					return;
				}
				fcn_004727a0(h, 3);
				fcn_00519190(0x1c47, g_868060 + *(int*) (b + 0x65) * 0x2f4);
			}
			else {
				grp = fcn_00502cd0(*(int*) (b + 0x5d), 2, 0, 0x1dc, 6);
				if (grp == 0) {
					return;
				}
				fcn_004727a0(h, 3);
				fcn_00519190(0x1c48, g_868060 + *(int*) (b + 0x65) * 0x2f4);
			}
			((City*)g_1015ea0)[a].x4c = sel;
			((City*)g_1015ea0)[a].x60 = sel;
			((City*)g_1015ea0)[c].x4c = sel == 0;
			((City*)g_1015ea0)[c].x60 = sel == 0;
			fcn_00594340();
			shown = sel;
		}
		d = (*(volatile unsigned int*)&g_6b7fac - t0) * 0.0013333333333333333;
		if (!(d < 0.25)) {
			d = 0.25;
		}
		slot->x3a4 = (float) d;
		fcn_005974e0(b, grp);
		fcn_00597940(h, 1, 0, b, grp);
		if (g_100f1dc == 2) {
			if (g_67d370 == a) {
				sel = 1;
			}
			else if (g_67d370 == c) {
				sel = 0;
			}
		}
	}
	if (h != -1) {
		fcn_00471e30(h);
	}
}
