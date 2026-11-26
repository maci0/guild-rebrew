


extern int* g_665f08;
extern int g_7749f8[];
extern char* g_774a10;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774a18;

void __cdecl fcn_004230e0(int);
void __cdecl d2_FreeTutorialNodes(int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShutdownTutorial(void)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (g_7749f8[i] != 0) {
			fcn_004230e0(g_7749f8[i]);
		}
	}
	d2_FreeTutorialNodes((*(int*)&g_774a10));
	(*(int*)&g_774a10) = 0;
	g_665f08[0] = 0;
	g_665f08[2] = 0;
	g_665f08[3] = 0;
	g_665f08[4] = 0;
	g_665f08[5] = 0;
	g_665f08[6] = 0;
	g_665f08[7] = 0;
	g_665f08[8] = -1;
	d2_DestroyForm(g_665f08[9]);
	g_665f08[9] = -1;
	d2_DestroyForm(g_665f08[13]);
	g_665f08[13] = -1;
	g_665f08[5] = 0;
	d2_TutorialActive = 0;
	g_774a18 = 0;
}
