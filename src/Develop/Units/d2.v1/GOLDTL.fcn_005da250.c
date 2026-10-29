

// SIZE 0x38
typedef struct Row {
	char* who;
	int id;
	char pad8[8];
	int x;
	int y;
	char pad18[0x14];
	int a;
	int shown;
	int b;
} Row;

// SIZE 0x3cc
struct s_1015f4c {
	int x;
	int y;
	char pad[0x3c4];
};

#include "client_types.h"

extern s_1015f4c g_1015f4c[];
extern int g_772514;
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004f63d0(int id, int* ids, short kind);
int __cdecl fcn_005d9ca0(char* e, char* who, int n, int a4);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_004f61c0(int* ids, int* b, int* c, short kind);
int __cdecl fcn_005ca560(Row* r);
void __cdecl fcn_005ca740(int, int, int, int, Row*, int);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_005c9160(char*, int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005d9f70(char* e, char* who);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005da250(char* e, char* a2)
{
	int result;
	int count;
	int n;
	int dlg;
	char text[0x40];
	int b[32];
	int ids[32];
	int c[32];
	Row rows[32];
	char* who;
	int win;
	int i;
	int sel;

	result = 0x20;
	if (e[2] != 6 && e[2] != 7) {
		if (e[0x166] == 0xd) {
			return 0x60;
		}
		who = fcn_00508e40(*(int*) (a2 + 0x214));
		if (who == 0 || who[0x166] == 0xd) {
			return 0x60;
		}
		b[0] = fcn_004f63d0(*(int*) (a2 + 0x214), ids, *(short*) e);
		if (b[0] == 0) {
			return 0x60;
		}
		return fcn_005d9ca0(e, who, b[0], 0);
	}
	dlg = fcn_00470820(0, 0, "privillegien\\Beweise_Sichten");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x173f);
	d2_SetForm(dlg, 2);
	win = g_772514;
	d2_SetForm(dlg, 3);
	fcn_0046e830(-1, -1, g_772514, win, 0x767);
	n = fcn_004f61c0(ids, b, c, *(short*) e);
	for (i = 0, count = 0; i < n; i++) {
		who = fcn_00508e40(ids[i]);
		if (who != 0) {
			rows[count].who = who;
			rows[count].a = c[i];
			rows[count].b = b[i];
			fcn_005ca560(&rows[count]);
			rows[count].shown = 1;
			count++;
		}
	}
	d2_SetForm(dlg, 2);
	if (count != 0) {
		for (i = 0; i < count; i++) {
			fcn_0051af00(text, "%i (%i) %s", rows[i].a, rows[i].b, (rows[i].a != 1) + 0x1748);
			rows[i].x = 0x32;
			rows[i].y = i * 0x69 + 10;
			fcn_005ca740(0x32, i * 0x69 + 10, g_772514, 0x56, &rows[i], 1);
			fcn_005c9160(text, ((struct s_1015f4c*) g_1015f4c)[g_772514].x - 0xf, i * 0x69 + 10 + 0x2d, 0xc8, 0x55);
		}
	} else {
		fcn_00519190(0x1741, g_774970);
	}
	fcn_00473a90(0, 0);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			sel = -1;
			for (i = 0; i < count; i++) {
				if (g_67d370 == rows[i].id) {
					sel = i;
					break;
				}
			}
			if (sel > -1) {
				result = fcn_005d9f70(e, rows[sel].who);
			}
		}
	} while (fcn_005373e0(fcn_005da250, 0x657c7));
	fcn_00471e30(dlg);
	return result;
}
