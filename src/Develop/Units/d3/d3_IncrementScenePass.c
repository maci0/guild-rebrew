#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x0043ad10 */
/* ADDRESS: GOLDDE 0x00433ad0 */
void __cdecl d3_IncrementScenePass(char a)
{
	if (a) {
		++g_6b8008;
	}
}
