extern char* evt_CurrentScript;
extern char g_676bfc[];


// SIZE 0xcd
typedef struct {
	char pad[0xcc];
	unsigned char b0 : 5;
	unsigned char b5 : 1;
} S4105a0;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl fcn_0040f690(S4105a0** object, char* flag)
{
	S4105a0* p;

	p = *object;
	if (m_is_tracked(p) == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) ((char*) evt_CurrentScript + 0x118), g_676bfc);
		return 0;
	}
	p->b5 = *flag;
	return 0;
}
