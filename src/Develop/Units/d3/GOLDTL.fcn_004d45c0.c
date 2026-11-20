

#include "Develop/DieGildeAddOn/game/cutscene_clock.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl fcn_005373e0(void*, int);
void __cdecl d3_UpdateCameraAtScreenEdges(void);
void __cdecl fcn_004d06d0(void);
void __cdecl fcn_004cf180(void);
void __cdecl fcn_004cf6b0(void);
void __cdecl fcn_004d0070(void);

void __cdecl fcn_004d45c0(int dur)
{
	int start;

	start = cut_CurrentTick;
	if (fcn_005373e0(fcn_004d45c0, 0x7d6c6) != 0) {
		do {
			d3_UpdateCameraAtScreenEdges();
			fcn_004d06d0();
			fcn_004cf180();
			fcn_004cf6b0();
			if (g_14ce8e0 != 0 || cut_CurrentTick >= start + dur)
				g_774654 = 1;
			fcn_004d0070();
		} while (fcn_005373e0(fcn_004d45c0, 0x7d6c6) != 0);
	}
}
