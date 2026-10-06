// FUNCTION: GOLD 0x0057df10
// FUNCTION: GOLDTL 0x5865f0

#include <string.h>

// SIZE 0xf8
#include "client_types.h"
struct msg {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	pos14_7f4c00 when;
	unsigned char code;
	char pad37[0x21];
	int who;
	int other;
	char pad60[8];
	int delay;
	char pad6c[0x8c];
};

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

int __cdecl fcn_004ecf00(char*, int*, int*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c5530(struct msg*);

int __cdecl fcn_005865f0(char* e, int* who, int kind)
{
	int s;
	int yes;
	int no;
	int b;
	struct msg m;
	int h;
	int ok;

	ok = 1;
	if (fcn_004ecf00(e, &s, &b, 0) != 0) {
		ok = 0;
	}
	if (kind == 3) {
		ok = 0;
	}
	h = fcn_00470820(0, 0, "Locations\\Domizil\\skill");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x4045, kind + 0x4172);
	fcn_00519190(kind + 0x4176);
	if (ok) {
		fcn_00519190(0x4046, 0x182);
	}
	fcn_004727a0(h, 2);
	s = fcn_00519190(0x4047);
	yes = fcn_00472250(h, 2, s);
	no = fcn_00472250(h, 2, s + 1);
	fcn_00472640(yes, ok);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == yes) {
				memset(&m, 0, sizeof(m));
				m.kind = 0x97;
				m.code = 1;
				m.owner = ((struct house*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].owner;
				m.target = *(int*) (e + 1);
				m.when = g_7f4c00;
				m.who = *who;
				m.delay = fcn_0042e410(0x5a0) + 1000;
				m.other = kind;
				fcn_004c5530(&m);
				g_774654 = 1;
			} else if (g_67d370 == no) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_005865f0, 0x677c7) != 0);
	fcn_00471e30(h);
	return 1;
}
