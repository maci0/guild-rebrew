#include <stdio.h>
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
} fcn_0046a110_Rect;
/* SIZE 0x10 */

#include "Develop/Units/d8_vesa/d3d_device_view.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern unsigned g_1052be4;
extern unsigned g_1052bec;
extern int g_77251c;
extern int g_772524;
extern int g_772540;
extern int g_772548;
extern int d2_ResourceOffset;
extern int g_772570;
extern int g_772574;
extern int g_7725a0;
extern int g_7725a4;
extern void* g_7725a8;
extern int tp_d2_SelectedControl;
extern float g_6628a8;
extern double g_6629c8;
extern float g_67d3c0[];

void __cdecl fcn_0047a090(void);
void __cdecl fcn_0047a040(int left, int top, int right, int bottom);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047cbf0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047ccd0(int x, int y, int surf, char* font, int c);
int __cdecl fcn_0047cc80(int x, int y, int surf, void* s, int idx, float scale, int tint);
void* __cdecl d2_GetResourceData(int idx);
int __cdecl fcn_00465950(const char* name);
void __cdecl fcn_004663e0(char* f, int surf);
void __cdecl fcn_00469fd0(char* e);
int __cdecl d2_DrawMouseCursor(int x, int y);
void __cdecl fcn_0047c560(int a, int b, int c);
void __cdecl fcn_004732c0(void);
void __cdecl d2_SelectFont(int font);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);
void __cdecl fcn_00479cc0(int a, int b, int c, int d, char* e);
void __cdecl fcn_00467920(int a0, int a1);
void __cdecl fcn_00468e40(int a0, int a1);
void __cdecl d2_DrawField(int idx, int surf);
void __cdecl d2_DrawWindow(int a0, int a1);
void __cdecl fcn_00469320(int idx, int surf);
void __cdecl d2_DrawAnimationSlot(int i, int tex);
void __cdecl d2_GetElementResourceSize(int a, int* w, int* h);

