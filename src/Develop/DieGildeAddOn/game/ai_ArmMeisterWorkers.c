extern char ai_ResourceRequests[];
extern char g_100b100[];
extern char g_67e358[];
/* 0x21c-stride entity-table sweep from 0x7f4ca0 to 0x85a0a0: matches the
   record whose owner pointer equals the driver's, resolves its type row
   through 0x100e764/0x100e724 and reports the 0x39 event. */
#include "Develop/DieGildeAddOn/game/object_prototype.h"
int __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl gm_LookupWeaponSpec(int);
int __cdecl gm_CheckBuildingCategoryForItem(int, int);
void __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
int __cdecl sprintf(char*, char*, ...);

extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100e724;
extern int g_100e764;
extern char* lpObjektePROT;
extern char gm_EntitySlotTable[];
/* ADDRESS: GOLDTL 0x00489010 */
/* ADDRESS: GOLDDE 0x00477ee0 */
void __cdecl ai_ArmMeisterWorkers(char* meister, char* building)
{
	char buf[0x400];
	int m;
	char* p;
	char* n;
	char* a;
	char* b;
	char* found;
	int i;
	int k;
	int done;

	for (m = 0; m < 0x300; m++) {
		p = gm_EntitySlotTable + m * 0x21c;
		if (*(unsigned short*) p == 0xffff
		    || *(char**) (p + 0x16c) != *(char**) (meister + 0x16c)
		    || *(char*) (p + 0x165) == 0
		    || *(char**) (p + 0x184) == 0
		    || *(int*) (*(char**) (p + 0x184) + 0x2c) != *(int*) (*(char**) (p + 0x16c) + 1)) {
			continue;
		}
		found = 0;
		n = (char*) gm_QueryEntities(*(int*) (p + 0x178), 1, 4, 0xc);
		if (n == 0) {
			return;
		}
		done = 0;
		for (a = (char*) &g_100b100, b = (char*) &g_100e764; !done; b += 4, a += 0x40) {
			if (*(int*) (b - 4) == 0 || *(int*) b == 0) {
				break;
			}
			k = *(unsigned short*) n;
			*(int*) (b - 4) = k;
			if (k != 0) {
				for (i = 0; !done && i < ai_ResourceCount; i++) {
					if (*(int*) ((int) &ai_ResourceRequests + i * 0x40) == *(int*) b) {
						found = a;
						done = 1;
					}
				}
			}
		}
		if (!done) {
			for (a = (char*) &g_100b100, b = (char*) &g_100e724; !done; b += 4, a += 0x40) {
				if (*(int*) (b - 4) == 0 || *(int*) b == 0) {
					break;
				}
				k = *(unsigned short*) n;
				*(int*) (b - 4) = k;
				if (k != 0) {
					for (i = 0; !done && i < ai_ResourceCount; i++) {
						if (*(int*) ((int) &ai_ResourceRequests + i * 0x40) == *(int*) b) {
							found = a;
							done = 1;
						}
					}
				}
			}
		}
		if (found != 0 && *(int*) (found + 0x28) != 0
		    && gm_LookupWeaponSpec(*(int*) found) != 0
		    && gm_CheckBuildingCategoryForItem((int) meister, *(int*) found) != 0) {
			sprintf(buf, "Meister %s bewaffnet %s mit %s", meister + 0x30, p + 0x30,
			        (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(int*) found] + 1);
			sprintf(buf, (char*) &g_67e358, *(int*) (p + 4),
			        *(int*) (building + 2), *(int*) found, 1, gm_ActiveTownIndex, 0);
			cm_SendSellObjekt(*(int*) (p + 4), *(int*) (building + 2), *(int*) found, 1,
			             gm_ActiveTownIndex, 0);
			*(int*) (found + 0x28) = *(int*) (found + 0x28) - 1;
		}
	}
}
