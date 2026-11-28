#include "Develop/client_types.h"

int __cdecl gm_RandomMod(unsigned short);
struct unit;
void __cdecl he_FreeAction(struct unit*);

/* ADDRESS: GOLDTL 0x00551010 */
/* ADDRESS: GOLDDE 0x00537400 */
void __cdecl he_AllocBuildingDamageEvent(char* u)
{
	*(pos14_7f4c00*) (u + 0x52) = *(pos14_7f4c00*) (u + 0x44);
	if ((unsigned short) gm_RandomMod(2) != 0) {
		he_FreeAction((struct unit*) u);
	}
}
