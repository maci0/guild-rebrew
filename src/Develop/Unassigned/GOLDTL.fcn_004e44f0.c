


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_005373e0(int, int);
int __cdecl evt_FindScriptById(int);

void __cdecl fcn_004e44f0(int a1)
{
	if (g_772f3c == 0 && fcn_005373e0(0, cut_EventLoopFlags | 0x8000) != 0) {
		while (evt_FindScriptById(a1) != 0 && fcn_005373e0(0, cut_EventLoopFlags | 0x8000) != 0) {
		}
	}
}
