#include "Develop/DieGildeAddOn/game/ch_script.h"



extern char* evt_CurrentScript;
float __cdecl d3_ComputeYawToTarget(int h, char* pos);
void __cdecl d3_WrapEulerAnglesPi(float* out, char* base, float* a, float* b);
char* __cdecl ch_CreateAction(char* e, int kind, ...);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040cad0 */
int __cdecl LookAtCharacter(char** a, char** b)
{
	float d;
	float v[3];
	float w[3];
	float u[3];
	char* e;

	if (*a == 0 || *b == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	d = d3_ComputeYawToTarget(*(int*) (*a + 0x34), *(char**) (*b + 0x34) + 0x4c);
	v[0] = 0.0f;
	v[1] = d;
	v[2] = 0.0f;
	d3_WrapEulerAnglesPi(v, *(char**) (*a + 0x34) + 0x84, u, w);
	e = *a;
	v[0] += *(float*) (*(char**) (e + 0x34) + 0x84);
	v[1] += *(float*) (*(char**) (e + 0x34) + 0x88);
	v[2] += *(float*) (*(char**) (e + 0x34) + 0x8c);
	ch_CreateAction(e, 7, (int) (d * 57.29578f), 0);
	return 0;
}
