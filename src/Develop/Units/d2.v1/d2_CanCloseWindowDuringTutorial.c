


extern int* d2_TutorialState;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_CanCloseWindowDuringTutorial(void)
{
	int* p;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return 1;
	}
	p = d2_TutorialState;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	return 1;
}
