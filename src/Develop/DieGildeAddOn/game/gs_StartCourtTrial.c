#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct Msg {
	int pad0;
	unsigned char type;
	char pad5[3];
	int src;
	int dst;
	char pad10[0x36 - 0x10];
	unsigned char b36;
	char pad37[0x58 - 0x37];
	int owner;
	int target;
	int who[4];
	char pad70[0xf8 - 0x70];
} Msg;
// SIZE 0xf8

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int handle;
	char pad8[4];
	char female;
	char padd[0x166 - 0xd];
	unsigned char rank;
	char pad167[0x21c - 0x167];
} Ent;
// SIZE 0x21c

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char* lpGebaeudePROT;
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl gm_RandomMod(int);
int __cdecl gm_FindFilteredEntity(Ent*, int, int, unsigned short*, int, float, int*);
void __cdecl cm_SendCopyEntityData(Msg*);

/* ADDRESS: GOLDDE 0x005bb500 */
int __cdecl gs_StartCourtTrial(Ent* ent, Ent* other, int count, int flag)
{
	unsigned short ids[4];
	int out;
	Msg msg;
	unsigned char* q;
	unsigned int i;

	ids[0] = 0xffff;
	ids[1] = 0xffff;
	ids[2] = 0xffff;
	ids[3] = 0xffff;
	q = gm_StartFilteredEntitySearch(1, 6);
	while (q != 0) {
		if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*q].category)) == 15) {
			break;
		}
		q = gm_FindNextFilteredEntity();
	}
	if (q == 0) {
		return 0x10;
	}

	msg.src = ent->handle;
	msg.dst = ((Ent*)gm_EntitySlotTable)[gm_LocalPlayerSlot].handle;
	msg.owner = ent->handle;
	msg.type = 0x2c;
	msg.b36 = 2;
	msg.target = other->handle;
	ids[0] = other->id;
	msg.who[0] = -1;
	msg.who[1] = -1;
	msg.who[2] = -1;
	msg.who[3] = -1;
	if (flag == 0) {
		for (i = 0; i < 768; i++) {
			if (((Ent*)gm_EntitySlotTable)[i].rank == 13) {
				msg.who[0] = ((Ent*)gm_EntitySlotTable)[i].handle;
				ids[1] = ((Ent*)gm_EntitySlotTable)[i].id;
				break;
			}
		}
		if (msg.who[0] == -1) {
			if ((short) gm_RandomMod(2)) {
				msg.who[0] = ((Ent*)gm_RichterKatholisch)->handle;
				ids[1] = ((Ent*)gm_RichterKatholisch)->id;
			} else {
				msg.who[0] = ((Ent*)gm_RichterEvangelisch)->handle;
				ids[1] = ((Ent*)gm_RichterEvangelisch)->id;
			}
		}
	} else {
		msg.who[0] = !ent->female ? ((Ent*)gm_RichterKatholisch)->handle : ((Ent*)gm_RichterEvangelisch)->handle;
		ids[1] = !ent->female ? ((Ent*)gm_RichterKatholisch)->id : ((Ent*)gm_RichterEvangelisch)->id;
	}
	if (other->rank != 0x11 && ent->rank != 0x11) {
		for (i = 0; i < 768; i++) {
			if (((Ent*)gm_EntitySlotTable)[i].rank == 0x11) {
				if (count > 2) {
					msg.who[3] = ((Ent*)gm_EntitySlotTable)[i].handle;
				}
				ids[2] = ((Ent*)gm_EntitySlotTable)[i].id;
				break;
			}
		}
	}
	if (!gm_FindFilteredEntity(ent, 0xc00, 4, ids, 0, 100.0f, &out)) {
		return 0x40;
	}
	if (ids[2] == 0xffff) {
		ids[2] = (unsigned short) out;
	} else {
		ids[3] = (unsigned short) out;
	}
	msg.who[1] = ((Ent*)gm_EntitySlotTable)[out & 0xffff].handle;
	if (!gm_FindFilteredEntity(ent, 0xc00, 4, ids, 0, 100.0f, &out)) {
		return 0x40;
	}
	msg.who[2] = ((Ent*)gm_EntitySlotTable)[out & 0xffff].handle;
	cm_SendCopyEntityData(&msg);
	return 0x10;
}
