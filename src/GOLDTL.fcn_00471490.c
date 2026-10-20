#include "client_types.h"

extern Obj_1038140 g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern int g_1040490;
extern int g_1040494;
extern int g_67d370;
extern int g_67d378;
extern int g_7725ec;
extern int g_772604;
extern char s_67d7a0[];

void __cdecl fcn_0041d9e0(char* text);
void __cdecl fcn_00465e60(char* base);
void __cdecl fcn_00466550(int idx, int surf);
void __cdecl fcn_00467920(int idx, int surf);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, char* surf, char* text, int flags);
void __cdecl fcn_0046dff0(int idx, char* surf);
int __cdecl fcn_00472050(int slot, int* w, int* h);
void __cdecl fcn_00472880(int idx);
int __cdecl fcn_004767f0(int x, int y, int w, int h, char* src, int sx, int sy, char* t);
void __cdecl fcn_0047a040(int left, int top, int right, int bottom);
void __cdecl fcn_0047c560(int a, int b, char* surf);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047ccd0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cd70(int idx, int surf);

/* ADDRESS: GOLDTL 0x00471490 */
void __cdecl fcn_00471490(int k)
{
	int saved;
	char* base;
	int v;
	int flags;
	int ybase;
	int col;
	int* rows;
	char* win;
	int row;
	char** pp;
	int w;
	int right;
	int h;
	char* surf;
	char* obj;
	int sx;
	int sy;
	int top;
	int oh1;
	int oh2;

	saved = g_772604;
	base = ((char*) g_1038140) + k * 0x2bc;
	if (*(int*) (base + 0x190) == 0) {
		return;
	}
	if (*(int*) (base + 0x198) == 0) {
		return;
	}
	fcn_00465e60(base);
	ybase = 0;
	pp = (char**) (base + 0x1ac);
	do {
		surf = pp[-2];
		if ((*(unsigned char*) surf & 0x10) == 0) {
			fcn_0041d9e0(s_67d7a0);
			return;
		}
		fcn_004767f0(0, 0, *(int*) (pp[0] + 4), *(int*) (pp[0] + 8), *(int*) (pp[0] + 0x20), 0, 0, surf);
		rows = (int*) (base + 4);
		for (row = 0; row < *(int*) (base + 0x184); rows++, row++) {
			win = (char*) &g_1015f40[*rows];
			oh2 = *(int*) (win + 8);
			oh1 = *(int*) (win + 4);
			*(int*) (win + 8) = ybase + oh2;
			fcn_0046dff0(*rows, surf);
			*(int*) (win + 4) = oh1;
			*(int*) (win + 8) = oh2;
			for (col = 0; col < *(int*) (win + 0x2c); col++) {
				obj = g_1015ea0 + ((int*) *(char**) (win + 0x28))[col] * 0x2f4;
				sx = *(int*) (obj + 0x10) - *(int*) (base + 0x188);
				sy = ybase - *(int*) (base + 0x18c) + *(int*) (obj + 0x14);
				if (*(int*) (obj + 4) != 0) {
					v = *(int*) (obj + 0x34) + ybase;
					if (v >= 0x100) {
						v = 0x100;
					}
					right = *(int*) (obj + 0x2c);
					if (right >= 0x100) {
						right = 0x100;
					}
					top = *(int*) (obj + 0x30) + ybase;
					fcn_0047a040(*(int*) (obj + 0x28) < 0 ? 0 : *(int*) (obj + 0x28),
					             top <= 0 ? 0 : top, right, v);
					switch (*(int*) (obj + 0x20)) {
					case 1:
						if (*(int*) (obj + 0x3c)) {
							fcn_0047ccd0(sx, sy, (int) surf, *(char**) (obj + 0xc), 0);
						} else {
							fcn_0047cba0(sx, sy, (int) surf, *(char**) (obj + 0xc), 0);
						}
						break;
					case 4:
						fcn_0047cd70(*(int*) (obj + 0x88), (int) surf);
						break;
					case 5:
					case 8:
						if (*(int*) (obj + 0x1d0) & 2) {
							if (g_1015ea0 + g_67d370 * 0x2f4 == obj || *(int*) (obj + 0x38) != 0) {
								if (*(int*) (obj + 0x1d0) & 1) {
									*(int*) (obj + 0x3c) = 1;
								}
							} else {
								if (*(int*) (obj + 0x1d0) & 1) {
									*(int*) (obj + 0x3c) = 0;
								}
							}
						}
						if (*(int*) (obj + 0x3c)) {
							fcn_0047ccd0(sx, sy, (int) surf, *(char**) (obj + 0xc), *(int*) (obj + 0x88));
						} else {
							fcn_0047cba0(sx, sy, (int) surf, *(char**) (obj + 0xc), *(int*) (obj + 0x88));
						}
						if (*(unsigned char*) (obj + 0x8c) == 0) {
							break;
						}
						if (*(int*) (obj + 0x84) != 0) {
							fcn_00472880(*(int*) (obj + 0x84));
						}
						flags = 0;
						if (*(int*) (obj + 0x3c)) {
							flags = 2;
						} else if (*(int*) (obj + 0x60)) {
							flags = 1;
						}
						if (*(int*) (obj + 0x6c)) {
							flags |= 8;
						}
						if (*(int*) (obj + 0x70)) {
							flags |= 0x10;
						}
						fcn_00472050(*(int*) obj, &w, &h);
						if (*(int*) (obj + 0x1dc) != -1) {
							sx = *(int*) (obj + 0x1dc) - *(int*) (base + 0x188);
							top = *(int*) (obj + 0x18);
						} else {
							sx = w - *(int*) (base + 0x188) + *(int*) (obj + 0x10) + 6;
							top = w * 3 + *(int*) (obj + 0x18);
						}
						if (*(int*) (obj + 0x1e0) != -1) {
							sy = ybase - *(int*) (base + 0x18c) + *(int*) (obj + 0x1e0);
						} else {
							sy = ybase - *(int*) (base + 0x18c) + *(int*) (obj + 0x14) - 1;
						}
						fcn_0046bd20(sx, sy, top, *(int*) (obj + 0x1c), surf,
						             obj + 0x8c, flags);
						fcn_00472880(flags);
						break;
					case 0x41:
						fcn_00466550(*(int*) (obj + 0x88), (int) surf);
						break;
					case 0x43:
						if (*(int*) (obj + 0x24) > 0) {
							fcn_0047a040(0, 0, g_1040494, g_1040490);
							fcn_00472880(*(int*) (obj + 0x84));
							flags = 0;
							if (*(int*) (obj + 0x3c)) {
								flags = 2;
							} else if (*(int*) (obj + 0x60)) {
								flags = 1;
							}
							if (*(int*) (obj + 0x6c)) {
								flags |= 8;
							}
							if (*(int*) (obj + 0x70)) {
								flags |= 0x10;
							}
							fcn_0046bd20(sx, sy, *(int*) (obj + 0x18), *(int*) (obj + 0x1c),
							             surf, *(char**) (obj + 0x88), flags);
							fcn_00472880(g_67d378);
						}
						break;
					case 0x45:
						sx = *(int*) (obj + 0x10);
						sy = *(int*) (obj + 0x14);
						*(int*) (obj + 0x10) = sx - *(int*) (base + 0x188);
						*(int*) (obj + 0x14) = ybase - *(int*) (base + 0x18c) + sy;
						fcn_00467920(*(int*) obj, (int) surf);
						*(int*) (obj + 0x10) = sx;
						*(int*) (obj + 0x14) = sy;
						break;
					}
				}
				fcn_0047a040(0, 0, g_1040494, g_1040490);
			}
		}
		fcn_0047c560(saved, g_7725ec, surf);
		ybase -= 0x100;
		pp++;
	} while (ybase > -0x200);
}
