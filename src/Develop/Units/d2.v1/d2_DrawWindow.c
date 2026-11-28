#include "Develop/DieGildeAddOn/game/client_data.h"
extern int g_772554;
extern char* d2_Controls;
extern char* d2_FileObjTable;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_67d3a0;
extern int g_67d3a4;

void __cdecl d2_RenderMarkupText(int, int);
void __cdecl d2_UpdateWindowScroll(int);
void __cdecl d2_DrawWindowBackground(int, int);
void __cdecl d2_SetElementEnabled(int, int);
void __cdecl d2_SetLabelText(int, char*);
void __cdecl d2_FlushQueuedQuads(int, int, int);
void __cdecl d2_SetClipRect(int, int, int, int);
void __cdecl d2_DrawSpriteFromSet(int, int, int, int, int);
int __cdecl d2_GetResourceData(int);
char* __cdecl itoa(int, char*, int);

/* Draw one window slot: sync the item states, size the frame, then blit the
 * border and the hatch pattern for the selected building. */
/* ADDRESS: GOLDTL 0x0046dff0 */
void __cdecl d2_DrawWindow(int windowIndex, int a1)
{
	char* b;
	int saved;
	int n;
	int i;
	int id;
	int rec;
	int x;
	int y;
	int w;
	int h;
	int vert;
	int cornerHeight;
	int horiz;
	int step;
	int off;
	int count;
	int mode;
	int surf;
	char buf[32];

	b = (char*) &d2_Windows[windowIndex];
	if (!*(int*) (b + 0x290)) {
		return;
	}
	saved = g_772554;
	g_772554 = 1;
	n = *(int*) (b + 0x2c);
	if (n > 0) {
		i = 0;
		do {
			id = *(int*) (*(int*) (b + 0x28) + i * 4);
			if (*(int*) (d2_Controls + 0x20 + id * 0x2f4) == 0x40) {
				rec = *(int*) (d2_Controls + id * 0x2f4 + 0x88);
				if (*(unsigned int*) ((char*) &d2_Windows[rec] + 0x14) & 0x4000) {
					d2_RenderMarkupText(0, rec);
				}
			}
			i++;
		} while (i < *(int*) (b + 0x2c));
	}
	if (*(unsigned int*) (b + 0x14) & 0x4000) {
		d2_RenderMarkupText(0, windowIndex);
	}
	rec = *(int*) (b + 0x274);
	g_772554 = saved;
	if (rec) {
		if (rec % 8 == 0) {
			*(char*) (b + 0x270) = 8;
		} else if (rec % 6 == 0) {
			*(char*) (b + 0x270) = 6;
		} else if (rec % 4 == 0) {
			*(char*) (b + 0x270) = 4;
		} else if (rec % 2 == 0) {
			*(char*) (b + 0x270) = 2;
		}
	}

	if (*(int*) (b + 0x3b8) != -1 || *(int*) (b + 0x3bc) != -1) {
		rec = *(int*) (b + 0x3bc);
		x = *(int*) (d2_Controls + 0x1f0 + rec * 0x2f4) * 0x3cc;
		if (rec != -1) {
			d2_SetElementEnabled(rec, *(int*) ((char*) d2_Windows + x + 0x274) + *(int*) ((char*) d2_Windows + x + 0x10) <= *(int*) ((char*) d2_Windows + x + 0x254));
			d2_SetElementEnabled(rec, *(int*) ((char*) d2_Windows + x + 0x260) + *(int*) ((char*) d2_Windows + x + 0x258) + *(int*) ((char*) d2_Windows + x + 0x10) < *(int*) ((char*) d2_Windows + x + 0x254));
		}
		if (*(int*) (b + 0x3b8) != -1) {
			d2_SetElementEnabled(*(int*) (b + 0x3b8), *(int*) ((char*) d2_Windows + x + 0x258) != 0);
		}
		if (*(int*) (b + 0x3c0) != -1) {
			itoa((int) ((double) *(int*) ((char*) d2_Windows + x + 0x254) / (double) *(int*) ((char*) d2_Windows + x + 0x274) + 0.5f), buf, 10);
			d2_SetLabelText(*(unsigned int*) (b + 0x3c0), buf);
		}
	}
	d2_UpdateWindowScroll(windowIndex);
	vert = a1;
	if (!g_772554) {
		if ((*(unsigned char*) (b + 0x14) & 1) || *(int*) (b + 0x3a0)) {
			d2_FlushQueuedQuads(0, 0, 0);
		}
		d2_DrawWindowBackground((int) b, vert);
	}
	if (*(unsigned char*) (b + 0x14) & 0x10) {
		d2_RenderMarkupText(vert, windowIndex);
	}
	d2_SetClipRect(*(int*) (b + 4), *(int*) (b + 8), *(int*) (b + 0xc) + *(int*) (b + 4), *(int*) (b + 0x10) + *(int*) (b + 8));
	if ((*(unsigned char*) (b + 0x14) & 4) && !g_772554) {
		surf = d2_GetResourceData(*(unsigned int*) (b + 0x288));
		rec = *(int*) (b + 0x288);
		x = *(int*) (b + 4);
		y = *(int*) (b + 8);
		h = *(int*) (b + 0x10);
		w = *(int*) (b + 0xc);
		if (rec != g_67d3a0 && rec != g_67d3a4) {
			horiz = *(short*) (d2_FileObjTable + 0x50 + rec * 0x54);
			cornerHeight = *(short*) (d2_FileObjTable + 0x52 + rec * 0x54);
			d2_DrawSpriteFromSet(*(int*) (b + 4), *(int*) (b + 8), a1, surf, 0);
			d2_DrawSpriteFromSet(*(int*) (b + 4) - horiz + w, *(int*) (b + 8), a1, surf, 1);
			d2_DrawSpriteFromSet(*(int*) (b + 4), *(int*) (b + 8) - cornerHeight + h, a1, surf, 2);
			d2_DrawSpriteFromSet(*(int*) (b + 4) - horiz + w, *(int*) (b + 8) - cornerHeight + h, a1, surf, 3);
			step = *(short*) (d2_FileObjTable + 0x1a0 + *(int*) (b + 0x288) * 0x54);
			h = *(short*) (d2_FileObjTable + 0x1a2 + *(int*) (b + 0x288) * 0x54);
			count = (*(int*) (b + 0xc) - horiz * 2) / step;
			off = 0;
			i = 0;
			if (count >= 1) {
				do {
					d2_DrawSpriteFromSet(*(int*) (b + 4) + off + horiz, *(int*) (b + 8) + 10, a1, surf, i % 4 + 4);
					d2_DrawSpriteFromSet(*(int*) (b + 4) + off + horiz, (*(int*) (b + 8) - h) - 0xb + *(int*) (b + 0x10), a1, surf, i % 4 + 4);
					off += step;
					i++;
				} while (i < count);
			}
			step = *(short*) (d2_FileObjTable + 0x398 + *(int*) (b + 0x288) * 0x54);
			vert = *(short*) (d2_FileObjTable + 0x39a + *(int*) (b + 0x288) * 0x54);
			count = (*(int*) (b + 0x10) - cornerHeight * 2) / vert;
			i = 0;
			if (count >= 1) {
				while (1) {
					if (i) {
						if (i == count - 1) {
							d2_DrawSpriteFromSet(*(int*) (b + 4) + 10, *(int*) (b + 8) + vert * i + cornerHeight, a1, surf, 9);
							d2_DrawSpriteFromSet((*(int*) (b + 4) - step) - 10 + *(int*) (b + 0xc), *(int*) (b + 8) + vert * i + cornerHeight, a1, surf, 9);
						} else {
							d2_DrawSpriteFromSet(*(int*) (b + 4) + 10, *(int*) (b + 8) + vert * i + cornerHeight, a1, surf, i % 4 + 10);
							d2_DrawSpriteFromSet((*(int*) (b + 4) - step) - 10 + *(int*) (b + 0xc), *(int*) (b + 8) + vert * i + cornerHeight, a1, surf, (i - 1) % 4 + 10);
						}
					} else {
						d2_DrawSpriteFromSet(*(int*) (b + 4) + 10, *(int*) (b + 8) + cornerHeight, a1, surf, 8);
						d2_DrawSpriteFromSet((*(int*) (b + 4) - step) - 10 + *(int*) (b + 0xc), *(int*) (b + 8) + cornerHeight, a1, surf, 8);
					}
					i++;
					if (i >= count) {
						break;
					}
				}
			}
		} else {
			d2_DrawSpriteFromSet(*(int*) (b + 4), *(int*) (b + 8), a1, surf, 0);
			d2_DrawSpriteFromSet(*(int*) (b + 4) - 8 + w, *(int*) (b + 8), a1, surf, 1);
			d2_DrawSpriteFromSet(*(int*) (b + 4), *(int*) (b + 8) - 8 + h, a1, surf, 2);
			d2_DrawSpriteFromSet(*(int*) (b + 4) - 8 + w, *(int*) (b + 8) - 8 + h, a1, surf, 3);
			count = (w - 0x10) >> 3;
			i = 0;
			if (count >= 1) {
				do {
					d2_DrawSpriteFromSet(*(int*) (b + 4) + 8 + i * 8, *(int*) (b + 8), a1, surf, 5);
					d2_DrawSpriteFromSet(*(int*) (b + 4) + 8 + i * 8, *(int*) (b + 8) - 8 + h, a1, surf, 8);
					i++;
				} while (i < count);
			}
			count = (h - 0x10) >> 3;
			i = 0;
			if (count >= 1) {
				do {
					d2_DrawSpriteFromSet(*(int*) (b + 4), *(int*) (b + 8) + 8 + i * 8, a1, surf, 0xb);
					d2_DrawSpriteFromSet(*(int*) (b + 4) - 8 + w, *(int*) (b + 8) + 8 + i * 8, a1, surf, 0xd);
					i++;
				} while (i < count);
			}
			if ((char) (*(unsigned int*) (b + 0x14) >> 8) < 0) {
				d2_DrawSpriteFromSet(*(int*) (b + 4) - 2, *(int*) (b + 8) - 2, a1, surf, 0x10);
				d2_DrawSpriteFromSet(*(int*) (b + 4) - 6 + w, *(int*) (b + 8) - 2, a1, surf, 0x10);
				d2_DrawSpriteFromSet(*(int*) (b + 4) - 2, *(int*) (b + 8) - 6 + h, a1, surf, 0x10);
				d2_DrawSpriteFromSet(*(int*) (b + 4) - 6 + w, *(int*) (b + 8) - 6 + h, a1, surf, 0x10);
			}
		}
	}
	if (*(int*) (b + 0x280)) {
		*(int*) (b + 0x280) = *(int*) (b + 0x280) - 1;
	}
	d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
}
