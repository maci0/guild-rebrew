extern char g_7e5fc0[];
extern int main_LoopFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenSurface;
extern int g_6a251c;
extern volatile int gm_GameTicks;



void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);

void __cdecl d2_DrawStatusBannerText(void)
{
	int x;
	int y;

	if (g_7e5fc0[0] != 0) {
		d2_SelectFont(0x53);
		if (main_LoopFlags & 0x8000) {
			x = d2_CenterX - 0x12c;
			y = (int) (d2_UiScale * 505.0f);
		} else {
			x = d2_CenterX - 0x12c;
			y = (int) (d2_UiScale * 575.0f);
		}
		d2_DrawWordWrappedText(x, y, 0x258, 0x18, d2_ScreenSurface, g_7e5fc0, 0x28);
		if ((*(unsigned int*)&gm_GameTicks) >= (unsigned int)(g_6a251c + 0x15e)) {
			g_7e5fc0[0] = 0;
		}
	}
}
