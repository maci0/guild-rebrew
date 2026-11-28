#include "Develop/DieGildeAddOn/game/ch_script.h"
#include "Develop/DieGildeAddOn/game/ch_motion.h"



extern float d3_UnitAxisVectors[3];
extern char* evt_CurrentScript;
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
void __cdecl d3_TransformDirection(char* src, float* v, float* out);
float __cdecl d3_SignedPlanarAngle(float* a, float* b);
void __cdecl d3_SetObjectRotation(char* h, float* v);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SetCharacterToDummy(char** a, char** b)
{
	float v[3];
	float c[3];
	float p[4];

	if (*a == 0 || *b == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 1;
	}
	d3_TransformPoint(*b, *b + 0x4c, p);
	ch_SetPosition(*a, p, 1);
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	d3_TransformDirection(*b, d3_UnitAxisVectors, c);
	v[1] = d3_SignedPlanarAngle(d3_UnitAxisVectors, c);
	d3_SetObjectRotation(*(char**) (*a + 0x34), v);
	return 0;
}
