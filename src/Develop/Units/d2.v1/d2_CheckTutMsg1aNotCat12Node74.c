#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
extern char* sv_SelectedBuilding;

/* ADDRESS: GOLDDE 0x00564ae0 */
int __cdecl d2_CheckTutMsg1aNotCat12Node74(int* msg)
{
	unsigned char* e;

	if (*msg == 0x1a) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category) == 0x12 && *((short*)sv_SelectedBuilding) == 0x74) {
				return 0;
			}
		}
	}
	return 1;
}
