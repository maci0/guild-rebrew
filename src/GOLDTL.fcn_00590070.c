// FUNCTION: GOLD 0x587ad0
// SIZE: 692
// FUNCTION: GOLDTL 0x590070
// SIZE: 692

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x180];
	unsigned char grave;
	char pad189[0x93];
};

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern int g_774800;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_14b556c;

int __cdecl fcn_00500e20(pos14_7f4c00*);
int __cdecl fcn_00525fb0(char*);
char* __cdecl fcn_005463a0(int, int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_0052a0c0(char*, int);
int __cdecl fcn_005373e0(void*, int);
float __cdecl fcn_00507f10(struct house*, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_0058ff60(char*, struct house*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);

void __cdecl fcn_00590070(char* who)
{
	int b2;
	char buf[0x400];
	struct house* hh;
	int st;
	int h;
	int s;
	int b1;
	int b4;
	int i;
	int k;

	hh = 0;
	st = fcn_00500e20(&g_7f4c00);
	if (fcn_00525fb0(who) != 0) {
		return;
	}
	if (g_774800 == 0 && st != 2) {
		fcn_0051af00(buf, 0x413b);
		fcn_00526120((int) buf, 4);
		fcn_00532ef0();
		return;
	}
	if (fcn_005463a0(2, 0, 0x8f, 3, *(int*) (who + 1)) != 0) {
		fcn_0051af00(buf, 0x413c);
		fcn_00526120((int) buf, 4);
		fcn_00532ef0();
		return;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\UpgradeWorker");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x4138);
	fcn_004727a0(h, 3);
	s = fcn_00519190(0x4139, 0x228);
	b1 = fcn_00472250(h, 3, s);
	b2 = fcn_00472250(h, 3, s + 1);
	b4 = fcn_00472250(h, 3, s + 2);
	fcn_0052a0c0(who, 0);
	while (fcn_005373e0(fcn_00590070, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		for (i = 0; i < 768; i++) {
			if (((struct house*)g_7f4ca0)[i].grave != 0) {
				hh = &((struct house*)g_7f4ca0)[i];
				break;
			}
		}
		if (hh != 0) {
			if (fcn_00507f10(hh, 1) >= 1.0) {
				fcn_00472640(b1, 0);
			} else {
				fcn_00472640(b1, 1);
			}
			if (fcn_00507f10(hh, 2) >= 1.0) {
				fcn_00472640(b2, 0);
			} else {
				fcn_00472640(b2, 1);
			}
			if (fcn_00507f10(hh, 4) >= 1.0) {
				fcn_00472640(b4, 0);
			} else {
				fcn_00472640(b4, 1);
			}
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == b1) {
				k = 1;
			} else if (g_67d370 == b2) {
				k = 2;
			} else if (g_67d370 == b4) {
				k = 4;
			} else {
				continue;
			}
			if (hh == 0) {
				fcn_00526120(g_14b556c, 0);
			} else if (fcn_0058ff60(who, hh, k) != 0) {
				g_774654 = 1;
			}
		}
	}
	fcn_00471e30(h);
	fcn_0052a2d0();
	fcn_005305a0();
	fcn_00532ef0();
}
