


extern int* d2_TutorialState;
extern volatile int gm_GameTicks;
extern float g_665f10;

void __cdecl d2_OpenTutorialProgress(void);
void __cdecl d2_CloseTutorialProgress(void);
#include "Develop/Units/d2.v1/d2_gui.h"

#define ELAPSED(t) (((unsigned int)gm_GameTicks) - (t) ? ((unsigned int)gm_GameTicks) - (t) : 0)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDDE 0x005663b0 */
void __cdecl d2_UpdateTutorialProgress(void)
{
	unsigned int dur;
	unsigned int el;

	if (d2_TutorialState[6] != 0 && d2_TutorialState[0] == 0xa) {
		if (d2_TutorialState[26] == -1) {
			d2_OpenTutorialProgress();
		}
		el = MIN(ELAPSED(d2_TutorialState[3]), *(unsigned int*) (d2_TutorialState[6] + 0x44));
		dur = *(unsigned int*) (d2_TutorialState[6] + 0x44);
		d2_SetElementValue(d2_TutorialState[27], 0, 0x190, (int) ((float) (int) (dur - el) / dur * g_665f10), 1);
	}
	else {
		d2_CloseTutorialProgress();
	}
}
