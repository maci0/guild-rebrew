extern char d2_HoverTextBuffer[];
extern char g_7766ba;
extern int d2_ScreenSurface;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDDE 0x0051c090 */
void __cdecl d2_DrawMouseTooltip(void)
{
	if (d2_HoverTextBuffer[0] != 0 && g_7766ba != 0) {
		d2_SelectFont(0x54);
		d2_DrawWordWrappedText(d2_MouseX - 0x36, d2_MouseY + 0x34, 0xa0, 0x60, d2_ScreenSurface, d2_HoverTextBuffer, 0xa8);
	}
}
