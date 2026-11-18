

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl SetEmitterColor(char** a, char* r, char* g, char* b, char* al)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	e[0xd2] = *r;
	e[0xd1] = *g;
	e[0xd0] = *b;
	e[0xd3] = *al;
	return 0;
}
