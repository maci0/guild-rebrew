#include "msx.h"

void __cdecl fcn_0041fbd0(const char* name, int a2)
{
	Chan_14cc460* p;

	if (g_6b71a4 != 0) {
		EnterCriticalSection(&g_14cc5a0);
		p = FindTrackByName(name);
		if (p != 0) {
			fcn_0041fc10(p, a2);
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
}
