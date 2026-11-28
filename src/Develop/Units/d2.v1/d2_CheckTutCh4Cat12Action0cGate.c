#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"

/* ADDRESS: GOLDDE 0x00565300 */
int __cdecl d2_CheckTutCh4Cat12Action0cGate(int* m)
{
	if (m[0] == 0x2b && m[1] != 0 && ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) m[1]].category)) == 0x12 &&
	    *(short*) (m[1] + 0x27) == (*(short*)&gm_LocalPlayerSlot) && (m[3] == 0xc || m[3] == 0x1df)) {
		return 1;
	}
	if (m[0] == 0x1a || m[0] == 0x19 || m[0] == 0x1c) {
		return 1;
	}
	return 0;
}
