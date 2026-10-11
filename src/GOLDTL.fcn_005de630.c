// FUNCTION: GOLD 0x5d2100
// FUNCTION: GOLDTL 0x005de630

#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	int ids[8];
	int pad3c[5];
} Req;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char b2;
	char pad3;
	int f4;
	char pad8[0x15e];
	unsigned char b166;
	char pad167[0xb5];
} House;

extern __int64 g_666018;
extern char* g_14a5590;
extern char g_7f4ca0[];
extern int g_664398[];

unsigned char* __cdecl fcn_005cd440(Req*, char*, int, int);
unsigned char* __cdecl fcn_00508e40(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c54c0(int, int, int, int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005de630(House* obj, int* arg)
{
	House* picks[3];
	Req req;
	char text[0x800];
	char text2[0x200];
	House* e;
	int start;
	int step;
	int n;
	int i;

	if (obj->b2 == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		req.f14 = 3;
		req.size = 0x400;
		req.kind = 6;
		req.cd = g_666018;
		e = (House*) fcn_005cd440(&req, g_14a5590, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = (House*) fcn_00508e40(arg[1]);
		if (e == 0) {
			return 0;
		}
	}
	start = gm_RandomMod(0x300);
	step = g_664398[gm_RandomMod(0x10)];
	n = 3;
	do {
		if (((House*)g_7f4ca0)[start].id != 0xffff && ((House*)g_7f4ca0)[start].b166 && &((House*)g_7f4ca0)[start] != obj &&
			&((House*)g_7f4ca0)[start] != e) {
			n--;
			picks[n] = &((House*)g_7f4ca0)[start];
		}
		start = (start + step) % 0x300;
	} while (n != 0);
	for (i = 0; i < 3; i++) {
		fcn_004c54c0(e->f4, picks[i]->f4, gm_RandomMod(0x20) + 0x14, 1);
	}
	fcn_004ff210(e->id, -0x32 - gm_RandomMod(0x40));
	if (e->b2 == 6 || e->b2 == 7) {
		fcn_0051af00(text, 0x100d, picks[0]->id, picks[0]->id, picks[1]->id, picks[2]->id);
		fcn_00545d40(e->f4, -1, text, 1, 0x5fb, 0);
	}
	if (picks[0]->b2 == 6 || picks[0]->b2 == 7) {
		fcn_0051af00(text, 0x100e, e->id, picks[1]->id, picks[2]->id);
		fcn_00545d40(picks[0]->f4, -1, text, 1, 0x5fb, 0);
	}
	if (picks[1]->b2 == 6 || picks[1]->b2 == 7) {
		fcn_0051af00(text, 0x100f, e->id, picks[0]->id, picks[2]->id);
		fcn_00545d40(picks[1]->f4, -1, text, 1, 0x5fb, 0);
	}
	if (picks[2]->b2 == 6 || picks[2]->b2 == 7) {
		fcn_0051af00(text, 0x100f, e->id, picks[0]->id, picks[1]->id);
		fcn_00545d40(picks[2]->f4, -1, text, 1, 0x5fb, 0);
	}
	arg[4] = 1;
	if (obj->b2 == 6) {
		fcn_0051af00(text2, 0x10a1, e->id, picks[0]->id, picks[1]->id, picks[2]->id);
		fcn_0051af00(text, 0xfe8, text2);
		fcn_005dbe90(text);
	}
	return 1;
}
