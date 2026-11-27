

#include "client_scene_loader.h"

extern int g_67a370;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
#include "client_lighting.h"

void __cdecl d3_ReloadSceneResources(int mask, int b, SCENE_PROGRESS a)
{
	SCENE_PROGRESS_CONTEXT s;

	s.skip = 1;
	s.count = 0;
	s.total = 0;
	s.fn = a;
	s.id = b;
	d3_VisitSceneObjects(g_67a370, 0, mask, d3_ReloadObjectResourcesCallback, &s);
	s.skip = 0;
	d3_VisitSceneObjects(g_67a370, 0, mask, d3_ReloadObjectResourcesCallback, &s);
	d3_ReloadSceneTextureSurfaces(a);
	UpdateSceneLighting(1);
}
