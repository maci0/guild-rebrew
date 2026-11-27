

#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_UpdateCameraAtScreenEdges(void);
void __cdecl cut_UpdateCombatHoverTarget(void);
void __cdecl fcn_004cf180(void);
void __cdecl fcn_004cf6b0(void);
void __cdecl cut_UpdateCombatEffects(void);

void __cdecl fcn_004d45c0(int dur)
{
	int start;

	start = cut_CurrentTick;
	if (main_RunFrameLoop(fcn_004d45c0, 0x7d6c6) != 0) {
		do {
			d3_UpdateCameraAtScreenEdges();
			cut_UpdateCombatHoverTarget();
			fcn_004cf180();
			fcn_004cf6b0();
			if (g_14ce8e0 != 0 || cut_CurrentTick >= start + dur)
				g_774654 = 1;
			cut_UpdateCombatEffects();
		} while (main_RunFrameLoop(fcn_004d45c0, 0x7d6c6) != 0);
	}
}
