

#include <stdio.h>

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	char pad10[0x3cc - 0x10];
} Slot;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int linked;
	char pad60[0x2f0 - 0x60];
	char* owner;
} Ctl;

extern int g_6a25b8;
extern int g_6a25c0;
extern int g_6a25d8;
extern int g_1040494;
extern int g_7746f0;
extern int g_14b5f10;
extern unsigned short g_774970;
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char g_6a2fc8[];
extern char g_6a2e8c[];

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl d2_SetForm(int h, int mode);
int __cdecl fcn_0050f950(int a, int b);
int __cdecl fcn_00507c30(int k);
float __cdecl fcn_004ff040(char* e);
void __cdecl fcn_005186c0(int id, int a, int b, char* out);
void __cdecl fcn_00519190(char* fmt, ...);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
int __cdecl fcn_004677e0(int a, int b, int c, int d, int e, int f, int g, int h);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00534160(int x, int y, int v, int kind);

void __cdecl fcn_0052e7b0(char* e)
{
	char buf[512];
	int rel;
	int kind;
	int pct;
	int x;
	int v;

	if (g_6a25b8 != -1) {
		return;
	}
	g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2fc8);
	d2_SetForm(g_6a25b8, 1);
	if (e != 0 && g_7746f0 < 2) {
		rel = fcn_0050f950(g_774970, *(unsigned short*) e);
		kind = 0;
		if (*(unsigned char*) (e + 0x165) != 0) {
			kind = fcn_00507c30(*(unsigned char*) (e + 0x165));
		}
		pct = (int) (fcn_004ff040(e) * 100.0);
		fcn_005186c0(*(unsigned short*) e, 1, 4, buf);
		fcn_00519190(g_6a2e8c, buf, pct);
		d2_SetForm(g_6a25b8, 0);
		x = (((Slot*)g_1015f40)[g_772514].width - 0x30) >> 1;
		g_6a25c0 = fcn_004677e0(0x18, 0x6c, 0x30, 0, 0x64, 0x75, 0x442, g_772514);
		d2_SetElementValue(g_6a25c0, -0x7f, 0x7f, rel);
		if (e[2] == 5 || e[2] == 6 || e[2] == 7) {
			fcn_0046f740(x - 8, 0x30, *(int*) (e + 0x54), g_772514);
		}
		if (kind == 0xb || kind == 0xc || kind == 0xa) {
			v = *(unsigned char*) (e + 0x82);
			fcn_0046f740(0x19, 0x7e, 0x5df, g_772514);
			fcn_00534160(0x29, 0x7e, v, 0x4f1);
			fcn_0046f740(0x19, 0x8c, 0x5e0, g_772514);
			fcn_00534160(0x29, 0x8c, *(unsigned char*) (e + 0x83), 0x4f1);
		}
	}
	else {
		sprintf(buf, "%i %s", g_7746f0, g_14b5f10);
		fcn_00519190(buf);
	}
	d2_SetForm(g_6a25b8, 0);
	x = (((Slot*)g_1015f40)[g_772514].width - 0x30) >> 1;
	if (e != 0) {
		g_6a25d8 = fcn_0046f740(x, 0x38, *(int*) (e + 0x18c), g_772514);
		((Ctl*)g_1015ea0)[g_6a25d8].owner = e;
		((Ctl*)g_1015ea0)[g_6a25d8].linked = 1;
	}
	else {
		fcn_0046f740(x, 0x38, 0x521, g_772514);
	}
}
