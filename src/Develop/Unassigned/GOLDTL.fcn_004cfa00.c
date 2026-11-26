


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf950;

int __cdecl main_RunFrameLoop(int, int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
void __cdecl io_ClearInputState(void);

void __cdecl fcn_004cfa00(int id)
{
	int r;

	if (g_772f3c != 0)
		return;
	if (main_RunFrameLoop(0, 0x7d6c6) != 0) {
		do {
			if (g_14ce8e0 != 0 || g_14cf950 != 0)
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
