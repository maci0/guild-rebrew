extern char g_6b7e98[];


// SIZE 0xd5
typedef struct {
	char pad[0xd4];
	unsigned char b0 : 6;
	unsigned char b6 : 1;
} S410600;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040f400 */
int __cdecl SetEmitterRebirthFill(S410600** emitter, char* value)
{
	S410600* p;

	p = *emitter;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "SetEmitterRebirthFill: invalid handle...");
		return 0;
	}
	p->b6 = *value;
	return 0;
}
