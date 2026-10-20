#include <stdio.h>

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
} fcn_0046a110_Rect;
/* SIZE 0x10 */

extern void* g_6b5de0;
extern int g_1015ea0;
extern int g_1015ea4;
extern int g_1040490;
extern int g_1040494;
extern int g_1052be4;
extern int g_1052bec;
extern int g_14ce8d4;
extern int g_67d370;
extern int g_67d378;
extern int g_67d398;
extern int g_77250c;
extern int g_77251c;
extern int g_772524;
extern int g_772540;
extern int g_772548;
extern int g_772568;
extern int g_772570;
extern int g_772574;
extern int g_7725a0;
extern int g_7725a4;
extern int g_7725a8;
extern int g_7725d0;
extern float g_6628a0;
extern float g_6628a8;
extern double g_6629c8;
extern double g_662c38;
extern float g_67d3c0[];

void __cdecl fcn_0047a090(void);
void __cdecl fcn_0047a040(int left, int top, int right, int bottom);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cbf0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047ccd0(int x, int y, int surf, char* font, int c);
int __cdecl fcn_0047cc80(int x, int y, int surf, void* s, int idx, float scale, int tint);
void* __cdecl fcn_00466190(int idx);
int __cdecl fcn_00465950(const char* name);
void __cdecl fcn_004663e0(char* f, int surf);
void __cdecl fcn_00469fd0(char* e);
int __cdecl fcn_00473a10(int x, int y);
void __cdecl fcn_0047c560(int a, int b, int c);
void __cdecl fcn_004732c0(void);
void __cdecl fcn_00472880(int font);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);
void __cdecl fcn_00479cc0(int a, int b, int c, int d, char* e);
void __cdecl fcn_00467920(int a0, int a1);
void __cdecl fcn_00468e40(int a0, int a1);
void __cdecl fcn_00466550(int idx, int surf);
void __cdecl fcn_0046dff0(int a0, int a1);
void __cdecl fcn_00469320(int idx, int surf);
void __cdecl fcn_0047cd70(int i, int tex);
void __cdecl fcn_00472050(int a, int* w, int* h);

