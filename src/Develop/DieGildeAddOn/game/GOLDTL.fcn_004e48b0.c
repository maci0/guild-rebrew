

extern int g_772f3c;
extern unsigned char* g_772f50;
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl fcn_005373e0(int, int);

void __cdecl fcn_004e48b0(void)
{
	if (g_772f3c == 0) {
		g_772f50 = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x5a, 1);
		while ((*g_772f50 & 4) == 0) {
			fcn_005373e0(0, cut_EventLoopFlags | 0x80);
		}
	}
}
