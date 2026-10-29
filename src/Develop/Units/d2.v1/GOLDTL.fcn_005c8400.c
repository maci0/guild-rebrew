

typedef struct {
	int f0;
	int pad4[2];
	int fc;
	int pad10[3];
} Tab5c84;
// SIZE 0x1c

typedef struct {
	int bar;
	int btn;
	char* e;
} Line5c84;
// SIZE 0xc

typedef struct {
	char pad[0x178];
	int f178;
	char pad17c[0xa0];
} Ent5c84;
// SIZE 0x21c

extern Tab5c84 g_776aa0[16];
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern char g_6ac820[];
extern char g_6811b0[];
extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005a5440(int, Tab5c84*, int, int, int);
void __cdecl fcn_0046f280(int);
void __cdecl fcn_0046b2b0(int);
int __cdecl fcn_0050d5d0(int, int, char**);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int x, int y, int owner, int other, int arg5, int* id2, int* id1, int* id3);
int __cdecl fcn_0046f740(int x, int y, int id, int win);
int __cdecl fcn_0046f100(int x, int y, int cx, int cy, int a5, int win);
char* __cdecl gm_SearchTable67(int);

int __cdecl fcn_005c8400(void)
{
	int i;
	int id2;
	int n;
	int id1;
	int id3;
	char* list[9];
	Line5c84 lines[9];
	int h;
	int k;
	int cy;
	char* r;

	id1 = -1;
	id2 = -1;
	id3 = -1;
	for (k = 0; k < 16; k++) {
		g_776aa0[k].f0 = -1;
		g_776aa0[k].fc = 0;
	}
	for (k = 0; k < 9; k++) {
		lines[k].bar = -1;
		lines[k].btn = -1;
		lines[k].e = 0;
	}
	h = fcn_00470820(0, 0, g_6ac820);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 2);
	fcn_00519190(0x1f3e);
	d2_SetForm(h, 4);
	fcn_00519190(0x1f3f);
	d2_SetForm(h, 5);
	fcn_00519190(0x1f40);
	d2_SetForm(h, 1);
	fcn_005a5440(((Ent5c84*)g_7f4ca0)[g_774970].f178, g_776aa0, h, 1, 0);
	for (k = 0; k < 9; k++) {
		if (lines[k].bar != -1) {
			fcn_0046f280(lines[k].bar);
			fcn_0046b2b0(lines[k].btn);
			lines[k].bar = -1;
			lines[k].btn = -1;
			lines[k].e = 0;
		}
	}
	fcn_0050d5d0(g_774970, 0, list);
	n = fcn_0050d5d0(g_774970, 0, list);
	d2_SetForm(h, 3);
	fcn_00519190((int) g_6811b0);
	if (n >= 9) {
		fcn_00519190(0x18cb);
	}
	cy = *(short*) (g_772500 + 0x269d8);
	d2_SetForm(h, 0);
	fcn_00533f40(0x215, 0x16b, g_772514, fcn_00472830(h, 3), 0x6a, &id2, &id1, &id3);
	for (i = 0; i < n; i++) {
		d2_SetForm(h, 3);
		lines[i].btn = fcn_0046f740((*(int*) (g_77255c + 0xc) - cy) >> 1, i * 0x6a, 0x75a, g_772514);
		lines[i].bar = fcn_0046f100((*(int*) (g_77255c + 0xc) - cy) >> 1, i * 0x6a + 4, cy, 0x62, 0x10, g_772514);
		lines[i].e = list[i];
		/* both fields through one symbol: c2 chains the two stores, which issues the bar store first */
		*(int*) (((char*)g_1015f40) + lines[i].bar * 0x3cc + 0x28c) = 0x56;
		*(int*) (((char*)g_1015f40) + lines[i].bar * 0x3cc + 0x18) = 0x10;
		r = gm_SearchTable67(*(int*) (lines[i].e + 0xac));
		if (r != 0) {
			fcn_00519190(0x1f41, r, *(int*) (lines[i].e + 0xb4), *(int*) (lines[i].e + 0xc0), lines[i].e + 0xc4);
		}
	}
	return h;
}
