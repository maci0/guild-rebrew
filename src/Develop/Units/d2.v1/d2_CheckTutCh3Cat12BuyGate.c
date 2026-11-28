#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern int* d2_TutorialState;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl d2_CheckTutCh3Cat12BuyGate(int* m)
{
	if (d2_TutorialState[14] >= 0 && m[0] == 0x28 && m[3] == 0x155) {
		d2_TutorialState[14] = 1;
		return 1;
	}
	if (d2_TutorialState[14] >= 1 && m[0] == 0x27 && m[3] == 0x1d0) {
		d2_TutorialState[14] = 2;
		return 1;
	}
	if (d2_TutorialState[14] >= 2 && m[1] != 0 && m[0] == 0x24 &&
	    ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) m[1]].category)) == 0x12 && *(short*) (m[1] + 0x27) == (*(short*)&gm_LocalPlayerSlot)) {
		d2_TutorialState[14] = 3;
		return 1;
	}
	if (m[0] == 0x1a || m[0] == 0x1c) {
		return 1;
	}
	return 0;
}
