extern char d2_HoverTextBuffer[];
extern int g_67d8dc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);


/* ADDRESS: GOLDTL 0x00475240 */
void __cdecl d2_DrawHoverText(int fontId)
{
	if (d2_HoverTextBuffer[0] != 0 && g_67d8dc != 0) {
		d2_SelectFont(fontId);
		d2_DrawWordWrappedText(d2_MouseX - 0x36, d2_MouseY + 0x34, 0xa0, 0x60, d2_ScreenSurface, d2_HoverTextBuffer, 0xa8);
	}
}
