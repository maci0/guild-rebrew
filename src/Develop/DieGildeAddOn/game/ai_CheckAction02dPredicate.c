#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

unsigned short __cdecl gm_RandomMod(int);


/* ADDRESS: GOLD 0x004a9150 */
/* ADDRESS: GOLDTL 0x004a9270 */
int __cdecl ai_CheckAction02dPredicate(int unused, char* actor)
{
	if (*(int*) (actor + 0x194) >= 8 && *(unsigned int*) (actor + 4) % 4 == (unsigned int)((*(int*)&gm_GameTime) % 4) && gm_RandomMod(4) == 0)
		return 1;
	return 0;
}
