

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00538060(void);
#include "client_timer.h"
void __cdecl fcn_00405540(char*, int);

void __cdecl fcn_004e5980(void)
{
	char** p;

	fcn_0042df30(fcn_00538060, 1);
	for (p = ((char**)ch_CharacterSlots); (int) p < (int) (((char**)ch_CharacterSlots) + 0x300); p++) {
		if (*p != 0 && (*(unsigned char*) (*p + 0x8c) & 4) == 0) {
			fcn_00405540(*p, 1);
		}
	}
}
