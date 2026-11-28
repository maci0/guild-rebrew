#include "game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern unsigned char g_slot_table[2];
extern unsigned char gm_ActiveTownIndex;
typedef struct { char x00[0x21]; unsigned char x21; char x22[0x22b]; } BUILDING_LIMIT_VIEW;
char* __cdecl gm_SearchTable67(int);
unsigned short* __cdecl gm_QueryEntities(int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetSeasonTreasury(char*, unsigned char);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
struct unit;
struct unit* __cdecl he_StartHandlungSearch(int, ...);
struct unit* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x004974e0 */
/* ADDRESS: GOLDDE 0x00485f60 */
int __cdecl ai_StartRaumKaufen(int unused, char* entity, int mode, char* itemReq, char* bldReq)
{
	char* building;
	int amount;
	unsigned short* ent;
	int i;
	int who;
	BUILDING_LIMIT_VIEW* limit;

	if (entity[2] == 3)
		return 0;
	if (mode != 1)
		return 0;
	if (itemReq[0] != 2)
		return 0;
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(int*) (itemReq + 4)].kind) != 2)
		return 0;
	if (bldReq[0] != 4)
		return 0;
	building = gm_SearchTable67(*(int*) (bldReq + 4));
	if (building == 0)
		return 0;
	if (*(unsigned short*) (building + 0x27) == 0xffff)
		return 0;
	amount = gm_GetSeasonTreasury(g_slot_table + *(unsigned short*) (building + 0x27) * 0x21c, gm_ActiveTownIndex);
	if (*(float*) (itemReq + 0x14) > 0.0f && *(float*) (itemReq + 0x14) < 1.0f)
		amount = (int) ((float) amount * *(float*) (itemReq + 0x14));
	who = gm_ActiveTownIndex;
	if (amount < (int) gm_GetSeasonPrice(*(int*) (itemReq + 4), who))
		return 0;
	i = 0;
	limit = &((BUILDING_LIMIT_VIEW*) lpGebaeudePROT)[*(unsigned char*) building];
	ent = gm_QueryEntities(*(int*) (building + 0x5d), 1, 4, 2);
	while (ent != 0) {
		if (*ent != 0xfd)
			i++;
		ent = (unsigned short*) gm_NextEntityQueryMatch();
	}
	if (i >= limit->x21)
		return 0;
	ent = (unsigned short*) he_StartHandlungSearch(2, 0, 0x1f, 3, *(int*) (building + 1));
	while (ent != 0) {
		i++;
		ent = (unsigned short*) he_fn_Handlung();
	}
	return i < limit->x21 ? 0xe : 0;
}
