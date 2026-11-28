


extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char io_LastKeyScancode;

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
void __cdecl io_ClearInputState(void);

void __cdecl evt_WaitAndCancelScript(int id)
{
	int r;

	if (cut_SkipMode != 0)
		return;
	if (main_RunFrameLoop(0, 0x7d6c6) != 0) {
		do {
			if (io_RightButtonReleased != 0 || io_LastKeyScancode != 0)
				break;
			if (evt_FindScriptById(id) == 0)
				return;
		} while (main_RunFrameLoop(0, 0x7d6c6) != 0);
	}
	r = evt_FindScriptById(id);
	if (r != 0)
		evt_RequestScriptExit(r);
	io_ClearInputState();
}
