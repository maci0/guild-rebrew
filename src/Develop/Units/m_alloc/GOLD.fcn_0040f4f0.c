

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl d3_UpdateParticleTimeAndAlpha(char** a, int* x, int* y, int* z, int* w)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	*(int*) (e + 0xbc) = *x;
	*(int*) (e + 0xc0) = *y;
	*(int*) (e + 0xc4) = *z;
	*(float*) (e + 0xb8) = (float) *w;
	return 0;
}
