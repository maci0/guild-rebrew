

#include "Develop/Units/m_alloc/m_alloc_checks.h"
int __cdecl fcn_00452420(int);
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl KillEmitter(int* allocation)
{
	if (m_is_tracked((void*) *allocation) != 0) {
		fcn_00452420(*allocation);
	} else {
		evt_LogScriptError(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676a28);
	}
	return 0;
}
