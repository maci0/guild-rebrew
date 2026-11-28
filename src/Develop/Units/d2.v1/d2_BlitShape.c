#pragma pack(push, 1)
// SIZE 0x2a
typedef struct {
	char p0[6];
	unsigned short h;
	char p8[4];
	unsigned char kind;
	char pd[0x19];
	int x26;
} Spr;
#pragma pack(pop)

// SIZE 0x20
typedef struct {
	char p0[0x10];
	int x10;
	char p14[8];
	int bits;
} Surf;

extern int shp_SuppressDraw;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_RenderSurfaceWidth;
extern int shp_ShapeBlendMode;

void __cdecl d2_StoreShapeSize(int, int, Surf*, Spr*);
void __cdecl d2_ClearLastSpriteSize(int, int, int, Spr*);
void __cdecl d2_BlitRleSprite(int, int, int, Spr*);
void __cdecl d2_ClearDrawnShapeSize(int, int, int, Spr*);
void __cdecl d2_ClearDrawnSpriteSize(int, int, int, Spr*);


/* ADDRESS: GOLDTL 0x00478fc0 */
int __cdecl d2_BlitShape(int x, int y, Surf* s, Spr* spr)
{
	int saved;
	int right;
	int h;

	if (shp_SuppressDraw == 0) {
		if (spr->x26 != -1) {
			h = spr->h;
			if (x <= d2_ClipRight) {
				if (h + x >= d2_ClipLeft) {
					right = h + x;
					saved = d2_RenderSurfaceWidth;
					d2_RenderSurfaceWidth = s->x10;
					switch (spr->kind) {
					case 0:
						if (shp_ShapeBlendMode == 0) {
							d2_ClearDrawnShapeSize(x, y, s->bits, spr);
						} else {
							d2_ClearDrawnSpriteSize(x, y, s->bits, spr);
						}
						return 1;
					case 1:
						if (x < d2_ClipLeft) {
							d2_ClearLastSpriteSize(x, y, s->bits, spr);
						} else if (right > d2_ClipRight) {
							d2_ClearLastSpriteSize(x, y, s->bits, spr);
						} else {
							d2_BlitRleSprite(x, y, s->bits, spr);
						}
						return 1;
					case 2:
						return 1;
					}
					d2_RenderSurfaceWidth = saved;
				}
			}
		} else {
			switch (spr->kind) {
			case 0:
				return 0;
			case 2:
				return 1;
			case 1:
				d2_StoreShapeSize(x, y, s, spr);
				return 1;
			}
		}
	}
	return 0;
}
