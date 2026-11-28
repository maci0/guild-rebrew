

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040ef60 */
int __cdecl SetEmitterDirection(char** a, int* x, int* y, int* z)
{
	char* e;
	float fx;
	float fy;
	float fz;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	fx = *x * 0.01f;
	fy = *y * 0.01f;
	fz = *z * 0.01f;
	*(float*) (e + 0x74) = fx;
	*(float*) (e + 0x78) = fy;
	*(float*) (e + 0x7c) = fz;
	return 0;
}
