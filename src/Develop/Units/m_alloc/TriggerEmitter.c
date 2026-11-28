extern char g_6b7e98[];


#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040f560 */
/* ADDRESS: GOLDDE 0x0040f5b0 */
int __cdecl TriggerEmitter(char** emitterRef)
{
	char* p;

	p = *emitterRef;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "TriggerEmitter: invalid handle...");
		return 0;
	}
	p[0xd5] |= 2;
	return 0;
}
