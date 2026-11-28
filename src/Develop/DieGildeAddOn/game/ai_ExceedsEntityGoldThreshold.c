extern unsigned char gm_ActiveTownIndex;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AmountToUnits(int, char);


/* ADDRESS: GOLDTL 0x004b46c0 */
/* ADDRESS: GOLDDE 0x004a29b0 */
int __cdecl ai_ExceedsEntityGoldThreshold(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return gm_AmountToUnits(*(int*) (p + 0x38), (*(char*)&gm_ActiveTownIndex)) > *(int*) (thr + 0x14);
}
