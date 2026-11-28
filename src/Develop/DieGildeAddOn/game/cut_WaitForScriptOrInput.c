


extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl main_RunFrameLoop(void*, int);
int __cdecl evt_FindScriptById(int);

int __cdecl cut_WaitForScriptOrInput(int id, int(__cdecl* cb)(int), int arg)
{
	if (cut_SkipMode != 0)
		return 0;
	if (main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) == 0)
		return 0;
	do {
		if (evt_FindScriptById(id) == 0)
			return 0;
		if (io_RightButtonReleased != 0) {
			if (cb != 0)
				return cb(arg);
			return 1;
		}
	} while (main_RunFrameLoop(0, cut_EventLoopFlags | 0x8000) != 0);
	return 0;
}
