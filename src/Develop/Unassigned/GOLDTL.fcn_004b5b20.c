#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl main_ExitToFrameHandler(void* fn);
int __cdecl fcn_005438c0(void);

/* ADDRESS: GOLDTL 0x004b5b20 */
void __cdecl fcn_004b5b20(void* fn)
{
	g_774954 = 1;
	main_ExitToFrameHandler(fcn_005438c0);
}
