extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl gm_QueryEntities(int, int, int, int);
#include "Develop/DieGildeAddOn/game/building_prototype.h"

/* ADDRESS: GOLDTL 0x005049a0 */
int __cdecl gm_FindBuildingPrimarySlot(unsigned char* building)
{
	BUILDING_PROTOTYPE* type;
	unsigned short* slot;
	int found;
	int category;
	int item;
	int i;

	found = 0;
	category = gm_GetBuildingTypeCategory(building[0]);
	type = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[building[0]];
	if (category != 1 && category != 7 && category != 8) {
		if (category == 4) {
			return gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0xf7);
		}
		if (gm_CheckEntityType(building) != 0) {
			return gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0xfd);
		}
		slot = type->components;
		for (i = 0; i < 0x40; i++, slot++) {
			if (*slot != 0xffff) {
				item = *slot & 0x7fff;
				if (((OBJECT_PROTOTYPE*)lpObjektePROT)[item].kind == 2 && item != 0xfd) {
					return gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, item);
				}
			}
		}
		return found;
	}

		if (type->category == 0x1d) {
			found = gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0x205);
		} else if (type->category == 0x16) {
			found = gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0x12e);
		} else if (type->category == 4) {
			found = gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0x54);
		} else if (type->category == 0x1f) {
			found = gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, 0xfd);
		}
		if (found == 0) {
			slot = type->components;
			for (i = 0; i < 0x40; i++, slot++) {
				if (*slot != 0xffff) {
					item = *slot & 0x7fff;
					if (((OBJECT_PROTOTYPE*)lpObjektePROT)[item].kind == 2 && item != 0xfd) {
						return gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, item);
					}
				}
			}
		}
		return found;
}
