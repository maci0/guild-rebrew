// FUNCTION: GOLDTL 0x005b37d0

typedef struct
{
	char pad0[0x27c];
	int x27c;
	char pad280[0x3cc - 0x280];
} Win;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern int g_14ce8e0;
extern int g_774654;
extern int g_772514;
extern int g_67a370;
extern int g_6b8300;
extern char* g_1042320;
extern char g_1052a40[];
extern int g_773d70;
extern int g_773d8c;
extern char s_6ab7e4[];
extern char s_6ab7cc[];
extern char s_6ab7ac[];
extern char s_6ab790[];
extern char s_6ab778[];
extern char s_6ab764[];
extern char s_6ab748[];
extern char s_6ab728[];
extern char s_6ab710[];
extern char s_6ab6f8[];
extern char s_6ab6e4[];
extern char s_6ab6d0[];

int __cdecl fcn_0046e940(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0045a230(int, int, int);
int __cdecl fcn_00459d50(int);
int __cdecl fcn_00459d90(int, int);
int __cdecl fcn_004346f0(char*);
int __cdecl fcn_00402ba0(int, int);
void __cdecl fcn_005b0f00(Win*);
void __cdecl fcn_0046f280(int);

void __cdecl fcn_005b37d0(void)
{
	Win* w;
	int h;
	int total;
	int n;
	int v;
	char* p;

	h = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414);
	fcn_00472900(((Win*)g_1015f40)[h].x27c, 0x54);
	while (fcn_005373e0((void*) fcn_005b37d0, 0x657c7) != 0) {
		w = &((Win*)g_1015f40)[h];
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		g_772514 = h;
		fcn_00519190((int) "$C");
		fcn_00519190((int) s_6ab7e4);
		total = fcn_0045a230(0x1ff, 0x80, 0);
		fcn_00519190((int) s_6ab7cc, total);
		v = fcn_0045a230(0x1ff, 1, 0);
		total += v;
		fcn_00519190((int) s_6ab7ac, v);
		v = fcn_0045a230(0x1ff, 2, 0);
		total += v;
		fcn_00519190((int) s_6ab790, v);
		v = fcn_00459d50(*(int*) (((char*)g_67a370) + 0xb0));
		total += v;
		fcn_00519190((int) s_6ab778, v);
		v = fcn_00459d90(g_6b8300, 1);
		total += v;
		fcn_00519190((int) s_6ab764, v);
		v = fcn_0045a230(0x1ff, 0x28, 0);
		total += v;
		fcn_00519190((int) s_6ab748, v);
		n = 0;
		for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
			n += fcn_004346f0(p);
		}
		fcn_00519190((int) s_6ab728, n);
		fcn_00519190((int) s_6ab710, total);
		fcn_00519190((int) s_6ab6f8, fcn_00402ba0(-1, 1));
		fcn_00519190((int) s_6ab6e4, g_773d70);
		fcn_00519190((int) s_6ab6d0, g_773d8c);
		fcn_005b0f00(w);
	}
	fcn_0046f280(h);
}
