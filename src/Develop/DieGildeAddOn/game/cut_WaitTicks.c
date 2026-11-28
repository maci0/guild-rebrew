


extern int cut_SkipMode;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateFloatingStatTexts(void);
void __cdecl d2_AppendPendingPlayerNames(int);

/* ADDRESS: GOLDDE 0x004d1610 */
void __cdecl cut_WaitTicks(int dur)
{
	int end;

	end = cut_CurrentTick;
	if (cut_SkipMode != 0)
		return;
	if (main_RunFrameLoop(cut_WaitTicks, cut_EventLoopFlags | 0x8000) == 0)
		return;
	do {
		if (cut_CurrentTick >= end + dur)
			d2_DialogCloseRequested = 1;
		d2_UpdateFloatingStatTexts();
		d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
	} while (main_RunFrameLoop(cut_WaitTicks, cut_EventLoopFlags | 0x8000) != 0);
}
