


extern volatile int gm_GameTicks;
extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateFloatingStatTexts(void);
void __cdecl d2_AppendPendingPlayerNames(int);
void __cdecl cut_WaitSeconds(int);

/* ADDRESS: GOLDDE 0x004d1680 */
int __cdecl cut_WaitForTimeoutOrInput(int secs, int(__cdecl* cb)(int), int arg)
{
	int start;
	int res;

	start = (*(unsigned int*)&gm_GameTicks);
	res = 0;
	if (cut_SkipMode != 0)
		return 0;
	if (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) != 0) {
		do {
			if (io_RightButtonReleased != 0) {
				if (cb != 0)
					res = cb(arg);
				else
					res = 1;
				d2_DialogCloseRequested = 1;
			} else if ((*(unsigned int*)&gm_GameTicks) >= secs * (1.0 / 14.0) + start) {
				d2_DialogCloseRequested = 1;
			}
			d2_UpdateFloatingStatTexts();
			d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
		} while (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) != 0);
	}
	return res;
}
