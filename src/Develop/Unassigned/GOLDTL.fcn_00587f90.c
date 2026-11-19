


extern int g_100f1dc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_14cf732;

int __cdecl fcn_00587f90(char* o)
{
	if (*(int*) (o + 0x7c) == 0 && !(*(float*) (o + 0x20) > 0.01f)) {
		if (g_100f1dc != -1 && d2_CurrentElementId == *(int*) (o + 0xb8)) {
			g_14cf732 = 0;
			*(int*) (o + 0x78) = *(int*) (o + 0x6c);
			*(int*) (o + 0x7c) = 1;
			return 1;
		}
		if (g_14cf732 != 0) {
			g_14cf732 = 0;
			*(int*) (o + 0x78) = *(int*) (o + 0x6c);
			*(int*) (o + 0x7c) = 1;
			return 1;
		}
	}
	return 0;
}
