#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl d2_CheckTutMsg1aNotCat12Node74(int* m);

int __cdecl d2_CheckTutCh4Cat12Action78Gate(int* m)
{
	if (m[0] == 0x2b && m[1] != 0 && ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) m[1]].category)) == 0x12 &&
	    *(short*) (m[1] + 0x27) == (*(short*)&gm_LocalPlayerSlot) && (m[3] == 0x79 || m[3] == 0x7a || m[3] == 0x78)) {
		return 1;
	}
	return d2_CheckTutMsg1aNotCat12Node74(m);
}