/* ADDRESS: GOLDTL 0x0046a110 */
void __cdecl fcn_0046a110(int clearAll)
{
	struct { fcn_0046a110_Rect screen; float uv[2]; } loc;
	union { fcn_0046a110_Rect clip[2]; char buf[40]; } u;
	char* ent;
	char* child;
	char* e2;
	char* font;
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
	loc.screen.left = 0;
	loc.screen.top = 0;
	loc.screen.right = g_1040494;
	loc.screen.bottom = d2_ScreenHeight;
	loc.uv[0] = 0.0f;
	loc.uv[1] = 1.0f;
	(*(void (__stdcall **)(void*, void*)) ((int) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl + 0xa0))(g_6b5de0, &loc.screen);
	if (clearAll) {
		(*(void (__stdcall **)(void*, int, void*, int, int, float, int)) ((int) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl + 0x90))(g_6b5de0, 0, 0, 1, 0, 1.0f, 0);
	}
	else {
		n = 0;
		if (g_1052be4 > 0) {
			u.clip[0].left = 0;
			u.clip[0].top = 0;
			u.clip[0].right = g_1040494;
			u.clip[0].bottom = g_1052be4;
			n = 1;
		}
		if (g_1052bec < d2_ScreenHeight - g_1052be4) {
			u.clip[n].left = 0;
			u.clip[n].top = g_1052bec + g_1052be4;
			u.clip[n].right = g_1040494;
			u.clip[n].bottom = d2_ScreenHeight;
			n++;
		}
		if (n) {
			(*(void (__stdcall **)(void*, int, void*, int, int, float, int)) ((int) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl + 0x90))(g_6b5de0, n, u.clip, 1, 0, 1.0f, 0);
		}
	}
	if ((*(int *)&g_7725a8)) {
		fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
		fcn_0047cba0(0, 0, g_77250c, (char*) (*(int *)&g_7725a8), 0);
	}
	if (!*(char**) g_772540)
		goto label_46aadd;
	while (1) {
		if (i >= 0x3fe)
			goto label_46aadd;
		ent = *(char**) ((char*) g_772540 + i * 4);
		if ((!*(int*) (ent + 0x50) || !*(int*) (*(int*) (ent + 0x50) + 0x198))
		    && *(int*) (ent + 4) && !*(int*) (ent + 0x48)) {
			dx = *(int*) (ent + 0x10);
			dy = *(int*) (ent + 0x14);
			left = *(int*) (ent + 0x28);
			top = *(int*) (ent + 0x30);
			right = *(int*) (ent + 0x2c);
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
				fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
				fcn_00469fd0((char*) g_7725a4);
				g_7725a0 = *(int*) (ent + 0x40);
				g_7725a4 = 0;
			}
			fcn_0047a040(left, top, right, bottom);
			switch (*(int*) (ent + 0x20)) {
			case 1:
				if (*(int*) (ent + 0x1e4) != -1) {
					font = (char*) d2_GetResourceData(*(int*) (ent + 0x1e4));
					fcn_0047cba0(*(int*) (ent + 0x1e8) + dx, *(int*) (ent + 0x1ec) + dy,
					             g_77250c, font, d2_ResourceOffset);
				}
				if (*(int*) (ent + 0x1d0) & 2) {
					if ((char*) (g_1015ea0 + d2_CurrentElementId * 0x2f4) == ent || !*(int*) (ent + 0x38)) {
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
				else {
					if (!*(int*) (ent + 0x68))
						fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
					if (*(int*) (ent + 0x3c))
						fcn_0047ccd0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
					else if (*(int*) (ent + 0x68))
						fcn_0047cba0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
					else if (*(int*) (ent + 0x60))
						fcn_0047cbf0(dx, dy, g_77250c, *(char**) (ent + 0xc), 0);
				}
				break;
			case 4:
				d2_DrawAnimationSlot(*(int*) (ent + 0x88), g_77250c);
				break;
			case 5:
			case 8:
				if (*(int*) (ent + 0x1e4) != -1) {
					font = (char*) d2_GetResourceData(*(int*) (ent + 0x1e4));
					fcn_0047cba0(*(int*) (ent + 0x1e8) + dx, *(int*) (ent + 0x1ec) + dy,
					             g_77250c, font, d2_ResourceOffset);
				}
				if ((char*) (g_1015ea0 + d2_CurrentElementId * 0x2f4) != ent && *(int*) (ent + 0x38)) {
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
					goto label_46a7ab;
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
label_46a7ab:
				if (*(float*) (ent + 0x1f4) != g_6628a8) {
					y2 = (int) ((g_6628a0 - *(float*) (ent + 0x1f4)) * (float) *(int*) (ent + 0x1c)) + dy;
					if (bottom < y2)
						y2 = bottom;
					fcn_0047a040(left, top, right, y2);
					fcn_0047cbf0(dx, dy, g_77250c, *(char**) (ent + 0xc), *(int*) (ent + 0x88));
					fcn_0047a040(left, top, right, bottom);
					if (d2_CurrentElementId != *(int*) ent) {
						f = *(float*) (ent + 0x1f4);
						if (f > g_6629c8)
							f = (float) g_6629c8;
						sprintf(u.buf, (char*) 0x67d43c, (int) (f * 100.0));
						d2_SelectFont(d2_DefaultFont + 1);
						fcn_0046bd20(dx, dy + *(int*) (ent + 0x1c) - 0xf,
						             *(unsigned short*) (*(char**) (ent + 0xc) + 6),
						             *(int*) (ent + 0x1c), g_77250c, u.buf, 0x28);
					}
				}
				if (*(char*) (ent + 0x8c)) {
					if (*(int*) (ent + 0x84))
						d2_SelectFont(*(int*) (ent + 0x84));
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
					d2_GetElementResourceSize(*(int*) ent, &w2, &h2);
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
					if ((char*) (g_1015ea0 + d2_CurrentElementId * 0x2f4) == ent && !tp_d2_SelectedControl
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
				d2_DrawWindow(*(int*) (ent + 0x88), g_77250c);
				break;
			case 0x41:
				d2_DrawField(*(int*) (ent + 0x88), g_77250c);
				break;
			case 0x43:
				if (*(int*) (ent + 0x24) <= 0)
					break;
				if (*(int*) (ent + 0x78))
					break;
				if (*(int*) (ent + 0x1d0) & 2) {
					if ((char*) (g_1015ea0 + d2_CurrentElementId * 0x2f4) == ent || *(int*) (ent + 0x38)) {
						if (*(int*) (ent + 0x1d0) & 1)
							*(int*) (ent + 0x3c) = 1;
					}
					else if (*(int*) (ent + 0x1d0) & 1)
						*(int*) (ent + 0x3c) = 0;
				}
				if (*(int*) (ent + 0x24) == 2)
					*(int*) (ent + 0x24) = 1;
				d2_SelectFont(*(int*) (ent + 0x84));
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
				d2_SelectFont(d2_CurrentFont);
				break;
			case 0x45:
				if (*(int*) (ent + 0x40)) {
					child = *(char**) (ent + 0x40);
					fcn_00479cc0(*(int*) (ent + 0x28), *(int*) (ent + 0x30),
					             *(int*) (child + 0xc), *(int*) (child + 0x10),
					             (char*) g_77250c);
				}
				fcn_00467920(*(int*) ent, g_77250c);
				fcn_00479cc0(0, 0, g_1040494, d2_ScreenHeight, (char*) g_77250c);
				break;
			case 0x47:
				*(int*) (ent + 0x30) = top;
				*(int*) (ent + 0x34) = bottom;
				fcn_00469320(*(int*) ent, g_77250c);
				break;
			}
		}
		fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
		i++;
		if (!*(char**) ((char*) g_772540 + i * 4))
			break;
	}
label_46aadd:
	if (g_7725a4) {
		fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
		fcn_00469fd0((char*) g_7725a4);
		g_7725a0 = 0;
		g_7725a4 = 0;
	}
	if (tp_d2_SelectedControl && *(signed char*) (tp_d2_SelectedControl + 0x28) < 0 && *(int*) (tp_d2_SelectedControl + 0x12c) != -1
	    && *(int*) (tp_d2_SelectedControl + 0x1c) < *(int*) (tp_d2_SelectedControl + 0x18) && g_14ce8d4)
		fcn_004663e0((char*) tp_d2_SelectedControl, g_77250c);
	fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
	d2_DrawMouseCursor(g_772570, g_772574);
	fcn_0047c560(0, 0, 0);
	fcn_004732c0();
	g_772524 = (int) d2_GetResourceData(fcn_00465950((char*) 0x67d474));
	d2_FontHeight = 0x18;
	g_77251c++;
}
