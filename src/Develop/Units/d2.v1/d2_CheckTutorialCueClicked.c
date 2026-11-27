


extern int* g_665f08;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1dc;

int __cdecl d2_CheckTutorialCueClicked(void)
{
	int r;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return -4;
	}
	if (*(int*) ((char*)&g_100f1dc) != -1 && d2_CurrentElementId == g_665f08[19]) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
