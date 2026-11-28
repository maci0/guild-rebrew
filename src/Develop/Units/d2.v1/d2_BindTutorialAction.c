


extern int* d2_TutorialState;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl d2_BindTutorialAction(int action)
{
	int* p;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return -4;
	}
	p = d2_TutorialState;
	*(int*) ((char*) p + 0x1c) = action;
	*(int*) ((char*) d2_TutorialState + 0x20) = -1;
	return 0;
}
