#include "client_types.h"
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1040494;
extern int d2_ScreenHeight;


void __cdecl d2_SetOverlayAnimation(int, int);

void __cdecl fcn_004116d0(void);
void __cdecl fcn_00533a40(char*);
void __cdecl fcn_00475220(char*);

void __cdecl fcn_00525ef0(void)
{
	d2_SetOverlayAnimation(0, 0);
	ResetDisplayCounters();
	fcn_004116d0();
	fcn_00533a40(g_6b5c60);
	fcn_00475220(g_6b5c60);
	g_6772c4 = 1;
	g_6b5c80 = 0;
	d2_MouseTopBoundary = 0;
	d2_MouseRightBoundary = g_1040494 - 8;
	d2_MouseBottomBoundary = d2_ScreenHeight;
}
