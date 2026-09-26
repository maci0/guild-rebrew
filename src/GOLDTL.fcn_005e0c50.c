// FUNCTION: GOLDTL 0x005e0c50
// SIZE: 823

#include <stdio.h>

// SIZE 0x210
typedef struct {
	char pad0[9];
	char name[0x80];
	char text[0x187];
} Rec;

// SIZE 0x220
typedef struct {
	char id;
	char pad1[3];
	int h;
	int f8;
	int padc;
	Rec rec;
} Slot;

// SIZE 0x3cc
typedef struct {
	char pad0[0x260];
	int f260;
	char pad264[0x18];
	int f27c;
	char pad280[0x14c];
} Win;

// SIZE 0x2f4
typedef struct {
	char pad0[0x10];
	int f10;
	int f14;
	char pad18[0x28];
	Win* f40;
	char pad44[0x2b0];
} Ctl;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char s_6acfdc[];
extern char s_6acfcc[];
extern char s_6acfb4[];
extern char s_6ad004[];
extern char* g_14ac648;
extern char g_773de8;

// SIZE 0x9600
typedef struct {
	int v[0x2580];
} Blob;

extern unsigned short g_7ea3c0[];
extern int g_772514;
extern int g_7e46ac;
extern int g_6b7fdc;
extern int g_100f894;
extern char* g_14ac64c;
extern int g_14ce8e0;
extern int g_14ce8d8;
extern int g_774654;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471db0(int, int);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);
void __cdecl fcn_005e0140(int, int, Slot*, Rec*, char*, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_0042f120(char*, int, int*);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_005e0b40(int, int, char*);
int __cdecl fcn_005dfe80(char*, int);
int __cdecl fcn_005268c0(char*, int);
void __cdecl fcn_0051e080(char*, char*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005e0c50(Blob* src)
{
	int i;
	int dlg;
	int sel;
	int wait;
	int b;
	int a;
	int c;
	int st;
	char tmp[0x104];
	char buf[0x104];
	Slot slots[16];
	Rec recs[32];
	int flag;
	int h;

	wait = g_7e46ac;
	dlg = fcn_00470820(0, 0, s_6acfdc);
	fcn_00471db0(dlg, 1);
	fcn_00471d80(dlg, 2);
	fcn_004727a0(dlg, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	fcn_004727a0(0, 2);
	fcn_00519190(0x1c58);
	fcn_004727a0(0, 0);
	fcn_00533f40(0x214, 0x168, g_772514, fcn_00472830(dlg, 1), 0x82, &a, &b, &c);
	fcn_005e0140(dlg, 1, slots, recs, s_6acfcc, 0);
	fcn_00472640(slots[0].h, 0);
	fcn_00472640(slots[1].h, 0);
	sel = fcn_00472830(dlg, 1);
	while (fcn_005373e0((void*) fcn_005e0c50, wait) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_14ce8d8 != 0 && ((Win*)g_1015f40)[sel].f260 == 0) {
			for (i = 2; i < 16; i++) {
				if (g_67d370 != slots[i].h && g_100f894 != slots[i].f8) {
					if (g_100f894 == -1) {
						continue;
					}
					if (((Ctl*)g_1015ea0)[((Win*)g_1015f40)[g_100f894].f27c].f40 != &((Win*)g_1015f40)[slots[i].f8]) {
						continue;
					}
				}
				flag = 0;
				sprintf(tmp, s_6acfb4, slots[i].rec.name);
				if (fcn_0042f120(tmp, g_6b7fdc, &st)) {
					flag = 1;
				}
				fcn_00472170(slots[i].h, 0);
				if (!fcn_005e0b40(((Ctl*)g_1015ea0)[slots[i].h].f10, ((Ctl*)g_1015ea0)[slots[i].h].f14, slots[i].rec.text)) {
					fcn_00472170(slots[i].h, 1);
					break;
				}
				if (!flag || fcn_005dfe80(g_14ac64c, 0x101)) {
					sprintf(buf, s_6ad004, i);
					(*(Blob*)g_7ea3c0) = *src;
					g_773de8 = (char) i;
					h = fcn_005268c0(g_14ac648, 0);
					fcn_0051e080(buf, slots[i].rec.text, 1);
					fcn_00471e30(h);
					g_774654 = 1;
				}
				fcn_00472170(slots[i].h, 1);
			}
		}
	}
	fcn_00471e30(dlg);
	return 0;
}
