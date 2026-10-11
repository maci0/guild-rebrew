#include "msx.h"

void __cdecl fcn_004200d0(const char* name, int a2)
{
	Chan_14cc460* p;

	if (g_6b71a4 != 0) {
		EnterCriticalSection(&g_14cc5a0);
		p = FindTrackByName(name);
		LeaveCriticalSection(&g_14cc5a0);
		if (p != 0) {
			fcn_00420120(p, a2);
		}
	}
}
