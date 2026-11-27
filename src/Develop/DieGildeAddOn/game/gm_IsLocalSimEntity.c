extern unsigned char g_6a375c;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned int g_14cbcb4;


/* ADDRESS: GOLDTL 0x0047dca0 */
int __cdecl gm_IsLocalSimEntity(char* entity)
{
	if ((g_14cbca0 == -1 || entity[2] == 6 || *(unsigned int*) (entity + 4) % g_6a375c == g_14cbcb4) &&
	    (*(int*) (entity + 0x1cc) & 0x3000) == 0)
		return 1;
	return 0;
}
