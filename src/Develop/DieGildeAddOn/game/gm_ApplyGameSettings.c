


extern unsigned char gm_ClientModeFlags;
extern int g_6b5c94;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7766a8;
extern float g_675308;
extern int g_7766b0;
extern int g_7766ac;

void __cdecl io_SetMouseSensitivity(int);

/* ADDRESS: GOLDDE 0x005c3a70 */
void __cdecl gm_ApplyGameSettings(void)
{
	g_6b5c94 = 0;
	if (gm_ClientModeFlags & 4) {
		g_675308 = (float) (((*(unsigned int*)g_68a9cc) * 0.25 + 0.5) * 0.8);
	}
	else {
		g_675308 = (float) (g_7766a8 * 0.00625f + 0.25);
	}
	io_SetMouseSensitivity(g_7766b0 - 0x40);
	g_6a256c = 100 - (g_7766ac & 0xff);
}
