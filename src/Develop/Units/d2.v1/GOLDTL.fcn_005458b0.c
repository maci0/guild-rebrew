#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
extern int d2_ScreenHeight;
extern int g_1040494;

// SIZE 0xc

#include "client_types.h"
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];

// SIZE 0x3cc

extern s_1015f4c g_1015f4c[];



int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_PositionControl(int, int, int);
void __cdecl d2_SetFormVisibility(int, int);

void __cdecl d2_CreateEventBar(void)
{
	int i;

	g_77e8a0 = d2_LoadForm(0, 0, "Panel\\Event_Leiste");
	d2_SetForm(g_77e8a0, 0);
	d2_PositionControl(g_1040494 - 0x7d, d2_ScreenHeight - 0x21, g_1015f4c[d2_CurrentWindowId].f270);
	for (i = 0; i < 16; i++) {
		g_77e8c0[i].h = -1;
	}
	d2_SetFormVisibility(g_77e8a0, 0);
}
