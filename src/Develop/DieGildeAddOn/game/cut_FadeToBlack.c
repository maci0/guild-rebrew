

extern int cut_SkipMode;
extern unsigned char* g_772f50;
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(int, int);

void __cdecl cut_FadeToBlack(void)
{
	if (cut_SkipMode == 0) {
		g_772f50 = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x5a, 1);
		while ((*g_772f50 & 4) == 0) {
			main_RunFrameLoop(0, cut_EventLoopFlags | 0x80);
		}
	}
}
