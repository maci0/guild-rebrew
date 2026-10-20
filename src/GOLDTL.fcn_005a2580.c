#include <string.h>

/* Slot row passed to fcn_005ca560/fcn_005ca740. */
struct sel {
	char* who;           /* 0x00 */
	char pad4[0x0c];
	int x10;             /* 0x10 */
	int x14;             /* 0x14 */
	char pad18[0x18];
	int used;            /* 0x30 */
	char pad34[4];
};
// SIZE 0x38

/* Item record passed to fcn_004c5530. */
typedef struct Rec {
	char pad0[4];
	unsigned char kind;  /* 0x04 */
	char pad5[3];
	int x8;              /* 0x08 */
	int xc;              /* 0x0c */
	char pad10[0x18];
	int x28;             /* 0x28 */
	int x2c;             /* 0x2c */
	int x30;             /* 0x30 */
	short x34;           /* 0x34 */
	unsigned char x36;   /* 0x36 */
	char pad37[0x25];
	int x5c;             /* 0x5c */
	int x60;             /* 0x60 */
	char pad64[0x94];
} Rec;
// SIZE 0xf8

extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
extern unsigned short g_774970;
extern int g_774654;
extern int g_67d370;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_14ce8e0;
extern int g_100f1dc;
extern char g_7f4ca4[];

int __cdecl fcn_00470820(int a, int b, char* name);
void __cdecl fcn_00471b60(int h);
void __cdecl fcn_004727a0(int h, int page);
void __cdecl fcn_005340f0(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_004f7120(int id, char* rec, int* out1, int* out2, int* idx);
void __cdecl fcn_0046f2c0(int a, int b);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_005ca560(struct sel* s);
void __cdecl fcn_005ca740(int x, int y, int a, int b, struct sel* s, int c);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_005c91c0(char* buf, int x, int y, int a, int b);
char* __cdecl fcn_005463a0(int a, int b, int c);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_00472250(int h, int a, int b);
void __cdecl fcn_004c5530(Rec* r);
int __cdecl fcn_005373e0(void* fn, int id);
void __cdecl fcn_00471e30(int h);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x005a2580 */
void __cdecl fcn_005a2580(char* a0, char* a1, char* a2)
{
	struct sel sel[3];
	Rec rec;
	char buf[512];
	int seen[3];
	int vals[3];
	int idx[3];
	int out1;
	int out2;
	int h;
	int changed;
	int y;
	int x;
	int rc;
	int line;
	int found;
	int j;
	char* p;
	char* e;

	y = -1;
	seen[0] = -1;
	seen[1] = -1;
	seen[2] = -1;
	h = 0;
	memset(sel, 0, sizeof(sel));
	vals[0] = 0;
	vals[1] = 0;
	vals[2] = 0;
	h = fcn_00470820(0, 0, "locations\\Wirtshaus\\DUNKLEECKE");
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_00473a90(0, 0);
	memset(sel, 0, sizeof(sel));
	changed = 1;
	do {
		p = a2 + 0x1c;
		for (j = 0; j < 3; j++) {
			if (fcn_004f7120(*(int*) p, (*(unsigned short*) (a0 + 0x27)) * 540 + 0x7f4ca0,
				&out1, &out2, &idx[j])) {
				if (seen[j] != *(int*) p) {
					changed = 1;
				}
				seen[j] = *(int*) p;
				sel[j].who = (char*) ((out2 & 0xffff) * 540 + 0x7f4ca0);
				vals[j] = out1;
			} else if (seen[j] != -1) {
				changed = 1;
				sel[j].who = 0;
				seen[j] = -1;
				vals[j] = 0;
			}
			p++;
		}
		if (changed) {
			fcn_004727a0(h, 1);
			fcn_0046f2c0(g_772514, 1);
			fcn_00519190(0x18a3);
			x = *(int*) (g_77255c + 0xc) / 2;
			y = (x - *(short*) (g_772500 + 0x1ebd8)) - 0x28;
			line = 0x46;
			for (j = 0; j < 3; j++) {
				sel[j].x10 = y;
				sel[j].x14 = line - 0x1e;
				sel[j].used = (sel[j].who != 0);
				fcn_005ca560(&sel[j]);
				fcn_005ca740(sel[j].x10, sel[j].x14, g_772514, 0x54, &sel[j], 1);
				if (seen[j] != -1) {
					fcn_0051af00(buf, 0x18a5, *(int*) (idx + j) * 5 + 0x13fd, vals[j]);
				} else {
					fcn_0051af00(buf, 0x18a6);
				}
				fcn_005c91c0(buf, x, line, 0xf0, 0x54);
				line += 0x69;
			}
			found = 0;
			changed = 0;
			y = -1;
			for (e = fcn_005463a0(1, 0, 0x74); e != 0; e = fcn_005462a0()) {
				if (*(int*) (e + 0xb0) == *(int*) (a0 + 1)) {
					found = 1;
					break;
				}
			}
			fcn_004727a0(h, 2);
			fcn_00519190(0x6811b0);
			if (found) {
				fcn_00519190(0x18a8);
			} else if (*(int*) (a2 + 0x28) < g_7f4c00) {
				rc = fcn_00472250(h, 2, fcn_00519190(0x18a7));
				y = rc;
			}
		}
		if (g_100f1dc != -1 && g_67d370 == y) {
			memset(&rec, 0, sizeof(rec));
			rec.kind = 0x74;
			rec.x36 = 2;
			rec.x8 = *(int*) (g_7f4ca4 + (*(unsigned short*) &g_774970) * 540 - 4);
			rec.xc = *(int*) (a0 + 1);
			rec.x28 = g_7f4c00;
			rec.x2c = g_7f4c04;
			rec.x30 = g_7f4c08;
			rec.x34 = g_7f4c0c;
			rec.x5c = *(int*) (a0 + 1);
			rec.x60 = *(int*) (a1 + 2);
			fcn_004c5530(&rec);
			g_774654 = 1;
		} else if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0(fcn_005a2580, 0x677c7) != 0);
	fcn_00471e30(h);
}
#pragma optimize("", on)
