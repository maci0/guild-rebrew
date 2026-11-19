extern char* evt_CurrentScript;
extern char g_676cf8[];


#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl fcn_0040f8a0(char** objectRef)
{
	char* p;

	p = *objectRef;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676cf8);
		return 0;
	}
	p[0xcd] |= 2;
	return 0;
}
