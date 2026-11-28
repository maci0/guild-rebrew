extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"


#include <string.h>

/* ADDRESS: GOLDDE 0x004ff8f0 */
char __cdecl d3_ClassifyBuildingSceneObject(char* o)
{
	unsigned char* t;

	if (strncmp(o, "gb_", 3) == 0) {
		t = 0;
		if (o[0x4b] == 2) {
			t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(*(int*) (o + 0x48) & 0xffffff)];
		}
		if (t == 0) {
			if (strstr(o, "_TOR_") == 0) {
				o[0x216] = (o[0x216] & 0xfd) | 1;
				return 1;
			}
		} else if ((((BUILDING_PROTOTYPE*)t)->category) != 0x1f) {
			o[0x216] = (o[0x216] & 0xfd) | 1;
			return 1;
		} else {
			o[0x216] |= 3;
		}
	}
	return 1;
}
