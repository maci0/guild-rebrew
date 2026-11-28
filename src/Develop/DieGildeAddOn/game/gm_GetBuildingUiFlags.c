#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
extern int gm_AllEntitiesControllable;

int __cdecl gm_MapBuildingCatToGuildSlot(int);
int __cdecl gm_CheckStatLevel(int, int);

int __cdecl gm_GetBuildingUiFlags(unsigned short* who, unsigned char* p, short* cmd)
{
	unsigned char* t;
	int lvl;
	int flags;
	int i;

	t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*p];
	lvl = gm_CheckStatLevel(*who, gm_MapBuildingCatToGuildSlot((((BUILDING_PROTOTYPE*)t)->category)));
	flags = 0x81;
	if (*(unsigned short*) (p + 0x25) == *who) {
		flags |= 0x103c;
	}
	if (cmd != 0 && (*cmd == 0x211 || *cmd == 0x205)) {
		flags &= ~1;
	}
	if (*(unsigned short*) (p + 0x27) == *who) {
		flags |= 0x4461;
		for (i = 0; i < 6; i++) {
			if (((BUILDING_PROTOTYPE*)t)->worker_kind[i] == 0) {
				break;
			}
			if (lvl == ((BUILDING_PROTOTYPE*)t)->worker_kind[i]) {
				flags |= 0x2200;
				break;
			}
		}
	}
	if (cmd != 0 && *cmd == 0x21b) {
		flags |= 0x5000;
	}
	if (gm_AllEntitiesControllable != 0) {
		flags = -1;
	}
	return flags;
}