/* ADDRESS: GOLDTL 0x0046a110 */
void __cdecl fcn_0046a110(int a1)
{
	fcn_0046a110_Rect screen;
	fcn_0046a110_Rect clip[2];
	float uv[2];
	char* ent;
	char* tab;
	char* child;
	char* e2;
	char* font;
	fcn_0046a110_Rect* rects;
	char buf[40];
	int i;
	int n;
	int dx;
	int dy;
	int left;
	int right;
	int top;
	int bottom;
	int t;
	int flags;
	int v;
	int y2;
	int w2;
	int h2;
	float f;

	i = 0;
	g_7725a0 = 0;
	g_7725a4 = 0;
	fcn_0047a090();
	screen.left = 0;
	screen.top = 0;
	screen.right = g_1040494;
	screen.bottom = g_1040490;
	uv[0] = 0.0f;
	uv[1] = 1.0f;
	(*(void (__cdecl **)(void*, void*)) (*(int*) g_6b5de0 + 0xa0))(g_6b5de0, &screen);
	if (a1) {
		n = 0;
		rects = 0;
	}
	else {
		if (g_1052be4) {
			clip[0].left = 0;
			clip[0].top = 0;
			clip[0].right = g_1040494;
			clip[0].bottom = g_1052be4;
		}
		n = (g_1052be4 != 0);
		if (g_1052bec < g_1040490 - g_1052be4) {
			clip[n].left = 0;
			clip[n].top = g_1052bec + g_1052be4;
			clip[n].right = g_1040494;
			clip[n].bottom = g_1040490;
			n++;
		}
		if (!n)
			goto label_46a1f2;
		rects = clip;
	}
	(*(void (__cdecl **)(void*, int, void*, int, int, float, int)) (*(int*) g_6b5de0 + 0x90))(g_6b5de0, n, rects, 1, 0, 1.0f, 0);
label_46a1f2:
	if (g_7725a8) {
		fcn_0047a040(0, 0, g_1040494, g_1040490);
		fcn_0047cba0(0, 0, g_77250c, (char*) g_7725a8, 0);
	}
	tab = (char*) g_772540;
	if (!*(char**) tab)
		goto label_46aadd;
	for (;;) {
		if (i >= 0x3fe)
			goto label_46aadd;
		ent = *(char**) (tab + i * 4);
		if ((!*(int*) (ent + 0x50) || !*(int*) (*(int*) (ent + 0x50) + 0x198))
		    && *(int*) (ent + 4) && !*(int*) (ent + 0x48)) {
			dx = *(int*) (ent + 0x10);
			dy = *(int*) (ent + 0x14);
			left = *(int*) (ent + 0x28);
			right = *(int*) (ent + 0x2c);
			top = *(int*) (ent + 0x30);
			bottom = *(int*) (ent + 0x34);
			child = *(char**) (ent + 0x40);
			if (child) {
				do {
					e2 = (char*) (g_1015ea0 + *(int*) (child + 0x27c) * 0x2f4);
					if (left < *(int*) (e2 + 0x28))
						left = *(int*) (e2 + 0x28);
					if (*(int*) (e2 + 0x2c) < right)
						right = *(int*) (e2 + 0x2c);
					if (top < *(int*) (e2 + 0x30))
						top = *(int*) (e2 + 0x30);
					if (*(int*) (e2 + 0x34) < bottom)
						bottom = *(int*) (e2 + 0x34);
					child = *(char**) (e2 + 0x40);
				} while (child);
			}
			if (g_7725a4 && (*(int*) (ent + 0x40) != g_7725a0 || !*(int*) (g_7725a4 + 0x40))) {
				fcn_0047a040(0, 0, g_1040494, g_1040490);
				fcn_00469fd0((char*) g_7725a4);
				g_7725a0 = *(int*) (ent + 0x40);
				g_7725a4 = 0;
			}
			fcn_0047a040(left, top, right, bottom);
			switch (*(int*) (ent + 0x20)) {
			case 1:
				if (*(int*) (ent + 0x1e4) != -1) {
					font = (char*) fcn_00466190(*(int*) (ent + 0x1e4));
					fcn_0047cba0(*(int*) (ent + 0x1e8) + dx, *(int*) (ent + 0x1ec) + dy,
					             g_77250c, font, g_772568);
				}
				if (*(int*) (ent + 0x1d0) & 2) {
					if ((char*) (g_1015ea0 + g_67d370 * 0x2f4) == ent || !*(int*) (ent + 0x38)) {
						if (!*(int*) (ent + 0x4c)) {
							if (*(int*) (ent + 0x1d0) & 1)
								*(int*) (ent + 0x3c) = 1;
						}
						else if (*(int*) (ent + 0x1d0) & 1)
							*(int*) (ent + 0x3c) = 0;
					}
					else if (*(int*) (ent + 0x1d0) & 1)
						*(int*) (ent + 0x3c) = 0;
				}
				v = *(int*) (ent + 0x80);
				if (v != 0 && v != 1 && v != -1) {
					f = g_67d3c0[v];
					if (*(int*) (ent + 0x3c))
						fcn_0047cc80(dx, dy, g_77250c, *(void**) (ent + 0xc), 0, f, 1);
					else
						fcn_0047cc80(dx, dy, g_77250c, *(void**) (ent + 0xc), 0, f, 0);
				}
				if (!*(int*) (ent + 0x68))
					fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
				if (*(int*) (ent + 0x3c))
					fcn_0047ccd0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
				else if (*(int*) (ent + 0x68))
					fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
				else if (*(int*) (ent + 0x60))
					fcn_0047cbf0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
				break;
			case 4:
				fcn_0047cd70(*(int*) (ent + 0x88), g_77250c);
				break;
			case 5:
			case 8:
				if (*(int*) (ent + 0x1e4) != -1) {
					font = (char*) fcn_00466190(*(int*) (ent + 0x1e4));
					fcn_0047cba0(*(int*) (ent + 0x1e8) + dx, *(int*) (ent + 0x1ec) + dy,
					             g_77250c, font, g_772568);
				}
				if ((char*) (g_1015ea0 + g_67d370 * 0x2f4) != ent && *(int*) (ent + 0x38)) {
					if (*(int*) (ent + 0x1d0) & 1)
						*(int*) (ent + 0x3c) = 0;
				}
				else if (*(int*) (ent + 0x1d0) & 1)
					*(int*) (ent + 0x3c) = 1;
				v = *(int*) (ent + 0x80);
				if (v != 0 && v != 1 && v != -1) {
					f = g_67d3c0[v];
					if (*(int*) (ent + 0x3c))
						fcn_0047cc80(dx, dy, g_77250c, *(void**) (ent + 0xc), *(int*) (ent + 0x88), f, 1);
					else
						fcn_0047cc80(dx, dy, g_77250c, *(void**) (ent + 0xc), *(int*) (ent + 0x88), f, 0);
				}
				if (*(int*) (ent + 0x3c))
					fcn_0047ccd0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
				else if (*(int*) (ent + 0x60)) {
					if (*(float*) (ent + 0x1f4) == g_6628a8)
						fcn_0047cbf0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
					else
						fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
				}
				else
					fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
				if (*(float*) (ent + 0x1f4) != g_6628a8) {
					y2 = (int) ((g_6628a0 - *(float*) (ent + 0x1f4)) * (float) *(int*) (ent + 0x1c)) + dy;
					if (bottom < y2)
						y2 = bottom;
					fcn_0047a040(left, top, right, y2);
					fcn_0047cbf0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
					fcn_0047a040(left, top, right, bottom);
					if (g_67d370 != *(int*) ent) {
						f = *(float*) (ent + 0x1f4);
						if (!(f <= g_6629c8))
							f = (float) g_6629c8;
						sprintf(buf, (char*) 0x67d43c, (int) (f * g_662c38));
						fcn_00472880(g_67d398 + 1);
						fcn_0046bd20(dx, dy + *(int*) (ent + 0x1c) - 0xf,
						             *(unsigned short*) (*(char**) (ent + 0xc) + 6),
						             *(int*) (ent + 0x1c), g_77250c, buf, 0x28);
					}
				}
				if (*(char*) (ent + 0x8c)) {
					if (*(int*) (ent + 0x84))
						fcn_00472880(*(int*) (ent + 0x84));
					if (*(int*) (ent + 0x40))
						fcn_0047a040(left, top, right, bottom);
					else
						fcn_0047a040(0, 0, 0x320, 0x258);
					flags = 0;
					if (*(int*) (ent + 0x3c))
						flags = 2;
					else if (*(int*) (ent + 0x60))
						flags = 1;
					if (*(int*) (ent + 0x6c))
						flags |= 8;
					if (*(int*) (ent + 0x70))
						flags |= 0x10;
					fcn_00472050(*(int*) ent, &w2, &h2);
					if (*(int*) (ent + 0x1dc) != -1)
						t = dx + *(int*) (ent + 0x1dc);
					else
						t = w2 + dx + 6;
					if (*(int*) (ent + 0x1e0) != -1)
						v = dy + *(int*) (ent + 0x1e0);
					else
						v = dy - 1;
					fcn_0046bd20(t, v, *(int*) (ent + 0x18), *(int*) (ent + 0x1c),
					             g_77250c, ent + 0x8c, flags);
				}
				if (*(char*) (ent + 0xcc)) {
					if ((char*) (g_1015ea0 + g_67d370 * 0x2f4) == ent && !g_7725d0
					    && !(*(int*) (ent + 0x1d0) & 0x40) && !*(int*) (ent + 0x4c)) {
						g_7725a4 = (int) ent;
						g_7725a0 = *(int*) (ent + 0x40);
					}
				}
				break;
			case 9:
				fcn_00468e40(*(int*) ent, g_77250c);
				break;
			case 0x40:
				if (*(int*) (ent + 0x24) <= 0)
					break;
				fcn_0046dff0(*(int*) (ent + 0x88), g_77250c);
				break;
			case 0x41:
				fcn_00466550(*(int*) (ent + 0x88), g_77250c);
				break;
			case 0x43:
				if (*(int*) (ent + 0x24) <= 0)
					break;
				if (*(int*) (ent + 0x78))
					break;
				if (*(int*) (ent + 0x1d0) & 2) {
					if ((char*) (g_1015ea0 + g_67d370 * 0x2f4) == ent || *(int*) (ent + 0x38)) {
						if (*(int*) (ent + 0x1d0) & 1)
							*(int*) (ent + 0x3c) = 1;
					}
					else if (*(int*) (ent + 0x1d0) & 1)
						*(int*) (ent + 0x3c) = 0;
				}
				if (*(int*) (ent + 0x24) == 2)
					*(int*) (ent + 0x24) = 1;
				fcn_00472880(*(int*) (ent + 0x84));
				flags = 0;
				if (*(int*) (ent + 0x3c))
					flags = 2;
				else if (*(int*) (ent + 0x60))
					flags = 1;
				if (*(int*) (ent + 0x6c))
					flags |= 8;
				if (*(int*) (ent + 0x70))
					flags |= 0x10;
				if (*(int*) (ent + 0x54))
					flags |= 4;
				fcn_0046bd20(dx, dy, *(int*) (ent + 0x18), *(int*) (ent + 0x1c),
				             g_77250c, (char*) *(int*) (ent + 0x88), flags);
				*(int*) (ent + 0x1c) = g_772548;
				fcn_00472880(g_67d378);
				break;
			case 0x45:
				if (*(int*) (ent + 0x40)) {
					child = *(char**) (ent + 0x40);
					fcn_00479cc0(*(int*) (ent + 0x28), *(int*) (ent + 0x30),
					             *(int*) (child + 0xc), *(int*) (child + 0x10),
					             (char*) g_77250c);
				}
				fcn_00467920(*(int*) ent, g_77250c);
				fcn_00479cc0(0, 0, g_1040494, g_1040490, (char*) g_77250c);
				break;
			case 0x47:
				*(int*) (ent + 0x30) = top;
				*(int*) (ent + 0x34) = bottom;
				fcn_00469320(*(int*) ent, g_77250c);
				break;
			}
		}
		fcn_0047a040(0, 0, g_1040494, g_1040490);
		i++;
		if (!*(char**) (tab + i * 4))
			break;
	}
label_46aadd:
	if (g_7725a4) {
		fcn_0047a040(0, 0, g_1040494, g_1040490);
		fcn_00469fd0((char*) g_7725a4);
		g_7725a0 = 0;
		g_7725a4 = 0;
	}
	if (g_7725d0 && *(signed char*) (g_7725d0 + 0x28) < 0 && *(int*) (g_7725d0 + 0x12c) != -1
	    && *(int*) (g_7725d0 + 0x1c) < *(int*) (g_7725d0 + 0x18) && g_14ce8d4)
		fcn_004663e0((char*) g_7725d0, g_77250c);
	fcn_0047a040(0, 0, g_1040494, g_1040490);
	fcn_00473a10(g_772570, g_772574);
	fcn_0047c560(0, 0, 0);
	fcn_004732c0();
	g_772524 = (int) fcn_00466190(fcn_00465950((char*) 0x67d474));
	g_1015ea4 = 0x18;
	g_77251c++;
}
