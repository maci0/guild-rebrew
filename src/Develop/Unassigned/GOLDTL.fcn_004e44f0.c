


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);

void __cdecl cut_WaitForScript(int scriptId)
{
	if (g_772f3c == 0 && main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) != 0) {
		while (evt_FindScriptById(scriptId) != 0 && main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) != 0) {
		}
	}
}
