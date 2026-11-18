

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl SetEmitterTimeAndAlpha(char** a, int* x, int* y, int* z, int* w)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	*(int*) (e + 0xc4) = *x;
	*(int*) (e + 0xc8) = *y;
	*(int*) (e + 0xcc) = *z;
	*(float*) (e + 0xc0) = (float) *w;
	return 0;
}
