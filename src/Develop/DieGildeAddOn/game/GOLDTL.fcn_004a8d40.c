#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;

unsigned short __cdecl gm_RandomMod(int);


/* ADDRESS: GOLDTL 0x004a8d40 */
int __cdecl ai_CheckUseTrankPredicate(int unused, char* entity)
{
	if (*(unsigned int*) (entity + 4) % 4 == (unsigned int)((*(int*)&gm_GameTime) % 4) && *(unsigned int*) (entity + 4) % 8 == (unsigned int)((unsigned short) (*(int*)&g_7f4c04) % 8))
		return gm_RandomMod(4) == 0;
	return 0;
}
