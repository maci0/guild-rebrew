#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_14ac864;
extern int g_67d370;
extern int g_772514;
extern int g_774654;
extern pos14_7f4c00 g_7f4c00;

// SIZE 0xf8
typedef struct {
	int f0;
	char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
} Msg_5d5930;

// SIZE 0x38
typedef struct {
	int p0;
	int f4;
	char pad8[8];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	int x30;
	unsigned int x34;
} Rec_5d5930;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004f6470(int, int*, unsigned short);
int __cdecl fcn_004f61c0(int*, int*, int*, unsigned short);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5530(Msg_5d5930*);
int __cdecl fcn_00470820(int, int, char*);
int __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0046e830(int, int, int, int, int);
void __cdecl fcn_005ca560(Rec_5d5930*);
void __cdecl fcn_005ca740(int, int, int, int, Rec_5d5930*, int);
void __cdecl fcn_005c9160(char*, int, int, int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00525f60(int*, int);
int __cdecl fcn_005d5670(unsigned char*, unsigned char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0051af00(char*, int, ...);

/* ADDRESS: GOLDTL 0x005d5930 */
int __cdecl fcn_005d5930(unsigned char* p, int* q)
{
	Rec_5d5930 recs[0x20];
	char buf[0x200];
	int c[0x20];
	int ids[0x20];
	char text[0x40];
	int b[0x20];
	Msg_5d5930 m;
	pos14_7f4c00 pos;
	int cnt;
	int dlg;
	char* e;
	char* obj;
	int n;
	int i;
	int y;
	int k;
	int result;
	int* rp;
	Rec_5d5930* r;

	if (*(unsigned char*) (p + 2) != 6 && *(unsigned char*) (p + 2) != 7) {
		e = fcn_00508e40(q[0x85]);
		if (e == 0) {
			return 0x60;
		}
		b[0] = fcn_004f6470(*(int*) (e + 4), ids, *(unsigned short*) p);
		if (b[0] >= gm_RandomMod(8)) {
			pos = g_7f4c00;
			fcn_00500bb0(&pos, 0x60, 0, 0);
			memset(&m, 0, sizeof(m));
			m.fc = *(int*) (p + 4);
			m.b4 = 0x45;
			m.b36 = 2;
			m.f8 = *(int*) (p + 4);
			m.pos = g_7f4c00;
			m.f58 = *(int*) (p + 4);
			m.f5c = *(int*) (e + 4);
			fcn_004c5530(&m);
			return 0x10;
		} else {
			fcn_004c54c0(*(int*) (p + 4), *(int*) (e + 4), -0x1a, 1);
			return 0x10;
		}
	}
	dlg = fcn_00470820(0, 0, "privillegien\\erpressung");
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x1d55);
	d2_SetForm(dlg, 2);
	d2_SetForm(dlg, 3);
	fcn_0046e830(-1, -1, g_772514, g_772514, 0x767);
	n = fcn_004f61c0(ids, b, c, *(unsigned short*) p);
	cnt = 0;
	for (i = 0; i < n; i++) {
		obj = fcn_00508e40(ids[i]);
		if (obj != 0) {
			recs[cnt].p0 = (int) obj;
			recs[cnt].x2c = c[i];
			recs[cnt].x34 = b[i];
			fcn_005ca560(&recs[cnt]);
			recs[cnt].x30 = 1;
			cnt++;
		}
	}
	d2_SetForm(dlg, 2);
	if (cnt != 0) {
		if (cnt > 0) {
			y = 0xa;
			k = cnt;
			r = recs;
			do {
				fcn_0051af00(text, (int) "%i (%i) %s", r->x2c, r->x34, (r->x2c != 1) + 0x1748);
				r->x10 = 0x32;
				r->x14 = y;
				fcn_005ca740(0x32, y, g_772514, 0x56, r, 1);
				fcn_005c9160(text, *(int*) (g_772514 * 0x3cc + 0x1015f4c) - 0xf, y + 0x2d, 200, 0x55);
				r++;
				y += 0x69;
			} while (--k != 0);
		}
	} else {
		fcn_00519190(0x1d50);
	}
	result = 0x20;
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			for (i = 0, rp = (int*) recs; i < cnt; i++, rp += 0xe) {
				if (g_67d370 == rp[1]) {
					if (fcn_00525f60(q, 2) != 0) {
						if ((*(unsigned int*) (recs[i].p0 + 0x1c8) & 0x200) != 0) {
							fcn_0051af00(buf, 0x1d52, *(unsigned short*) recs[i].p0);
							fcn_00526120(buf, 0);
						} else if (recs[i].x34 < 3) {
							fcn_00526120(*(char**) 0x14ac864, 0);
						} else {
							obj = fcn_00508e40(ids[i]);
							if (fcn_005d5670((unsigned char*) q, (unsigned char*) obj) != 0) {
								g_774654 = 1;
							}
							result = 0x92;
						}
					}
					break;
				}
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d5930, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
