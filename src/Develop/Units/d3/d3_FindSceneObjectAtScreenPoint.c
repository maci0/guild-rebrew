


// SIZE 0x8
typedef struct Hit {
	char* e;
	float d;
} Hit;

// SIZE 0x58
typedef struct Ctx {
	Hit hits[9];
	char* cam;
	int mask;
	float x;
	float y;
} Ctx;

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/d3_camera.h"
extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
char __cdecl d3_PickClosestObjectCallback(char*, char*);

char* __cdecl d3_FindSceneObjectAtScreenPoint(float a, float b, int flags, int mask)
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
	ctx.x = d3_ViewportCenterX - a;
	ctx.cam = d3_ActiveCamera;
	ctx.mask = mask;
	ctx.y = g_1052bc8 - b;
	d3_VisitSceneObjects(d3_ActiveScene, 0, flags, d3_PickClosestObjectCallback, &ctx);
	for (i = 0; i < 9; i++) {
		if (ctx.hits[i].e != 0 && ctx.hits[i].d < best) {
			r = ctx.hits[i].e;
			best = ctx.hits[i].d;
		}
	}
	return r;
}
