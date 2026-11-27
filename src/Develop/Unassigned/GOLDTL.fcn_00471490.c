#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"

extern D2_FORM_RECORD g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7725ec;
extern char s_67d7a0[];

void __cdecl ReportClientMessage(char* text);
void __cdecl d2_ClearOwnerDirtyRects(char* base);
void __cdecl d2_DrawField(int idx, int surf);
void __cdecl d2_DrawValueGauge(int idx, int surf);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, char* surf, char* text, int flags);
void __cdecl d2_DrawWindow(int idx, char* surf);
int __cdecl d2_GetElementResourceSize(int slot, int* w, int* h);
void __cdecl d2_SelectFont(int idx);
int __cdecl d2_BlitBufferToSurface(int x, int y, int w, int h, char* src, int sx, int sy, char* t);
void __cdecl d2_SetClipRect(int left, int top, int right, int bottom);
void __cdecl d2_FlushQueuedQuads(int a, int b, char* surf);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawHighlightSprite(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawAnimationSlot(int idx, int surf);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00471490 */
void __cdecl d2_RenderFormToTextures(int k)
{
	char** pp;
	int saved;
	char* base;
	int v;
	int flags;
	int ybase;
	int col;
	D2_WIN* win;
	int row;
	int w;
	int right;
	int h;
	char* surf;
	char* obj;
	int sx;
	int sy;
	int top, left;
	int oh1;
	int oh2;

	saved = d2_QueuedQuadCount;
	base = ((char*) g_1038140) + k * 0x2bc;
	if (*(int*) (base + 0x190) == 0) {
		return;
	}
	if (*(int*) (base + 0x198) == 0) {
		return;
	}
	d2_ClearOwnerDirtyRects(base);
	ybase = 0;
	pp = (char**) (base + 0x1ac);
	do {
		surf = pp[-2];
		if ((*(unsigned char*) surf & 0x10) == 0) {
			ReportClientMessage(s_67d7a0);
			return;
		}
		d2_BlitBufferToSurface(0, 0, *(int*) (pp[0] + 4), *(int*) (pp[0] + 8), *(int*) (pp[0] + 0x20), 0, 0, surf);
		for (row = 0; row < *(int*) (base + 0x184); row++) {
			win = &((D2_WIN*)g_1015f40)[((int*) (base + 4))[row]];
			oh2 = win->top;
			oh1 = win->left;
			win->top = ybase + oh2;
			d2_DrawWindow(((int*) (base + 4))[row], surf);
			win->left = oh1;
			win->top = oh2;
			for (col = 0; col < win->count; col++) {
				obj = (char*) &((D2_CONTROL_TL*) g_1015ea0)[win->children[col]];
				sx = (*(D2_CONTROL_TL*) obj).x - *(int*) (base + 0x188);
				sy = ybase - *(int*) (base + 0x18c) + (*(D2_CONTROL_TL*) obj).y;
				if ((*(D2_CONTROL_TL*) obj).value_004 != 0) {
					v = (*(D2_CONTROL_TL*) obj).clip_bottom + ybase;
					if (v >= 0x100) {
						v = 0x100;
					}
					right = (*(D2_CONTROL_TL*) obj).clip_right;
					if (right >= 0x100) {
						right = 0x100;
					}
					top = (*(D2_CONTROL_TL*) obj).clip_top + ybase;
					left = (*(D2_CONTROL_TL*) obj).clip_left;
					d2_SetClipRect(left & ((left < 0) - 1), top & ((top <= 0) - 1), right, v);
					switch ((*(D2_CONTROL_TL*) obj).kind) {
					case 1:
						if ((*(D2_CONTROL_TL*) obj).value_03c) {
							d2_DrawHighlightSprite(sx, sy, (int) surf, *(char**) (&(*(D2_CONTROL_TL*) obj).data), 0);
						} else {
							d2_DrawSpriteFromSet(sx, sy, (int) surf, *(char**) (&(*(D2_CONTROL_TL*) obj).data), 0);
						}
						break;
					case 4:
						d2_DrawAnimationSlot((*(D2_CONTROL_TL*) obj).value_088, (int) surf);
						break;
					case 5:
					case 8:
						if ((*(D2_CONTROL_TL*) obj).flags_1d0 & 2) {
							if ((char*) &((D2_CONTROL_TL*) g_1015ea0)[d2_CurrentElementId] == obj || (*(D2_CONTROL_TL*) obj).value_038 != 0) {
								if ((*(D2_CONTROL_TL*) obj).flags_1d0 & 1) {
									(*(D2_CONTROL_TL*) obj).value_03c = 1;
								}
							} else {
								if ((*(D2_CONTROL_TL*) obj).flags_1d0 & 1) {
									(*(D2_CONTROL_TL*) obj).value_03c = 0;
								}
							}
						}
						if ((*(D2_CONTROL_TL*) obj).value_03c) {
							d2_DrawHighlightSprite(sx, sy, (int) surf, *(char**) (&(*(D2_CONTROL_TL*) obj).data), (*(D2_CONTROL_TL*) obj).value_088);
						} else {
							d2_DrawSpriteFromSet(sx, sy, (int) surf, *(char**) (&(*(D2_CONTROL_TL*) obj).data), (*(D2_CONTROL_TL*) obj).value_088);
						}
						if (*(unsigned char*) (&(*(D2_CONTROL_TL*) obj).payload.fields.value_08c) == 0) {
							break;
						}
						if ((*(D2_CONTROL_TL*) obj).font != 0) {
							d2_SelectFont((*(D2_CONTROL_TL*) obj).font);
						}
						flags = 0;
						if ((*(D2_CONTROL_TL*) obj).value_03c) {
							flags = 2;
						} else if ((*(D2_CONTROL_TL*) obj).value_060) {
							flags = 1;
						}
						if ((*(D2_CONTROL_TL*) obj).value_06c) {
							flags |= 8;
						}
						if ((*(D2_CONTROL_TL*) obj).value_070) {
							flags |= 0x10;
						}
						d2_GetElementResourceSize(*(int*) obj, &w, &h);
						if ((*(D2_CONTROL_TL*) obj).value_1dc != -1) {
							sx = (*(D2_CONTROL_TL*) obj).value_1dc - *(int*) (base + 0x188);
							top = (*(D2_CONTROL_TL*) obj).width;
						} else {
							sx = w - *(int*) (base + 0x188) + (*(D2_CONTROL_TL*) obj).x + 6;
							top = w * 3 + (*(D2_CONTROL_TL*) obj).width;
						}
						if ((*(D2_CONTROL_TL*) obj).value_1e0 != -1) {
							sy = ybase - *(int*) (base + 0x18c) + (*(D2_CONTROL_TL*) obj).value_1e0;
						} else {
							sy = ybase - *(int*) (base + 0x18c) + (*(D2_CONTROL_TL*) obj).y - 1;
						}
						fcn_0046bd20(sx, sy, top, (*(D2_CONTROL_TL*) obj).height, surf,
						             obj + 0x8c, flags);
						break;
					case 0x41:
						d2_DrawField((*(D2_CONTROL_TL*) obj).value_088, (int) surf);
						break;
					case 0x43:
						if ((*(D2_CONTROL_TL*) obj).mode > 0) {
							d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
							d2_SelectFont((*(D2_CONTROL_TL*) obj).font);
							flags = 0;
							if ((*(D2_CONTROL_TL*) obj).value_03c) {
								flags = 2;
							} else if ((*(D2_CONTROL_TL*) obj).value_060) {
								flags = 1;
							}
							if ((*(D2_CONTROL_TL*) obj).value_06c) {
								flags |= 8;
							}
							if ((*(D2_CONTROL_TL*) obj).value_070) {
								flags |= 0x10;
							}
							fcn_0046bd20(sx, sy, (*(D2_CONTROL_TL*) obj).width, (*(D2_CONTROL_TL*) obj).height,
							             surf, *(char**) (&(*(D2_CONTROL_TL*) obj).value_088), flags);
							d2_SelectFont(d2_CurrentFont);
						}
						break;
					case 0x45:
						sx = (*(D2_CONTROL_TL*) obj).x;
						sy = (*(D2_CONTROL_TL*) obj).y;
						(*(D2_CONTROL_TL*) obj).x = sx - *(int*) (base + 0x188);
						(*(D2_CONTROL_TL*) obj).y = ybase - *(int*) (base + 0x18c) + sy;
						d2_DrawValueGauge(*(int*) obj, (int) surf);
						(*(D2_CONTROL_TL*) obj).x = sx;
						(*(D2_CONTROL_TL*) obj).y = sy;
						break;
					}
				}
				d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
			}
		}
		d2_FlushQueuedQuads(saved, g_7725ec, surf);
		ybase -= 0x100;
		pp++;
	} while (ybase > -0x200);
}
