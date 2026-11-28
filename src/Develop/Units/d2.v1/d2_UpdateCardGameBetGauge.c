

extern int g_6ad580;
extern int g_6ad568;
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"
extern s_1015f4c d2_WindowMetricsView[];
extern int g_776644;
extern int g_776648;
extern unsigned char gm_ActiveTownIndex;

void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddWindowValueGauge(int, int, int, int, int, int, int, int);
int __cdecl gm_AmountToUnits(int, char);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetSlotVisibility(int, int);

void __cdecl d2_UpdateCardGameBetGauge(int show)
{
	if (show != 0) {
		if (g_6ad580 == -1) {
			d2_SetForm(g_6ad568, 5);
			g_6ad580 = d2_AddWindowValueGauge(0, 0, ((int*)d2_WindowMetricsView)[d2_CurrentWindowId * 243] - 0xb4, 0, 100, 0x7b, 2,
			    d2_CurrentWindowId);
			d2_SetElementValue(g_6ad580, gm_AmountToUnits(g_776644, (*(char*)&gm_ActiveTownIndex)), gm_AmountToUnits(g_776648, (*(char*)&gm_ActiveTownIndex)),
			    gm_AmountToUnits(g_776644, (*(char*)&gm_ActiveTownIndex)), 1);
		}
		else {
			d2_SetSlotVisibility(g_6ad580, show);
		}
	}
}
