#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* gm_MarketEntity;
extern unsigned char gm_ActiveTownIndex;
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/season_slots.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
void* __cdecl gm_AddObjekt(void);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_QueryEntities(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
/* ADDRESS: GOLDTL 0x00501d20 */
/* ADDRESS: GOLDDE 0x004ed360 */
void __cdecl gm_RefreshLocalMarketStock(int season)
{
	unsigned int ids[8];
	char* slots;
	void* entity;
	void* query;
	unsigned short* result;
	unsigned short* r2;
	char* def;
	int i;
	int j;
	int k;
	int count;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
	ids[0] = 0x92;
	ids[1] = 0x93;
	ids[2] = 0x94;
	ids[3] = 0x95;
	ids[4] = 0x96;
	ids[5] = 0x97;
	ids[6] = 0x2db;
	ids[7] = 0;

	(*(int*)&gm_MarketEntity) = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if ((*(int*)&gm_MarketEntity) == 0) {
		return;
	}

	slots = gm_MarketStockTable + season * 0x2a90;
	if (season != gm_ActiveTownIndex) {
		return;
	}
	for (i = 0; i < 0x55; i++) {
		((MARKET_STOCK_SLOT*)slots)[i].active = 0;
	}

	entity = gm_StartFilteredEntitySearch(1, 6);
	while (entity != 0) {
		if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) entity].category) != '\n') {
			query = gm_QueryEntities(*(int*) ((char*) entity + 0x5d), 1, 0, 0xff);
			for (i = 0; query != 0 && i < 0x55; i++) {
				if (((MARKET_STOCK_SLOT*)slots)[i].objekt_id != 0 &&
				    gm_QueryEntities(*(int*) ((char*) query + 0x14), 1, 0, ((MARKET_STOCK_SLOT*)slots)[i].objekt_id) != 0) {
					((MARKET_STOCK_SLOT*)slots)[i].active = 1;
					def = (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[((MARKET_STOCK_SLOT*)slots)[i].objekt_id];
					for (j = 0; j < 0x55; j++) {
						for (k = 0; k < 4; k++) {
							if (((MARKET_STOCK_SLOT*)slots)[j].objekt_id == ((OBJECT_PROTOTYPE *)def)->ingredient_ids[k]) {
								((MARKET_STOCK_SLOT*)slots)[j].active = 1;
							}
						}
					}
				}
			}
		}
		entity = gm_FindNextFilteredEntity();
	}

	for (i = 0; i < 0x55; i++) {
		result = gm_QueryEntities(*(int*) ((char*) (*(int*)&gm_MarketEntity) + 0x5d), 1, 0, ((MARKET_STOCK_SLOT*)slots)[i].target_id);
		if (result != 0) {
			result = gm_QueryEntities(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (((MARKET_STOCK_SLOT*)slots)[i].active != 0) {
				if (gm_QueryEntities(*(int*) ((char*) result + 0x14), 1, 0, ((MARKET_STOCK_SLOT*)slots)[i].objekt_id) == 0) {
					gm_AllocObjekt(*(int*) ((char*) result + 2), ((MARKET_STOCK_SLOT*)slots)[i].objekt_id, 1);
				}
			}
		}
	}

	for (i = 0; ids[i] != 0; i++) {
		count = 0;
		result = gm_QueryEntities(*(int*) ((char*) (*(int*)&gm_MarketEntity) + 0x5d), 1, 0, ids[i]);
		if (result != 0) {
			r2 = gm_QueryEntities(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (r2 != 0) {
				r2 = gm_QueryEntities(*(int*) ((char*) r2 + 0x14), 1, 5);
				while (r2 != 0) {
					count++;
					r2 = gm_NextEntityQueryMatch();
				}
				result = gm_QueryEntities(*(int*) ((char*) result + 0x14), 1, 4, 0x11);
				if (result != 0 && *(unsigned char*) ((char*) result + 0x1c) != count)
					*(unsigned char*) ((char*) result + 0x1c) = (unsigned char) count;
			}
		}
	}
}
