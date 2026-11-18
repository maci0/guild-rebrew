#include "Develop/Units/m_alloc/m_alloc_checks.h"

extern char* evt_CurrentScript;
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

/* ADDRESS: GOLDTL 0x00410760 */
int __cdecl SetEmitterMaxTrigger(char** a, int* c)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "SetEmitterMaxTris");
		return 0;
	}
	*(float*) (e + 0xb4) = (float) *c;
	return 0;
}
