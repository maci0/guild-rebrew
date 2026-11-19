


extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_004526d0(char* e, float* v);
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SetParticlePos(char** a, int* x, int* y, int* z)
{
	float v[4];
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	v[0] = (float) *x;
	v[1] = (float) *y;
	v[2] = (float) *z;
	fcn_004526d0(e, v);
	return 0;
}
