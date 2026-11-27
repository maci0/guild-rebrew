

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl TriggerEmitter(char** emitterRef)
{
	char* p;

	p = *emitterRef;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676cf8);
		return 0;
	}
	p[0xd5] |= 2;
	return 0;
}
