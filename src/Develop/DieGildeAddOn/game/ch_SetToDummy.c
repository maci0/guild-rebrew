#include "Develop/DieGildeAddOn/game/ch_motion.h"



extern float g_662d40[3];
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl d3_TransformDirection(char* src, float* v, float* out);
float __cdecl d3_SignedPlanarAngle(float* a, float* b);
void __cdecl d3_SetObjectRotation(char* h, float* v);

void __cdecl ch_SetToDummy(char* obj, char* src)
{
	float v[3];
	float b[3];
	float a[4];

	if (obj != 0) {
		d3_TransformPoint(src, src + 0x4c, a);
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		d3_TransformDirection(src, g_662d40, b);
		v[1] = d3_SignedPlanarAngle(g_662d40, b);
		d3_SetObjectRotation(*(char**) (obj + 0x34), v);
		ch_SetPosition(obj, a, 1);
	}
}
