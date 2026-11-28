#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern int* d2_TutorialState;
extern volatile int gm_GameTicks;
extern unsigned char* lpGebaeudePROT;

int __cdecl d2_UpdateTutCh2Cat0dStep(int* m)
{
	if (m[0] == 0x1b && m[1] != 0 && d2_TutorialState[1] == 4) {
		if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) m[1]].category)) == 0xd) {
			d2_TutorialState[0] = 0xa;
			d2_TutorialState[1] = 0xa;
			d2_TutorialState[3] = gm_GameTicks;
			return 1;
		}
	}
	else if (m[0] == 0x1c && m[1] != 0 && ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) m[1]].category)) == 0xd) {
		d2_TutorialState[0] = 0xb;
		d2_TutorialState[1] = 0xb;
		d2_TutorialState[3] = gm_GameTicks;
		return 1;
	}
	return 3;
}
