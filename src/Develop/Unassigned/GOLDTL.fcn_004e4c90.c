


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "client_dialog_state.h"

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl d2_AppendPendingPlayerNames(int);

void __cdecl cut_WaitTicks(int dur)
{
	int end;

	end = cut_CurrentTick;
	if (g_772f3c != 0)
		return;
	if (fcn_005373e0(cut_WaitTicks, cut_EventLoopFlags | 0x8000) == 0)
		return;
	do {
		if (cut_CurrentTick >= end + dur)
			g_774654 = 1;
		fcn_004cfca0();
		d2_AppendPendingPlayerNames((*(int*)&cut_ActiveCutscene));
	} while (fcn_005373e0(cut_WaitTicks, cut_EventLoopFlags | 0x8000) != 0);
}
