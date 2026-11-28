extern char g_6b7e98[];


#include "Develop/Units/m_alloc/m_alloc_checks.h"
int __cdecl d3_FreeMeshObject(int);
void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040edd0 */
int __cdecl KillEmitter(int* allocation)
{
	if (m_is_tracked((void*) *allocation) != 0) {
		d3_FreeMeshObject(*allocation);
	} else {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "KillEmitter: invalid handle...");
	}
	return 0;
}
