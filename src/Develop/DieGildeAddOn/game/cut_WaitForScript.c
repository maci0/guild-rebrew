


extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);

/* ADDRESS: GOLDDE 0x004d0ee0 */
void __cdecl cut_WaitForScript(int scriptId)
{
	if (cut_SkipMode == 0 && main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) != 0) {
		while (evt_FindScriptById(scriptId) != 0 && main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) != 0) {
		}
	}
}
