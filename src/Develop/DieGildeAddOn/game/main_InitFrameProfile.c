void __cdecl main_SampleFrameCounter(void);
extern char sv_EntityGreyTintFlags[];
extern char d3_ActiveBombs[];


#include <string.h>

#include "Develop/DieGildeAddOn/game/client_timer.h"

void __cdecl main_InitFrameProfile(void)
{
	tb_OpenFunction(main_SampleFrameCounter, 0x47);
	memset(sv_EntityGreyTintFlags, 0, 0x300);
	memset(d3_ActiveBombs, 0, 0x100);
}
