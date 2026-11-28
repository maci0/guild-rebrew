#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_EntitySlotTable[];


char* __cdecl gm_GetGuildHall(int k);
void* __cdecl gm_QueryEntities(int list, int a, int b, int c, int d);

void* __cdecl gm_FindBuildingTreasury(unsigned char* e)
{
	void* r;
	int t;
	unsigned char c;
	char* o;

	r = 0;
	t = gm_GetBuildingTypeCategory(e[0]);
	if (t == 5) {
		c = ((unsigned char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[gm_LocalPlayerSlot])[0x169];
		if (c == 0x1e) {
			o = gm_GetGuildHall(2);
		} else if (c == 0x1f) {
			o = gm_GetGuildHall(3);
		} else if (c == 0x20) {
			o = gm_GetGuildHall(4);
		} else if (c == 0x21) {
			o = gm_GetGuildHall(5);
		} else {
			o = 0;
		}
		if (o != 0) {
			r = gm_QueryEntities(*(int*) (o + 0x5d), 2, 6, 0, 0x142);
		}
	} else if (t == 3) {
		o = gm_GetGuildHall(1);
		r = gm_QueryEntities(*(int*) (o + 0x5d), 2, 6, 0, 0x115);
	}
	return r;
}
