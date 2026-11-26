


#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_662d40[3];

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_00455140(int, float*, float*);
float __cdecl fcn_00451380(float*, float*);

void __cdecl d3_ComputeObjectYawToTarget(float* out, int obj)
{
	float v[3];
	int save;

	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	out[0] = 0;
	out[1] = 0;
	out[2] = 0;
	fcn_00455140(obj, g_662d40, v);
	out[1] = fcn_00451380(g_662d40, v);
	d3_SelectSceneContext(save, 1);
}
