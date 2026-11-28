extern char* evt_CurrentScript;
extern char str_TriggerEmitter_invalid_handle[];


#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl d3_TriggerEmitter(char** objectRef)
{
	char* p;

	p = *objectRef;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), str_TriggerEmitter_invalid_handle);
		return 0;
	}
	p[0xcd] |= 2;
	return 0;
}
