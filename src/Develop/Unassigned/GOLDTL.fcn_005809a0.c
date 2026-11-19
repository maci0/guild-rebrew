


extern int* g_665f08;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_005809a0(int a1)
{
	int* p;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return -4;
	}
	p = g_665f08;
	*(int*) ((char*) p + 0x1c) = a1;
	*(int*) ((char*) g_665f08 + 0x20) = -1;
	return 0;
}
