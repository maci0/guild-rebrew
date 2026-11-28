#include <stdio.h>
#include <string.h>

// SIZE 0xc
typedef struct {
	int id;
	int value;
	int p8;
} Item;

// SIZE 0x14
typedef struct {
	char p0[0xe];
	short x;
	short y;
	char p12[2];
} Slot;

// SIZE 0x54
typedef struct {
	char p0[0x50];
	short x50;
	char p52[2];
} Cls;

// SIZE 0xc
typedef struct {
	char p0[4];
	int w;
	int h;
} Ctx;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d8cc;
extern short g_7725c4;
extern char* g_7725c0;
#include "Develop/client_types.h"
extern Anim_100e7a0 g_100e7a0[0x30];

extern char* g_772500;
extern int g_67d3ac;
extern int d2_ResourceOffset;
extern char* g_14a567c;

void __cdecl d2_SetClipRect(int, int, int, int);
void __cdecl d2_DrawSpriteFromSet(int, int, Ctx*, int, int);
void __cdecl d2_DrawAnimationSlot(int, Ctx*);
void __cdecl d2_SelectFont(int);
int __cdecl d2_GetResourceData(int);
int __cdecl d2_DrawScaledSpriteQuad(int, int, Ctx*, int, int, float, int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, Ctx*, char*, int);


/* ADDRESS: GOLDTL 0x00473800 */
void __cdecl d2_DrawCursorAndCounters(Ctx* c, int x, int y)
{
	Item* p;
	int old;
	int y1;
	int x1;
	int y0;
	int x0;
	char buf[0x40];
	int k;
	int i;
	int px;
	int py;
	int h;
	int id;
	int v;

	if (d2_SuppressOverlay != 0) {
		return;
	}
	x0 = d2_ClipLeft;
	y0 = g_7725fc;
	x1 = d2_ClipRight;
	y1 = d2_ClipBottom;
	d2_SetClipRect(0, 0, c->w, c->h);
	if (g_67d8cc == -1) {
		d2_DrawSpriteFromSet(x, y, c, (*(int*)&g_7725c0), (*(int*)&g_7725c4) & 0xffff);
	} else {
		((Slot*)g_100e7a0)[g_67d8cc].x = (short) x;
		((Slot*)g_100e7a0)[g_67d8cc].y = (short) y;
		d2_DrawAnimationSlot(g_67d8cc, c);
	}
	old = d2_CurrentFont;
	d2_SelectFont(d2_DefaultFont + 1);
	k = 0;
	for (i = 0; i < 6; i++) {
		p = &((Item*)d2_DisplayCounters)[i];
		if (p->id != -1) {
			px = x + ((Cls*)g_772500)[g_67d3ac].x50 + k % 3 * 0x1a;
			py = (d2_FontHeight + 0x1a) * (k / 3) + y;
			h = d2_GetResourceData(p->id);
			if (d2_DrawScaledSpriteQuad(px, py, c, h, d2_ResourceOffset, 0.5f, 0)) {
				v = p->value;
				id = p->id;
				if (id >= 0xdf && id < 0x3bb) {
					if (v != -1) {
						sprintf(buf, "%i", v);
					} else {
						strcpy(buf, g_14a567c);
					}
				} else {
					sprintf(buf, "%i", v);
				}
				d2_DrawWordWrappedText(px - 8, py + 0x18, 0x28, d2_FontHeight, c, buf, 8);
			}
			k++;
		}
	}
	d2_SelectFont(old);
	d2_SetClipRect(x0, y0, x1, y1);
}
