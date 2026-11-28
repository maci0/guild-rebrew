extern int* d2_TutorialState;
extern int* d2_TutorialState;
extern volatile int tb_TimerPaused;
extern volatile int tb_TimerPaused;
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLD 0x00576680 */
/* ADDRESS: GOLDTL 0x0057ec20 */
/* ADDRESS: GOLDDE 0x005649f0 */
int __cdecl d2_TutorialAllowsFlag(int a1)
{
	int* p;

	if (*(int*) ((char*)&d2_TutorialActive) == 0) {
		return 1;
	}
	p = d2_TutorialState;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	p = (int*) p[6];
	if (p == 0) {
		return 1;
	}
	if (*(int*) ((char*)&tb_TimerPaused) != 0) {
		return 0;
	}
	return (*(int*) ((char*) p + 0x68) & a1) != 0;
}
