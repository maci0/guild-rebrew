extern char* evt_CurrentScript;
extern char g_676c24[];


// SIZE 0xcd
typedef struct {
	char pad[0xcc];
	unsigned char b0 : 6;
	unsigned char b6 : 1;
} S410600;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl fcn_0040f6f0(S410600** objectRef, char* flag)
{
	S410600* p;

	p = *objectRef;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676c24);
		return 0;
	}
	p->b6 = *flag;
	return 0;
}
