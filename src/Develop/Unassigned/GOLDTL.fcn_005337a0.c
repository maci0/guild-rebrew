extern char g_100f8c0[];
extern char g_7766ba;
extern int g_77250c;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);

void __cdecl fcn_005337a0(void)
{
	if (g_100f8c0[0] != 0 && g_7766ba != 0) {
		d2_SelectFont(0x54);
		d2_DrawWordWrappedText(d2_MouseX - 0x36, d2_MouseY + 0x34, 0xa0, 0x60, g_77250c, g_100f8c0, 0xa8);
	}
}
