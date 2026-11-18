#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl fcn_0046f740(int, int, int, int);

void __cdecl fcn_004da4d0(int a1, void* a2)
{
	fcn_0046f740(0x8c, (short) (0x44 - *(short*) ((char*) a2 + 0x2c) * 10),
	    0x4df, d2_CurrentWindowId);
	(*(int*) ((char*) a2 + 0x2c))++;
}
