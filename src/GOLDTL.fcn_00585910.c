/* SIZE 0x3cc */
typedef struct {
	char pad0[0xc];
	int xc;
	char pad10[0x3cc - 0x10];
} Screen;

/* SIZE 0x2f4 */
typedef struct {
	char pad0[0x18];
	int x18;
	char pad1c[0x6c - 0x1c];
	int x6c;
	char pad70[0x2f4 - 0x70];
} Ctl;

extern int g_6b7fac;
extern int g_772514;
extern char* g_77255c;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern float g_662cf8;
extern char* g_14b58e8;
extern char* g_14b58ec;
extern char* g_14b58f0;
extern char* g_14b58f4;
extern char* g_14b5f04;
extern char g_679060[];
extern char g_68b3f8[];
extern char g_6a93c0[];

#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern Win_1015f40 g_1015f40[0x60];

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

void* __cdecl fcn_004ec7d0(unsigned char*);
int __cdecl fcn_004ecf00(char*, int*, int*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_00534160(int, int, int, int);
int __cdecl fcn_00468df0(int, int, int, char*, int);
void __cdecl fcn_00469110(int, int);
int __cdecl fcn_00472250(int, int, int);
char* __cdecl fcn_004ee160(char*);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_005865f0(char*, int*, int);
int __cdecl fcn_00586800(char*, int*);
int __cdecl fcn_00586a80(char*, int*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00585030(int);

/* ADDRESS: GOLDTL 0x00585910 */
void __cdecl fcn_00585910(char* e)
{
	char text[0x100];
	char buf[0x100];
	int prev;
	int stamp;
	int frac;
	int owner;
	int item;
	int ids[9];
	int* p;
	int sel;
	int i;
	char* data;
	int* src;

	data = fcn_004ec7d0((unsigned char*) e);
	src = *(int**) (e + 0x65);
	prev = fcn_004ecf00(e, &owner, &frac, 0);
	stamp = g_6b7fac;
	memset(ids, -1, sizeof(ids));
	g_100f1dc = -1;
	ids[0] = fcn_00470820(0, 0, g_6a93c0);
	fcn_00473a90(0, 0);
	fcn_00471b60(ids[0]);
	fcn_004727a0(ids[0], 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(ids[0], 2);
	ids[1] = g_772514;
	fcn_004727a0(ids[0], 1);
	fcn_00519190(0x4039);
	fcn_004727a0(ids[0], 2);
	if (data == 0) {
		fcn_00519190(0x4051, 0x182);
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		} while (fcn_005373e0((void*) fcn_00585030, 0x677c7) != 0);
		fcn_00471e30(ids[0]);
		return;
	}
	fcn_0046f740(((Screen*) g_77255c)->xc / 2 - 0x18, 0x1e, 0x6c7, ids[1]);
	fcn_0046f740(((Screen*) g_77255c)->xc / 2 - 0x16, 0x20, *(int*) (data + 0x18c), ids[1]);
	ids[2] = fcn_004677e0((((Screen*) g_77255c)->xc - 0x32) / 2, 0x55, 0x32, 0, 0x64, 0x75, 0x42, g_772514);
	d2_SetElementValue(ids[2], 0, 0x64, (int) (*(float*) (src + 1) * g_662cf8));
	fcn_0051af00(buf, g_68b3f8, data + 0x30, data + 0x40);
	item = d2_ShowTxt(0, 0, buf, ids[1]);
	((Ctl*) g_1015ea0)[item].x18 = g_1015f40[ids[1]].xc;
	((Ctl*) g_1015ea0)[item].x6c = 1;
	fcn_00472900(item, 0x53);
	fcn_0051af00(buf, (char*) 0x403f, *(unsigned short*) (data + 0xa));
	item = d2_ShowTxt(0x12c, 0x64, buf, ids[1]);
	fcn_00472900(item, 0x53);
	((Ctl*) g_1015ea0)[item].x6c = 1;
	((Ctl*) g_1015ea0)[item].x18 = 0xc8;
	fcn_0051af00(buf, (char*) 0x4040, fcn_004ee160(e));
	item = d2_ShowTxt(0x12c, 0x82, buf, ids[1]);
	fcn_00472900(item, 0x53);
	((Ctl*) g_1015ea0)[item].x6c = 1;
	((Ctl*) g_1015ea0)[item].x18 = 0xc8;
	fcn_0051af00(buf, g_679060, g_14b58e8);
	ids[4] = fcn_00468df0(0x14a, 0xbe, 0xc5, g_14b5f04, ids[1]);
	fcn_00469110(ids[4], g_1015f40[ids[1]].xc / 3 - 0x14);
	fcn_00472900(ids[4], 0x54);
	fcn_0051af00(buf, g_679060, g_14b58e8);
	ids[5] = fcn_00468df0(10, 0x64, 0xc5, buf, ids[1]);
	fcn_00469110(ids[5], g_1015f40[ids[1]].xc / 3 - 0x14);
	fcn_00472900(ids[5], 0x54);
	fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0x68, *((unsigned char*) src + 8), 0x4df);
	fcn_0051af00(buf, g_679060, g_14b58ec);
	ids[6] = fcn_00468df0(10, 0x82, 0xc5, buf, ids[1]);
	fcn_00469110(ids[6], g_1015f40[ids[1]].xc / 3 - 0x14);
	fcn_00472900(ids[6], 0x54);
	fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0x86, *((unsigned char*) src + 9), 0x4df);
	fcn_0051af00(buf, g_679060, g_14b58f0);
	ids[7] = fcn_00468df0(10, 0xa0, 0xc5, buf, ids[1]);
	fcn_00469110(ids[7], g_1015f40[ids[1]].xc / 3 - 0x14);
	fcn_00472900(ids[7], 0x54);
	fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0xa4, *((unsigned char*) src + 10), 0x4df);
	fcn_0051af00(buf, g_679060, g_14b58f4);
	ids[8] = fcn_00468df0(10, 0xbe, 0xc5, buf, ids[1]);
	fcn_00469110(ids[8], g_1015f40[ids[1]].xc / 3 - 0x14);
	fcn_00472900(ids[8], 0x54);
	fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0xc2, *((unsigned char*) src + 11), 0x4df);
	fcn_004727a0(ids[0], 3);
	ids[3] = fcn_00472250(ids[0], 3, fcn_00519190(0x4049));
	do {
		sel = fcn_004ecf00(e, &owner, &frac, 0);
		fcn_004727a0(ids[0], 4);
		fcn_00519190(0x6811b0);
		if (sel != 0) {
			ids[2] = fcn_004677e0((((Screen*) g_77255c)->xc - 0x12c) / 2, 0x12, 0x12c, 0, 0x64, 0x75, 0x42, g_772514);
			if (sel == 1) {
				fcn_0051af00(text, (char*) 0x404b);
			} else if (sel == 2) {
				fcn_0051af00(text, (char*) 0x404c, owner * 2 + 0x9a8);
			} else if (sel == 3) {
				fcn_0051af00(text, (char*) 0x404d, owner + 0x4172);
			}
			item = d2_ShowTxt(0, 0, text, g_772514);
			((Ctl*) g_1015ea0)[item].x18 = ((Screen*) g_77255c)->xc;
			((Ctl*) g_1015ea0)[item].x6c = 1;
			fcn_00472900(item, 0x54);
			d2_SetElementValue(ids[2], 0, 0x64, (int) (*(float*) (src + 1) * g_662cf8));
		}
		if (sel != prev || g_6b7fac > (unsigned int) (stamp + 0x32)) {
			data = fcn_004ec7d0((unsigned char*) e);
			if (data == 0) {
				g_774654 = 1;
				fcn_005373e0((void*) fcn_00585910, 0x20007);
				fcn_00471e30(ids[0]);
				return;
			}
			fcn_004727a0(ids[0], 2);
			fcn_00519190(0x6811b0);
			fcn_0046f740(((Screen*) g_77255c)->xc / 2 - 0x18, 0x1e, 0x6c7, ids[1]);
			fcn_0046f740(((Screen*) g_77255c)->xc / 2 - 0x16, 0x20, *(int*) (data + 0x18c), ids[1]);
			ids[2] = fcn_004677e0((((Screen*) g_77255c)->xc - 0x32) / 2, 0x55, 0x32, 0, 0x64, 0x75, 0x42, g_772514);
			d2_SetElementValue(ids[2], 0, 0x64, (int) (*(float*) (src + 1) * g_662cf8));
			fcn_0051af00(buf, g_68b3f8, data + 0x30, data + 0x40);
			item = d2_ShowTxt(0, 0, buf, ids[1]);
			((Ctl*) g_1015ea0)[item].x18 = g_1015f40[ids[1]].xc;
			((Ctl*) g_1015ea0)[item].x6c = 1;
			fcn_00472900(item, 0x53);
			fcn_0051af00(buf, (char*) 0x403f, *(unsigned short*) (data + 0xa));
			item = d2_ShowTxt(0x12c, 0x64, buf, ids[1]);
			fcn_00472900(item, 0x53);
			((Ctl*) g_1015ea0)[item].x6c = 1;
			((Ctl*) g_1015ea0)[item].x18 = 0xc8;
			fcn_0051af00(buf, (char*) 0x4040, fcn_004ee160(e));
			item = d2_ShowTxt(0x12c, 0x82, buf, ids[1]);
			fcn_00472900(item, 0x53);
			((Ctl*) g_1015ea0)[item].x6c = 1;
			((Ctl*) g_1015ea0)[item].x18 = 0xc8;
			fcn_0051af00(buf, g_679060, g_14b58e8);
			ids[4] = fcn_00468df0(0x14a, 0xbe, 0xc5, g_14b5f04, ids[1]);
			fcn_00469110(ids[4], g_1015f40[ids[1]].xc / 3 - 0x14);
			fcn_00472900(ids[4], 0x54);
			fcn_0051af00(buf, g_679060, g_14b58e8);
			ids[5] = fcn_00468df0(10, 0x64, 0xc5, buf, ids[1]);
			fcn_00469110(ids[5], g_1015f40[ids[1]].xc / 3 - 0x14);
			fcn_00472900(ids[5], 0x54);
			fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0x68, *((unsigned char*) src + 8), 0x4df);
			fcn_0051af00(buf, g_679060, g_14b58ec);
			ids[6] = fcn_00468df0(10, 0x82, 0xc5, buf, ids[1]);
			fcn_00469110(ids[6], g_1015f40[ids[1]].xc / 3 - 0x14);
			fcn_00472900(ids[6], 0x54);
			fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0x86, *((unsigned char*) src + 9), 0x4df);
			fcn_0051af00(buf, g_679060, g_14b58f0);
			ids[7] = fcn_00468df0(10, 0xa0, 0xc5, buf, ids[1]);
			fcn_00469110(ids[7], g_1015f40[ids[1]].xc / 3 - 0x14);
			fcn_00472900(ids[7], 0x54);
			fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0xa4, *((unsigned char*) src + 10), 0x4df);
			fcn_0051af00(buf, g_679060, g_14b58f4);
			ids[8] = fcn_00468df0(10, 0xbe, 0xc5, buf, ids[1]);
			fcn_00469110(ids[8], g_1015f40[ids[1]].xc / 3 - 0x14);
			fcn_00472900(ids[8], 0x54);
			fcn_00534160(g_1015f40[ids[1]].xc / 3 + 0xa, 0xc2, *((unsigned char*) src + 11), 0x4df);
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			p = &ids[5];
			for (i = 0; i < 4; i++) {
				if (*p == g_67d370) {
					fcn_00471af0(ids[0], 0);
					fcn_005865f0(e, src, i);
					fcn_00471af0(ids[0], 1);
					g_67d370 = -1;
				}
				p++;
			}
			if (g_67d370 == ids[4]) {
				fcn_00471af0(ids[0], 0);
				fcn_00586800(e, src);
				fcn_00471af0(ids[0], 1);
			} else if (g_67d370 == ids[3]) {
				fcn_00471af0(ids[0], 0);
				if (fcn_00586a80(e, src) != 0) {
					g_774654 = 1;
				}
				fcn_00471af0(ids[0], 1);
			}
		}
	} while (fcn_005373e0((void*) fcn_00585910, 0x677c7) != 0);
	fcn_00471e30(ids[0]);
	fcn_00532ef0();
}
