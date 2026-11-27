#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl d2_AddCouncilSeatMarker(int a1, void* ctx)
{
	d2_AddElementToWindow(0x8c, (short) (0x44 - *(short*) ((char*) ctx + 0x2c) * 10),
	    0x4df, d2_CurrentWindowId);
	(*(int*) ((char*) ctx + 0x2c))++;
}
