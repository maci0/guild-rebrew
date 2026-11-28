

#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d3_UpdateCameraAtScreenEdges(void);
void __cdecl cut_UpdateCombatHoverTarget(void);
void __cdecl cut_UpdateActiveBombs(void);
void __cdecl d3_UpdateMineExplosions(void);
void __cdecl cut_UpdateCombatEffects(void);

void __cdecl cut_RunCombatTickLoop(int dur)
{
	int start;

	start = cut_CurrentTick;
	if (main_RunFrameLoop(cut_RunCombatTickLoop, 0x7d6c6) != 0) {
		do {
			d3_UpdateCameraAtScreenEdges();
			cut_UpdateCombatHoverTarget();
			cut_UpdateActiveBombs();
			d3_UpdateMineExplosions();
			if (io_RightButtonReleased != 0 || cut_CurrentTick >= start + dur)
				d2_DialogCloseRequested = 1;
			cut_UpdateCombatEffects();
		} while (main_RunFrameLoop(cut_RunCombatTickLoop, 0x7d6c6) != 0);
	}
}
