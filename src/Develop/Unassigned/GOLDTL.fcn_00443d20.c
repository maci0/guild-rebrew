

// SIZE 0x8
typedef struct Hit {
	char* e;
	float d;
} Hit;

// SIZE 0x58
typedef struct Ctx {
	Hit hits[9];
	int cam;
	int mask;
	float x;
	float y;
} Ctx;

extern char g_6b85a0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
char __cdecl d3_PickClosestObjectCallback(char*, char*);

char* __cdecl d3_PickObject(int cam, float a, float b, int flags)
{
	float best;
	Ctx ctx;
	char* r = 0;
	unsigned int i;

	best = 1.0e10f;
	for (i = 0; i < 9; i++) {
		ctx.hits[i].d = 1.0e10f;
		ctx.hits[i].e = 0;
	}
	ctx.mask = 0;
	ctx.cam = cam;
	if (g_6b85a0 != 0) {
		ctx.x = (d3_ViewportRight - g_1042570) * 0.5f - a;
		ctx.y = (d3_ViewportBottom - g_1042574) * 0.5f - b;
	} else {
		ctx.x = d3_ViewportCenterX - a;
		ctx.y = g_1052bc8 - b;
	}
	d3_VisitSceneObjects(g_67a370, 0, flags, d3_PickClosestObjectCallback, &ctx);
	for (i = 0; i < 9; i++) {
		if (ctx.hits[i].e != 0 && ctx.hits[i].d < best) {
			r = ctx.hits[i].e;
			best = ctx.hits[i].d;
		}
	}
	return r;
}
