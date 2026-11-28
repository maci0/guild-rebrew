

#include "Develop/client_types.h"

#include "Develop/Units/d3/client_lighting.h"

/* ADDRESS: GOLDDE 0x0040da60 */
int __cdecl d3_SetSceneLightColor(int* a, int* b, int* c)
{
	d3_SceneAmbientColor.x = (float) *a;
	d3_SceneAmbientColor.y = (float) *b;
	d3_SceneAmbientColor.z = (float) *c;
	UpdateSceneLighting(1);
	return 1;
}
