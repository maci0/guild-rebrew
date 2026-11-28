

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl gm_AdvanceGameClock(void);
#include "Develop/DieGildeAddOn/game/client_timer.h"
void __cdecl ch_SetAnimationPaused(char*, int);

void __cdecl cut_PauseWorldAndCharacters(void)
{
	char** p;

	tb_SetCallbackPaused(gm_AdvanceGameClock, 1);
	for (p = ((char**)ch_CharacterSlots); (int) p < (int) (((char**)ch_CharacterSlots) + 0x300); p++) {
		if (*p != 0 && (*(unsigned char*) (*p + 0x8c) & 4) == 0) {
			ch_SetAnimationPaused(*p, 1);
		}
	}
}
