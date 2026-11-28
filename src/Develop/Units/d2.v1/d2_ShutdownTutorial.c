


extern int* d2_TutorialState;
extern int d2_TutorialSampleBanks[];
extern char* g_774a10;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_774a18;

void __cdecl sb_ReleaseSampleBank(int);
void __cdecl d2_FreeTutorialNodes(int);
void __cdecl d2_DestroyForm(int);

void __cdecl d2_ShutdownTutorial(void)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (d2_TutorialSampleBanks[i] != 0) {
			sb_ReleaseSampleBank(d2_TutorialSampleBanks[i]);
		}
	}
	d2_FreeTutorialNodes((*(int*)&g_774a10));
	(*(int*)&g_774a10) = 0;
	d2_TutorialState[0] = 0;
	d2_TutorialState[2] = 0;
	d2_TutorialState[3] = 0;
	d2_TutorialState[4] = 0;
	d2_TutorialState[5] = 0;
	d2_TutorialState[6] = 0;
	d2_TutorialState[7] = 0;
	d2_TutorialState[8] = -1;
	d2_DestroyForm(d2_TutorialState[9]);
	d2_TutorialState[9] = -1;
	d2_DestroyForm(d2_TutorialState[13]);
	d2_TutorialState[13] = -1;
	d2_TutorialState[5] = 0;
	d2_TutorialActive = 0;
	g_774a18 = 0;
}
