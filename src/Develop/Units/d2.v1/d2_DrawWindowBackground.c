#include "Develop/Units/d2.v1/d2_surface.h"








typedef struct
{
	char pad0[0x50];
	int color;
} D2_BG_PALETTE;

typedef struct
{
	char pad0[0x50];
	short w;
	short h;
} D2_BG_TEX_DEF;
// SIZE 0x54

// SIZE 0x3cc
typedef struct
{
	int pad0;
	int x;
	int y;
	int w;
	int h;
	int flags;
	char pad18[0x38 - 0x18];
	D2_SURFACE* surf;
	char pad3c[0x258 - 0x3c];
	int sy;
	char pad25c[0x268 - 0x25c];
	int sx;
	char pad26c[0x398 - 0x26c];
	int tex;
	char pad39c[4];
	D2_BG_PALETTE* pal;
	float alpha;
	int ml;
	int mt;
	int mr;
	int mb;
	char pad3b8[0x3c8 - 0x3b8];
	int img;
} D2_BG_WINDOW;


extern char* d2_BlackTexture;
extern char* d2_FileObjTable;
#include "Develop/DieGildeAddOn/game/game_data.h"

void* __cdecl d2_QueueTexturedQuad(int x, int y, int w, int h, int a5, void* r);
void __cdecl d2_SetQuadVertexColor(void* p, int r, int g, int b);
void __cdecl d2_DrawTexturedQuad(int x, int y, int w, int h, int color, float alpha);
void __cdecl d2_DrawSprite(int x, int y, int a3, int img);
int __cdecl d2_GetResourceData(int id);
void __cdecl d2_SetClipRect(int a, int b, int c, int d);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, int tex, int c);
void __cdecl d2_DrawSurfaceQuad(int x, int y, int w, int h, int bits, float alpha);

/* ADDRESS: GOLDTL 0x0046dd60 */
void __cdecl d2_DrawWindowBackground(D2_BG_WINDOW* w, int dst)
{
	void* p;
	D2_BG_TEX_DEF* d;
	int tex;
	int x0;
	int y0;
	int cw;
	int ch;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;
	int oy;
	int i;
	int rows;

	if (w->flags & 0x400) {
		p = d2_QueueTexturedQuad(w->x, w->y, w->w, w->h, (int) d2_WhiteSurface->surface, 0);
		if (p != 0)
			d2_SetQuadVertexColor(p, 0, 0, 0);
	}
	x0 = w->ml + w->x;
	y0 = w->mt + w->y;
	cw = w->w - w->mr - w->ml;
	ch = w->h - w->mb - w->mt;
	if (w->flags & 1)
		d2_DrawTexturedQuad(x0, y0, cw, ch, ((D2_BG_PALETTE*)d2_BlackTexture)->color, w->alpha);
	else if (w->pal != 0)
		d2_DrawTexturedQuad(x0, y0, cw, ch, w->pal->color, w->alpha);
	else if (w->img != 0)
		d2_DrawSprite(w->x - w->sx, w->y - w->sy, dst, w->img);
	if (w->tex != -1 && (tex = d2_GetResourceData(w->tex)) != 0) {
		clipLeft = d2_ClipLeft;
		clipTop = g_7725fc;
		clipRight = d2_ClipRight;
		clipBottom = d2_ClipBottom;
		d2_SetClipRect(w->x, w->y, w->w + w->x, w->h + w->y);
		d = &((D2_BG_TEX_DEF*)d2_FileObjTable)[w->tex];
		if (w->sy >= 0)
			oy = w->y - w->sy % d->h;
		else
			oy = w->y - w->sy % d->h - d->h;
		for (rows = 0; rows < w->h / d->h + 1.5; rows++) {
			for (i = 0; i < w->w / d->w; i++)
				d2_DrawSpriteFromSet(w->x + d->w * i, d->h * rows + oy, dst, tex, 0);
		}
		d2_SetClipRect(clipLeft, clipTop, clipRight, clipBottom);
	}
	if (w->surf != 0)
		d2_DrawSurfaceQuad(w->x, w->y, w->surf->width, w->surf->height, (int) w->surf->surface, 1.0f);
}
