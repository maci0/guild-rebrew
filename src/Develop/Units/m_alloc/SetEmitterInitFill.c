extern char g_6b7e98[];


// SIZE 0xd5
typedef struct {
	char pad[0xd4];
	unsigned char b0 : 5;
	unsigned char b5 : 1;
} S4105a0;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040f3a0 */
int __cdecl SetEmitterInitFill(S4105a0** a1, char* fill)
{
	S4105a0* emitter;

	emitter = *a1;
	if (m_is_tracked(emitter) == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "SetEmitterInitFill: invalid handle...");
		return 0;
	}
	emitter->b5 = *fill;
	return 0;
}
