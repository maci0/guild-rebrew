#include "Develop/DieGildeAddOn/game/spiel.h"
unsigned short __cdecl gm_RandomMod(int);

// FUNCTION: GOLD 0x4a8ee0
// FUNCTION: GOLDTL 0x4a9000

int __cdecl fcn_004a9000(int a, char* e)
{
	if (gm_MapEntityStatRange(*(unsigned char*) (e + 0x164)) == 7 && gm_RandomMod(3) != 0)
		return 1;
	return gm_RandomMod(4) == 0;
}
