#include "Develop/DieGildeAddOn/game/game_data.h"



void __cdecl d3_SelectSceneContext(int, int);
#include "Develop/Units/d3/client_scene_transform.h"

/* ADDRESS: GOLDDE 0x0057dea0 */
void __cdecl d3_GetObjectWorldPosition(float* result, char* object)
{
	float v[4];
	int saved;

	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	d3_TransformToObjectSpace(object, v, result);
	d3_SelectSceneContext(saved, 1);
}
