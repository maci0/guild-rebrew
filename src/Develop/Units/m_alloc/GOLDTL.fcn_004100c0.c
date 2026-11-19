

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

int __cdecl SetEmitterPhasespeed(char** a, int* x, int* y, int* z, int* w, int* v)
{
	char* e;
	float fx;
	float fy;
	float fz;
	float fw;
	float fv;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	fx = *x * 0.01f;
	fy = *y * 0.01f;
	fz = *z * 0.01f;
	fv = *v * 0.01f;
	fw = *w * 0.01f;
	*(float*) (e + 0x58) = fx;
	*(float*) (e + 0x5c) = fy;
	*(float*) (e + 0x60) = fz;
	*(float*) (e + 0x64) = fw;
	*(float*) (e + 0xbc) = fv;
	return 0;
}
