extern char g_100f8c0[];
extern int g_67d8dc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);


/* ADDRESS: GOLDTL 0x00475240 */
void __cdecl d2_DrawHoverText(int fontId)
{
	if (g_100f8c0[0] != 0 && g_67d8dc != 0) {
		d2_SelectFont(fontId);
		d2_DrawWordWrappedText(d2_MouseX - 0x36, d2_MouseY + 0x34, 0xa0, 0x60, g_77250c, g_100f8c0, 0xa8);
	}
}
