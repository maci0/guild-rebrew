

#include "client_scene_loader.h"

extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
#include "client_lighting.h"

void __cdecl fcn_0043ac00(int mask, int b, SCENE_PROGRESS a)
{
	SCENE_PROGRESS_CONTEXT s;

	s.skip = 1;
	s.count = 0;
	s.total = 0;
	s.fn = a;
	s.id = b;
	fcn_004379a0(g_67a370, 0, mask, fcn_0043aad0, &s);
	s.skip = 0;
	fcn_004379a0(g_67a370, 0, mask, fcn_0043aad0, &s);
	fcn_0045cfa0(a);
	UpdateSceneLighting(1);
}
