#include "game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

unsigned short* __cdecl gm_QueryEntities(int, int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDTL 0x004a4fb0 */
/* ADDRESS: GOLDDE 0x004939b0 */
unsigned int __cdecl ai_FindMissingBuildingUpgrade(unsigned int* outItem, unsigned int* outContainer, unsigned char* building)
{
	unsigned char* rec;
	unsigned char* bld;
	unsigned short* parentItem;
	unsigned short* compSlot;
	unsigned short* reqSlot;
	unsigned short* match;
	unsigned char objKind;
	int container;
	int usedCount;
	int hasParent;
	int idx;

	container = *(int*) (building + 0x5d);
	rec = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building];
	parentItem = 0;
	idx = 0;
	if ((unsigned char) ((BUILDING_PROTOTYPE*)rec)->component_count <= 0) {
		return 0;
	}
	reqSlot = (unsigned short*) (rec + 0xa5);
	compSlot = (unsigned short*) (rec + 0x23);
	bld = building;
	do {
		objKind = *(unsigned char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(*compSlot & 0x7fff)]));
		if (objKind != '!') {
			if (objKind != 2 && objKind != 6) {
label:
				if (!gm_QueryEntities(container, 1, 0, *compSlot & 0x7fff)) {
					if (!*(unsigned short*) ((char*) reqSlot - 2) ||
					    gm_QueryEntities(container, 1, 0, *(unsigned short*) ((char*) reqSlot - 2))) {
						if (!*reqSlot || gm_QueryEntities(container, 1, 0, *reqSlot)) {
							*outItem = *(unsigned short*) (rec + 0x23 + idx * 2) & 0x7fff;
							if (parentItem != 0) {
								*outContainer = *(unsigned int*) ((char*) parentItem + 2);
								return 1;
							}
							*outContainer = 0xffffffff;
							return 1;
						}
					}
				}
			} else {
				hasParent = 0;
				usedCount = 0;
				parentItem = 0;
				match = gm_QueryEntities(*(int*) (bld + 0x5d), 1, 4, 2);
				while (match != 0) {
					if (*match != 0xfd) {
						usedCount += 1;
					}
					if (*match == (*compSlot & 0x7fff)) {
						container = *(int*) ((char*) match + 0x14);
						hasParent = 1;
						parentItem = match;
						break;
					}
					match = gm_NextEntityQueryMatch();
				}
				if (usedCount < (int) (unsigned char) ((BUILDING_PROTOTYPE*)rec)->count_021 && !hasParent) {
					match = gm_QueryEntities(*(int*) (building + 0x5d), 1, 4, 6);
					do {
						if (!match) {
							break;
						}
						if (*match == (*compSlot & 0x7fff)) {
							container = *(int*) ((char*) match + 0x14);
							hasParent = 1;
							parentItem = match;
							break;
						}
						match = gm_NextEntityQueryMatch();
					} while (1);
					if (usedCount < (int) (unsigned char) ((BUILDING_PROTOTYPE*)rec)->count_021 && !hasParent) {
						goto label;
					}
				}
			}
			bld = building;
		}
		idx += 1;
		reqSlot += 2;
		compSlot += 1;
		if (idx >= (int) (unsigned char) ((BUILDING_PROTOTYPE*)rec)->component_count) {
			return 0;
		}
	} while (1);
}
