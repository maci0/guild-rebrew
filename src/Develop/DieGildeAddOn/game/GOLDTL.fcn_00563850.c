

#include "client_types.h"

// SIZE 0xc4
struct unit {
	char pad0[8];
	unsigned short house;
	char pada[6];
	int target;
	char pad14[0x30];
	pos14_7f4c00 p44;
	pos14_7f4c00 p52;
	pos14_7f4c00 p60;
	char pad6e[0xac - 0x6e];
	int search;
	int dist;
	char padb4[4];
	pos14_7f4c00 pb8;
	char padc6[2];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl he_FreeAction(struct unit*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00563850(struct unit* u)
{
	char* e;
	ENTITY_RECORD* h;

	e = gm_StartFilteredEntitySearch(1, 1, u->search);
	if (e == 0) {
		he_FreeAction(u);
		return;
	}
	u->target = *(int*) (e + 1);
	cm_RequestChangeBits(*(int*) (e + 1), 0x5a, 2, 4, 0);
	u->p60 = gm_GameTime;
	u->p52 = gm_GameTime;
	u->p44 = gm_GameTime;
	gm_AddTime(&u->p52, 0, 10, 0);
	u->pb8 = u->p52;
	h = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[u->house]);
	gm_AddTime(&u->pb8, 0, (int) (10.0 * (h->unk_00d >= 9 ? 0.4f : h->unk_00d == 8 ? 0.6f : h->unk_00d == 7 ? 0.8f : 1.0f) * u->dist), 0);
}
