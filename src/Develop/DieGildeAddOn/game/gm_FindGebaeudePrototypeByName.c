extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"


int __cdecl fcn_0065f220(const char*, const char*);

/* ADDRESS: GOLDDE 0x004f0230 */
int __cdecl gm_FindGebaeudePrototypeByName(const char* name)
{
	int i;

	for (i = 0; i < 0x58; i++) {
		if (fcn_0065f220(name, (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[i] + 1) == 0) {
			return i;
		}
	}
	return 0;
}
