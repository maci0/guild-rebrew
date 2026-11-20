#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_CurrentWindowId;
extern int d2_ScreenHeight;
extern int g_1040494;

// SIZE 0xc

#include "client_types.h"
extern D2_ACTION_POPUP_SLOT g_77e8c0[16];

// SIZE 0x3cc

extern s_1015f4c g_1015f4c[];



int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00471af0(int, int);

void __cdecl d2_CreateEventBar(void)
{
	int i;

	g_77e8a0 = fcn_00470820(0, 0, "Panel\\Event_Leiste");
	d2_SetForm(g_77e8a0, 0);
	fcn_00469c40(g_1040494 - 0x7d, d2_ScreenHeight - 0x21, g_1015f4c[d2_CurrentWindowId].f270);
	for (i = 0; i < 16; i++) {
		g_77e8c0[i].h = -1;
	}
	fcn_00471af0(g_77e8a0, 0);
}
