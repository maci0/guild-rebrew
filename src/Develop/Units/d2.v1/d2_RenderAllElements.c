#include <stdio.h>
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
} D2_RENDER_CLIP_RECT;
/* SIZE 0x10 */

#include "Develop/Units/d8_vesa/d3d_device_view.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern unsigned g_1052be4;
extern unsigned g_1052bec;
extern int g_77251c;
extern int d2_CurrentFontBank;
extern int d2_ZOrderStack;
extern int g_772548;
extern int d2_ResourceOffset;
extern int g_772570;
extern int g_772574;
extern int g_7725a0;
extern int g_7725a4;
extern void* g_7725a8;
extern int tp_d2_SelectedControl;
extern float flt_0_0;
extern double g_6629c8;
extern float g_67d3c0[];

void __cdecl d2_UpdateAnimations(void);
void __cdecl d2_SetClipRect(int left, int top, int right, int bottom);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawDimmedSpriteFrame(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawHighlightSprite(int x, int y, int surf, char* font, int c);
int __cdecl d2_DrawScaledSpriteQuad(int x, int y, int surf, void* s, int idx, float scale, int tint);
void* __cdecl d2_GetResourceData(int idx);
int __cdecl d2_FindResourceByName(const char* name);
void __cdecl d2_DrawFieldSliderPopup(char* f, int surf);
void __cdecl d2_DrawElementTooltip(char* e);
int __cdecl d2_DrawMouseCursor(int x, int y);
void __cdecl d2_FlushQueuedQuads(int a, int b, int c);
void __cdecl d2_UpdateAllScreenFades(void);
void __cdecl d2_SelectFont(int font);
void __cdecl d2_DrawWordWrappedText(int x, int y, int w, int h, int surf, char* text, int flags);
void __cdecl d2_SetSurfaceClipRect(int a, int b, int c, int d, char* e);
void __cdecl d2_DrawValueGauge(int a0, int a1);
void __cdecl d2_DrawTextButton(int a0, int a1);
void __cdecl d2_DrawField(int idx, int surf);
void __cdecl d2_DrawWindow(int a0, int a1);
void __cdecl d2_DrawBitmapElement(int idx, int surf);
void __cdecl d2_DrawAnimationSlot(int i, int tex);
void __cdecl d2_GetElementResourceSize(int a, int* w, int* h);

/* ADDRESS: GOLDTL 0x0046a110 */
/* ADDRESS: GOLDDE 0x0045d900 */
void __cdecl d2_RenderAllElements(int clearAll)
{
	struct { D2_RENDER_CLIP_RECT screen; float uv[2]; } loc;
	union { D2_RENDER_CLIP_RECT clip[2]; char buf[40]; } u;
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
	d2_UpdateAnimations();
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
		d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
		d2_DrawSpriteFromSet(0, 0, d2_ScreenSurface, (char*) (*(int *)&g_7725a8), 0);
	}
	if (!*(char**) d2_ZOrderStack)
		goto label_46aadd;
	while (1) {
		if (i >= 0x3fe)
			goto label_46aadd;
		ent = *(char**) ((char*) d2_ZOrderStack + i * 4);
		if ((!((D2_CONTROL_TL*) ent)->value_050 || !*(int*) (((D2_CONTROL_TL*) ent)->value_050 + 0x198))
		    && ((D2_CONTROL_TL*) ent)->value_004 && !((D2_CONTROL_TL*) ent)->value_048) {
			dx = ((D2_CONTROL_TL*) ent)->x;
			dy = ((D2_CONTROL_TL*) ent)->y;
			left = ((D2_CONTROL_TL*) ent)->clip_left;
			top = ((D2_CONTROL_TL*) ent)->clip_top;
			right = ((D2_CONTROL_TL*) ent)->clip_right;
			bottom = ((D2_CONTROL_TL*) ent)->clip_bottom;
			child = *(char**) &((D2_CONTROL_TL*) ent)->parent;
			if (child) {
				do {
					e2 = (char*) ((char*) &((D2_CONTROL_TL*) d2_Controls)[*(int*) (child + 0x27c)]);
					if (left < (*(D2_CONTROL_TL*) e2).clip_left)
						left = (*(D2_CONTROL_TL*) e2).clip_left;
					if ((*(D2_CONTROL_TL*) e2).clip_right < right)
						right = (*(D2_CONTROL_TL*) e2).clip_right;
					if (top < (*(D2_CONTROL_TL*) e2).clip_top)
						top = (*(D2_CONTROL_TL*) e2).clip_top;
					if ((*(D2_CONTROL_TL*) e2).clip_bottom < bottom)
						bottom = (*(D2_CONTROL_TL*) e2).clip_bottom;
					child = *(char**) (&(*(D2_CONTROL_TL*) e2).parent);
				} while (child);
			}
			if (g_7725a4 && (*(int*) &((D2_CONTROL_TL*) ent)->parent != g_7725a0 || !*(int*) (g_7725a4 + 0x40))) {
				d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
				d2_DrawElementTooltip((char*) g_7725a4);
				g_7725a0 = *(int*) &((D2_CONTROL_TL*) ent)->parent;
				g_7725a4 = 0;
			}
			d2_SetClipRect(left, top, right, bottom);
			switch (((D2_CONTROL_TL*) ent)->kind) {
			case 1:
				if (((D2_CONTROL_TL*) ent)->value_1e4 != -1) {
					font = (char*) d2_GetResourceData(((D2_CONTROL_TL*) ent)->value_1e4);
					d2_DrawSpriteFromSet(((D2_CONTROL_TL*) ent)->value_1e8 + dx, ((D2_CONTROL_TL*) ent)->value_1ec + dy,
					             d2_ScreenSurface, font, d2_ResourceOffset);
				}
				if (((D2_CONTROL_TL*) ent)->flags_1d0 & 2) {
					if ((char*) ((char*) &((D2_CONTROL_TL*) d2_Controls)[d2_CurrentElementId]) == ent || !((D2_CONTROL_TL*) ent)->value_038) {
						if (!((D2_CONTROL_TL*) ent)->disabled) {
							if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
								((D2_CONTROL_TL*) ent)->value_03c = 1;
						}
						else if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
							((D2_CONTROL_TL*) ent)->value_03c = 0;
					}
					else if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
						((D2_CONTROL_TL*) ent)->value_03c = 0;
				}
				v = ((D2_CONTROL_TL*) ent)->value_080;
				if (v != 0 && v != 1 && v != -1) {
					f = g_67d3c0[v];
					if (((D2_CONTROL_TL*) ent)->value_03c)
						d2_DrawScaledSpriteQuad(dx, dy, d2_ScreenSurface, ((D2_CONTROL_TL*) ent)->data, 0, f, 1);
					else
						d2_DrawScaledSpriteQuad(dx, dy, d2_ScreenSurface, ((D2_CONTROL_TL*) ent)->data, 0, f, 0);
				}
				else {
					if (!((D2_CONTROL_TL*) ent)->value_068)
						d2_DrawSpriteFromSet(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, 0);
					if (((D2_CONTROL_TL*) ent)->value_03c)
						d2_DrawHighlightSprite(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, 0);
					else if (((D2_CONTROL_TL*) ent)->value_068)
						d2_DrawSpriteFromSet(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, 0);
					else if (((D2_CONTROL_TL*) ent)->value_060)
						d2_DrawDimmedSpriteFrame(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, 0);
				}
				break;
			case 4:
				d2_DrawAnimationSlot(((D2_CONTROL_TL*) ent)->value_088, d2_ScreenSurface);
				break;
			case 5:
			case 8:
				if (((D2_CONTROL_TL*) ent)->value_1e4 != -1) {
					font = (char*) d2_GetResourceData(((D2_CONTROL_TL*) ent)->value_1e4);
					d2_DrawSpriteFromSet(((D2_CONTROL_TL*) ent)->value_1e8 + dx, ((D2_CONTROL_TL*) ent)->value_1ec + dy,
					             d2_ScreenSurface, font, d2_ResourceOffset);
				}
				if ((char*) ((char*) &((D2_CONTROL_TL*) d2_Controls)[d2_CurrentElementId]) != ent && ((D2_CONTROL_TL*) ent)->value_038) {
					if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
						((D2_CONTROL_TL*) ent)->value_03c = 0;
				}
				else if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
					((D2_CONTROL_TL*) ent)->value_03c = 1;
				v = ((D2_CONTROL_TL*) ent)->value_080;
				if (v != 0 && v != 1 && v != -1) {
					f = g_67d3c0[v];
					if (((D2_CONTROL_TL*) ent)->value_03c)
						d2_DrawScaledSpriteQuad(dx, dy, d2_ScreenSurface, ((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088, f, 1);
					else
						d2_DrawScaledSpriteQuad(dx, dy, d2_ScreenSurface, ((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088, f, 0);
					goto label_46a7ab;
				}
				if (((D2_CONTROL_TL*) ent)->value_03c)
					d2_DrawHighlightSprite(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088);
				else if (((D2_CONTROL_TL*) ent)->value_060) {
					if (((D2_CONTROL_TL*) ent)->value_1f4.real == flt_0_0)
						d2_DrawDimmedSpriteFrame(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088);
					else
						d2_DrawSpriteFromSet(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088);
				}
				else
					d2_DrawSpriteFromSet(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088);
label_46a7ab:
				if (((D2_CONTROL_TL*) ent)->value_1f4.real != flt_0_0) {
					y2 = (int) ((flt_1_0 - ((D2_CONTROL_TL*) ent)->value_1f4.real) * (float) ((D2_CONTROL_TL*) ent)->height) + dy;
					if (bottom < y2)
						y2 = bottom;
					d2_SetClipRect(left, top, right, y2);
					d2_DrawDimmedSpriteFrame(dx, dy, d2_ScreenSurface, *(char**) &((D2_CONTROL_TL*) ent)->data, ((D2_CONTROL_TL*) ent)->value_088);
					d2_SetClipRect(left, top, right, bottom);
					if (d2_CurrentElementId != ((D2_CONTROL_TL*) ent)->value_000) {
						f = ((D2_CONTROL_TL*) ent)->value_1f4.real;
						if (f > g_6629c8)
							f = (float) g_6629c8;
						sprintf(u.buf, (char*) 0x67d43c, (int) (f * 100.0));
						d2_SelectFont(d2_DefaultFont + 1);
						d2_DrawWordWrappedText(dx, dy + ((D2_CONTROL_TL*) ent)->height - 0xf,
						             *(unsigned short*) (*(char**) &((D2_CONTROL_TL*) ent)->data + 6),
						             ((D2_CONTROL_TL*) ent)->height, d2_ScreenSurface, u.buf, 0x28);
					}
				}
				if (*(char*) (ent + 0x8c)) {
					if (((D2_CONTROL_TL*) ent)->font)
						d2_SelectFont(((D2_CONTROL_TL*) ent)->font);
					if (*(int*) &((D2_CONTROL_TL*) ent)->parent)
						d2_SetClipRect(left, top, right, bottom);
					else
						d2_SetClipRect(0, 0, 0x320, 0x258);
					flags = 0;
					if (((D2_CONTROL_TL*) ent)->value_03c)
						flags = 2;
					else if (((D2_CONTROL_TL*) ent)->value_060)
						flags = 1;
					if (((D2_CONTROL_TL*) ent)->value_06c)
						flags |= 8;
					if (((D2_CONTROL_TL*) ent)->value_070)
						flags |= 0x10;
					d2_GetElementResourceSize(((D2_CONTROL_TL*) ent)->value_000, &w2, &h2);
					if (((D2_CONTROL_TL*) ent)->value_1dc != -1)
						t = dx + ((D2_CONTROL_TL*) ent)->value_1dc;
					else
						t = w2 + dx + 6;
					if (((D2_CONTROL_TL*) ent)->value_1e0 != -1)
						v = dy + ((D2_CONTROL_TL*) ent)->value_1e0;
					else
						v = dy - 1;
					d2_DrawWordWrappedText(t, v, ((D2_CONTROL_TL*) ent)->width, ((D2_CONTROL_TL*) ent)->height,
					             d2_ScreenSurface, ent + 0x8c, flags);
				}
				if (*(char*) (ent + 0xcc)) {
					if ((char*) ((char*) &((D2_CONTROL_TL*) d2_Controls)[d2_CurrentElementId]) == ent && !tp_d2_SelectedControl
					    && !(((D2_CONTROL_TL*) ent)->flags_1d0 & 0x40) && !((D2_CONTROL_TL*) ent)->disabled) {
						g_7725a4 = (int) ent;
						g_7725a0 = *(int*) &((D2_CONTROL_TL*) ent)->parent;
					}
				}
				break;
			case 9:
				d2_DrawTextButton(((D2_CONTROL_TL*) ent)->value_000, d2_ScreenSurface);
				break;
			case 0x40:
				if (((D2_CONTROL_TL*) ent)->mode <= 0)
					break;
				d2_DrawWindow(((D2_CONTROL_TL*) ent)->value_088, d2_ScreenSurface);
				break;
			case 0x41:
				d2_DrawField(((D2_CONTROL_TL*) ent)->value_088, d2_ScreenSurface);
				break;
			case 0x43:
				if (((D2_CONTROL_TL*) ent)->mode <= 0)
					break;
				if (((D2_CONTROL_TL*) ent)->value_078)
					break;
				if (((D2_CONTROL_TL*) ent)->flags_1d0 & 2) {
					if ((char*) ((char*) &((D2_CONTROL_TL*) d2_Controls)[d2_CurrentElementId]) == ent || ((D2_CONTROL_TL*) ent)->value_038) {
						if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
							((D2_CONTROL_TL*) ent)->value_03c = 1;
					}
					else if (((D2_CONTROL_TL*) ent)->flags_1d0 & 1)
						((D2_CONTROL_TL*) ent)->value_03c = 0;
				}
				if (((D2_CONTROL_TL*) ent)->mode == 2)
					((D2_CONTROL_TL*) ent)->mode = 1;
				d2_SelectFont(((D2_CONTROL_TL*) ent)->font);
				flags = 0;
				if (((D2_CONTROL_TL*) ent)->value_03c)
					flags = 2;
				else if (((D2_CONTROL_TL*) ent)->value_060)
					flags = 1;
				if (((D2_CONTROL_TL*) ent)->value_06c)
					flags |= 8;
				if (((D2_CONTROL_TL*) ent)->value_070)
					flags |= 0x10;
				if (((D2_CONTROL_TL*) ent)->value_054)
					flags |= 4;
				d2_DrawWordWrappedText(dx, dy, ((D2_CONTROL_TL*) ent)->width, ((D2_CONTROL_TL*) ent)->height,
				             d2_ScreenSurface, (char*) ((D2_CONTROL_TL*) ent)->value_088, flags);
				((D2_CONTROL_TL*) ent)->height = g_772548;
				d2_SelectFont(d2_CurrentFont);
				break;
			case 0x45:
				if (*(int*) &((D2_CONTROL_TL*) ent)->parent) {
					child = *(char**) &((D2_CONTROL_TL*) ent)->parent;
					d2_SetSurfaceClipRect(((D2_CONTROL_TL*) ent)->clip_left, ((D2_CONTROL_TL*) ent)->clip_top,
					             *(int*) (child + 0xc), *(int*) (child + 0x10),
					             (char*) d2_ScreenSurface);
				}
				d2_DrawValueGauge(((D2_CONTROL_TL*) ent)->value_000, d2_ScreenSurface);
				d2_SetSurfaceClipRect(0, 0, g_1040494, d2_ScreenHeight, (char*) d2_ScreenSurface);
				break;
			case 0x47:
				((D2_CONTROL_TL*) ent)->clip_top = top;
				((D2_CONTROL_TL*) ent)->clip_bottom = bottom;
				d2_DrawBitmapElement(((D2_CONTROL_TL*) ent)->value_000, d2_ScreenSurface);
				break;
			}
		}
		d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
		i++;
		if (!*(char**) ((char*) d2_ZOrderStack + i * 4))
			break;
	}
label_46aadd:
	if (g_7725a4) {
		d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
		d2_DrawElementTooltip((char*) g_7725a4);
		g_7725a0 = 0;
		g_7725a4 = 0;
	}
	if (tp_d2_SelectedControl && *(signed char*) (tp_d2_SelectedControl + 0x28) < 0 && *(int*) (tp_d2_SelectedControl + 0x12c) != -1
	    && *(int*) (tp_d2_SelectedControl + 0x1c) < *(int*) (tp_d2_SelectedControl + 0x18) && g_14ce8d4)
		d2_DrawFieldSliderPopup((char*) tp_d2_SelectedControl, d2_ScreenSurface);
	d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
	d2_DrawMouseCursor(g_772570, g_772574);
	d2_FlushQueuedQuads(0, 0, 0);
	d2_UpdateAllScreenFades();
	d2_CurrentFontBank = (int) d2_GetResourceData(d2_FindResourceByName((char*) 0x67d474));
	d2_FontHeight = 0x18;
	g_77251c++;
}
