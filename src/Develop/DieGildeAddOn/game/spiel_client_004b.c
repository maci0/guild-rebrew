extern unsigned char gm_ActiveTownIndex;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AmountToUnits(int, char);

int __cdecl gm_AmountToUnits(int, char);

int __cdecl gm_AmountToUnits(int, char);

/* ADDRESS: GOLD 0x004b4830 */
/* ADDRESS: GOLDTL 0x004b49a0 */
int __cdecl fcn_004b49a0(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return gm_AmountToUnits(*(int*) (p + 0x34) + *(int*) (p + 0x2c), (*(char*)&gm_ActiveTownIndex)) > *(int*) (thr + 0x14);
}

/* ADDRESS: GOLDTL 0x004b49e0 */
int __cdecl fcn_004b49e0(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return gm_AmountToUnits(*(int*) (p + 0x30), (*(char*)&gm_ActiveTownIndex)) > *(int*) (thr + 0x14);
}

/* ADDRESS: GOLDTL 0x004b4a20 */
int __cdecl fcn_004b4a20(int id, char* thr)
{
	char* p;

	p = (char*) gm_GetEntityTableEntry((char*) (id));
	if (p == 0)
		return 0;
	return gm_AmountToUnits(*(int*) (p + 0x3c), (*(char*)&gm_ActiveTownIndex)) > *(int*) (thr + 0x14);
}
