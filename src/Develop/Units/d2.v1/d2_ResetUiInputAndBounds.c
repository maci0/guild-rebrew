#include "client_types.h"
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1040494;
extern int d2_ScreenHeight;


void __cdecl d2_SetOverlayAnimation(int, int);

void __cdecl io_ClearInputState(void);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl d2_SetMouseTooltip(char*);

void __cdecl d2_ResetUiInputAndBounds(void)
{
	d2_SetOverlayAnimation(0, 0);
	ResetDisplayCounters();
	io_ClearInputState();
	d2_ShowStatusBanner(g_6b5c60);
	d2_SetMouseTooltip(g_6b5c60);
	g_6772c4 = 1;
	g_6b5c80 = 0;
	d2_MouseTopBoundary = 0;
	d2_MouseRightBoundary = g_1040494 - 8;
	d2_MouseBottomBoundary = d2_ScreenHeight;
}
