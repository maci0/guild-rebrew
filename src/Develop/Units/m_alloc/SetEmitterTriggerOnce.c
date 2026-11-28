

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

extern char* evt_CurrentScript;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char* g, int h, const char* msg);

/* ADDRESS: GOLDDE 0x0040f510 */
int __cdecl SetEmitterTriggerOnce(char** a, unsigned char* v)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "invalid object");
		return 0;
	}
	((Bits*) (e + 0xd4))->g0 = *v;
	return 0;
}
