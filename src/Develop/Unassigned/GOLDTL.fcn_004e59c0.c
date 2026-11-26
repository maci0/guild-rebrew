

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00538060(void);
#include "client_timer.h"
void __cdecl ch_SetAnimationPaused(char*, int);

void __cdecl fcn_004e59c0(void)
{
	char** p;

	tb_SetCallbackPaused(fcn_00538060, 0);
	for (p = ((char**)ch_CharacterSlots); (int) p < (int) (((char**)ch_CharacterSlots) + 0x300); p++) {
		if (*p != 0 && (*(unsigned char*) (*p + 0x8c) & 4) != 0) {
			ch_SetAnimationPaused(*p, 0);
		}
	}
}
