


extern volatile int gm_GameTicks;
extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateFloatingStatTexts(void);
void __cdecl d2_AppendPendingPlayerNames(int);

void __cdecl cut_WaitSeconds(int secs)
{
	int start;
	double end;

	start = (*(unsigned int*)&gm_GameTicks);
	if (cut_SkipMode != 0)
		return;
	if (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) == 0)
		return;
	end = secs * (1.0 / 14.0) + start;
	do {
		if ((*(unsigned int*)&gm_GameTicks) >= end)
			d2_DialogCloseRequested = 1;
		d2_UpdateFloatingStatTexts();
		d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
	} while (main_RunFrameLoop(cut_WaitSeconds, cut_EventLoopFlags | 0x8000) != 0);
}
