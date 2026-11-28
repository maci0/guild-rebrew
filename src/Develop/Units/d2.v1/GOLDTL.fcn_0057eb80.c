

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int* d2_TutorialState;

int __cdecl fcn_0057eb80(void)
{
	if (d2_TutorialActive == 0) {
		return 0;
	}
	return *(int*) (((char*)d2_TutorialState) + 0x3c) == 2;
}
