


extern int* g_665f08;
extern volatile int g_6b7fac;
extern float g_665f10;

void __cdecl d2_OpenTutorialProgress(void);
void __cdecl d2_CloseTutorialProgress(void);
#include "Develop/Units/d2.v1/d2_gui.h"

#define ELAPSED(t) (((unsigned int)g_6b7fac) - (t) ? ((unsigned int)g_6b7fac) - (t) : 0)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void __cdecl fcn_00580610(void)
{
	unsigned int dur;
	unsigned int el;

	if (g_665f08[6] != 0 && g_665f08[0] == 0xa) {
		if (g_665f08[26] == -1) {
			d2_OpenTutorialProgress();
		}
		el = MIN(ELAPSED(g_665f08[3]), *(unsigned int*) (g_665f08[6] + 0x44));
		dur = *(unsigned int*) (g_665f08[6] + 0x44);
		d2_SetElementValue(g_665f08[27], 0, 0x190, (int) ((float) (int) (dur - el) / dur * g_665f10), 1);
	}
	else {
		d2_CloseTutorialProgress();
	}
}
