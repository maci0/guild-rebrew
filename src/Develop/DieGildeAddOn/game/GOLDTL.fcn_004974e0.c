#include "game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "GOLDTL.fcn_004974e0_gconf.h"
extern unsigned char g_773d75;
typedef struct { char x00[0x21]; unsigned char x21; char x22[0x22b]; } BUILDING_LIMIT_VIEW;
char* __cdecl gm_SearchTable67(int);
unsigned short* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetSeasonTreasury(char*, unsigned char);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
struct unit;
struct unit* __cdecl he_StartHandlungSearch(int, ...);
struct unit* __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x004974e0 */
int __cdecl fcn_004974e0(int unused, char* e, int unused2, char* out, char* out2)
{
	char* r;
	int amount;
	unsigned short* ent;
	int i;
	int who;
	BUILDING_LIMIT_VIEW* limit;

	if (e[2] == 3)
		return 0;
	if (unused2 != 1)
		return 0;
	if (out[0] != 2)
		return 0;
	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(int*) (out + 4)].kind) != 2)
		return 0;
	if (out2[0] != 4)
		return 0;
	r = gm_SearchTable67(*(int*) (out2 + 4));
	if (r == 0)
		return 0;
	if (*(unsigned short*) (r + 0x27) == 0xffff)
		return 0;
	amount = gm_GetSeasonTreasury(g_slot_table + *(unsigned short*) (r + 0x27) * 0x21c, g_773d75);
	if (*(float*) (out + 0x14) > 0.0f && *(float*) (out + 0x14) < 1.0f)
		amount = (int) ((float) amount * *(float*) (out + 0x14));
	who = g_773d75;
	if (amount < (int) gm_GetSeasonPrice(*(int*) (out + 4), who))
		return 0;
	i = 0;
	limit = &((BUILDING_LIMIT_VIEW*) lpGebaeudePROT)[*(unsigned char*) r];
	ent = fcn_00502cd0(*(int*) (r + 0x5d), 1, 4, 2);
	while (ent != 0) {
		if (*ent != 0xfd)
			i++;
		ent = (unsigned short*) gm_NextEntityQueryMatch();
	}
	if (i >= limit->x21)
		return 0;
	ent = (unsigned short*) he_StartHandlungSearch(2, 0, 0x1f, 3, *(int*) (r + 1));
	while (ent != 0) {
		i++;
		ent = (unsigned short*) he_fn_Handlung();
	}
	return i < limit->x21 ? 0xe : 0;
}
