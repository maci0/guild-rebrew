#include "Develop/DieGildeAddOn/game/game_data.h"



void __cdecl d3_SelectSceneContext(int, int);
#include "client_scene_transform.h"

void __cdecl d3_GetObjectWorldPosition(float* result, char* object)
{
	float v[4];
	int saved;

	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	fcn_00455540(object, v, result);
	d3_SelectSceneContext(saved, 1);
}
