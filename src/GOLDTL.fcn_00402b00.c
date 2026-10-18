#include "Develop/DieGildeAddOn/game/ch_motion.h"



extern float g_662d40[3];
void __cdecl fcn_00455350(char* src, char* pos, float* out);
void __cdecl fcn_00455140(char* src, float* v, float* out);
float __cdecl fcn_00451380(float* a, float* b);
void __cdecl fcn_00438cb0(char* h, float* v);

void __cdecl fcn_00402b00(char* obj, char* src)
{
	float v[3];
	float b[3];
	float a[4];

	if (obj != 0) {
		fcn_00455350(src, src + 0x4c, a);
		v[0] = 0.0f;
		v[1] = 0.0f;
		v[2] = 0.0f;
		fcn_00455140(src, g_662d40, b);
		v[1] = fcn_00451380(g_662d40, b);
		fcn_00438cb0(*(char**) (obj + 0x34), v);
		ch_SetPosition(obj, a, 1);
	}
}
