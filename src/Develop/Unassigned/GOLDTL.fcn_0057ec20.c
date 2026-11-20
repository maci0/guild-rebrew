extern int* g_665f08;
extern int* g_665f08;
extern volatile int g_6b7fc0;
extern volatile int g_6b7fc0;
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLD 0x00576680 */
/* ADDRESS: GOLDTL 0x0057ec20 */
int __cdecl d2_TutorialAllowsFlag(int a1)
{
	int* p;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return 1;
	}
	p = g_665f08;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	p = (int*) p[6];
	if (p == 0) {
		return 1;
	}
	if (*(int*) ((char*)&g_6b7fc0) != 0) {
		return 0;
	}
	return (*(int*) ((char*) p + 0x68) & a1) != 0;
}
