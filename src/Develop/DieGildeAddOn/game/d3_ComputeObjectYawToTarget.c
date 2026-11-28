


#include "Develop/DieGildeAddOn/game/game_data.h"
extern float d3_UnitAxisVectors[3];

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_TransformDirection(int, float*, float*);
float __cdecl d3_SignedPlanarAngle(float*, float*);

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
	d3_TransformDirection(obj, d3_UnitAxisVectors, v);
	out[1] = d3_SignedPlanarAngle(d3_UnitAxisVectors, v);
	d3_SelectSceneContext(save, 1);
}
