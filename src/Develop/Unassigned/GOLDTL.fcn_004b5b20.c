#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl main_ExitToFrameHandler(void* fn);
int __cdecl main_RunGameLoop(void);

/* ADDRESS: GOLDTL 0x004b5b20 */
void __cdecl main_ExitToGameLoop(void* fn)
{
	g_774954 = 1;
	main_ExitToFrameHandler(main_RunGameLoop);
}
