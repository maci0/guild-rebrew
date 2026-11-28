

extern int* d2_TutorialState;
extern char g_6a8364[];
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"
extern s_1015f4c d2_WindowMetricsView[];

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);

void __cdecl d2_OpenTutorialProgress(void)
{
	d2_TutorialState[26] = d2_LoadForm(0, 0, g_6a8364);
	d2_CenterForm(d2_TutorialState[26], 3);
	d2_SetForm(d2_TutorialState[26], 0);
	d2_TutorialState[27] = d2_AddWindowValueGauge(((int*)d2_WindowMetricsView)[d2_CurrentWindowId * 243] / 2 - 200, 5, 0x190, 0, 0x190, 0x75,
	    0x42, d2_CurrentWindowId);
}
