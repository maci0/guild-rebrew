


extern int g_772f3c;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "client_dialog_state.h"

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_004e5140(int);

void __cdecl fcn_004e4c90(int dur)
{
	int end;

	end = cut_CurrentTick;
	if (g_772f3c != 0)
		return;
	if (fcn_005373e0(fcn_004e4c90, cut_EventLoopFlags | 0x8000) == 0)
		return;
	do {
		if (cut_CurrentTick >= end + dur)
			g_774654 = 1;
		fcn_004cfca0();
		fcn_004e5140((*(int*)&cut_ActiveCutscene));
	} while (fcn_005373e0(fcn_004e4c90, cut_EventLoopFlags | 0x8000) != 0);
}
