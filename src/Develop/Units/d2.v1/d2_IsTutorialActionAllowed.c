


#include "Develop/DieGildeAddOn/game/game_data.h"
extern int* d2_TutorialState;
extern volatile int tb_TimerPaused;

int __cdecl d2_IsTutorialActionAllowed(int mask)
{
	char* p;

	if (d2_TutorialActive == 0) {
		return 1;
	}
	p = ((char*)d2_TutorialState);
	if (*(int*) (p + 0x3c) == 2 || *(int*) p == 5) {
		return 0;
	}
	p = *(char**) (p + 0x18);
	if (p == 0) {
		return 1;
	}
	if (tb_TimerPaused != 0) {
		return 0;
	}
	return (*(int*) (p + 0x6c) & mask) != 0;
}
