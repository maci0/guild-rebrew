


extern int* d2_TutorialState;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_DialogButtonAction;

/* ADDRESS: GOLDDE 0x00566700 */
int __cdecl d2_CheckTutorialCueClicked(void)
{
	int r;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return -4;
	}
	if (*(int*) ((char*)&d2_DialogButtonAction) != -1 && d2_CurrentElementId == d2_TutorialState[19]) {
		r = 1;
	} else {
		r = 0;
	}
	return r;
}
