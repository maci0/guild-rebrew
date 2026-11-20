


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_005373e0(void*, int);
int __cdecl evt_FindScriptById(int);

int __cdecl cut_WaitForScriptOrInput(int id, int(__cdecl* cb)(int), int arg)
{
	if (g_772f3c != 0)
		return 0;
	if (fcn_005373e0(0, cut_EventLoopFlags | 0x8000) == 0)
		return 0;
	do {
		if (evt_FindScriptById(id) == 0)
			return 0;
		if (g_14ce8e0 != 0) {
			if (cb != 0)
				return cb(arg);
			return 1;
		}
	} while (fcn_005373e0(0, cut_EventLoopFlags | 0x8000) != 0);
	return 0;
}
