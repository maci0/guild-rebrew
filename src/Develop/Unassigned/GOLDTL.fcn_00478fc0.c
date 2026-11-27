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

extern int g_100ef80;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d96c;
extern int g_100f1bc;

void __cdecl d2_StoreShapeSize(int, int, Surf*, Spr*);
void __cdecl fcn_004774e0(int, int, int, Spr*);
void __cdecl fcn_0047a320(int, int, int, Spr*);
void __cdecl d2_ClearDrawnShapeSize(int, int, int, Spr*);
void __cdecl d2_ClearDrawnSpriteSize(int, int, int, Spr*);


/* ADDRESS: GOLDTL 0x00478fc0 */
int __cdecl d2_BlitShape(int x, int y, Surf* s, Spr* spr)
{
	int saved;
	int right;
	int h;

	if (g_100ef80 == 0) {
		if (spr->x26 != -1) {
			h = spr->h;
			if (x <= d2_ClipRight) {
				if (h + x >= d2_ClipLeft) {
					right = h + x;
					saved = g_67d96c;
					g_67d96c = s->x10;
					switch (spr->kind) {
					case 0:
						if (g_100f1bc == 0) {
							d2_ClearDrawnShapeSize(x, y, s->bits, spr);
						} else {
							d2_ClearDrawnSpriteSize(x, y, s->bits, spr);
						}
						return 1;
					case 1:
						if (x < d2_ClipLeft) {
							fcn_004774e0(x, y, s->bits, spr);
						} else if (right > d2_ClipRight) {
							fcn_004774e0(x, y, s->bits, spr);
						} else {
							fcn_0047a320(x, y, s->bits, spr);
						}
						return 1;
					case 2:
						return 1;
					}
					g_67d96c = saved;
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
