extern unsigned char gm_PlayerCount;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned int nt_LocalShardIndex;


/* ADDRESS: GOLDTL 0x0047dca0 */
/* ADDRESS: GOLDDE 0x0046cc60 */
int __cdecl gm_IsLocalSimEntity(char* entity)
{
	if ((nt_ClientSocket == -1 || entity[2] == 6 || *(unsigned int*) (entity + 4) % gm_PlayerCount == nt_LocalShardIndex) &&
	    (*(int*) (entity + 0x1cc) & 0x3000) == 0)
		return 1;
	return 0;
}
