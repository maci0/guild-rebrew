#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


#pragma pack(push, 1)
// SIZE 0x29
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x22];
	unsigned short slot;
} Player;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x22f];
	unsigned char level;
	char pad231[0x1c];
} Office;

// SIZE 0x6
typedef struct {
	char pad0[2];
	int id;
} Site;
#pragma pack(pop)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x8
typedef struct {
	char pad0[4];
	int id;
} Handle;

extern unsigned char* lpGebaeudePROT;

extern unsigned char g_773d75;


int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
int __cdecl fcn_0050b750(int, char);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl gv_AssignGraveyardField(Player*);
int __cdecl fcn_004c6090(Player*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);
Handle* __cdecl cm_GetCommandResult(int);
int __cdecl gm_CheckEntityType(Player*);
Site* __cdecl fcn_005049a0(Player*);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
void __cdecl init_Betrieb(Player*);

void __cdecl init_SetupBetriebWorkers(Player* p)
{
	BUILDING_PROTOTYPE * o;
	int h;
	Handle* q;
	Site* s;

	gm_GetBuildingTypeCategory(p->office);
	o = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[p->office];
	if (o->category == 9) {
		cm_SendSellObjekt(p->id, -1, 0x136, 1, (*(char*)&g_773d75), 0);
		cm_RequestMoveCredits(((ENTITY_RECORD*)g_7f4ca0)[p->slot].entity_id, -1, (*(char*)&g_773d75), fcn_0050b750(0x1f4, (*(char*)&g_773d75)));
	} else if (o->category != 4 && o->category != 0x10 && o->category != 0x13) {
		cm_SendSellObjekt(p->id, -1, 0x134, 1, (*(char*)&g_773d75), 0);
	}
	if (o->category != 9) {
		if (o->category == 4 || o->category == 0x10 || o->category == 0x13 || o->category == 0x1d) {
			if (o->category == 0x1d) {
				h = gv_AssignGraveyardField(p);
			} else {
				if (((ENTITY_RECORD*)g_7f4ca0)[p->slot].entity_state != 6 && ((ENTITY_RECORD*)g_7f4ca0)[p->slot].entity_state != 7) {
					fcn_004c6090(p, 0, o->role_230, 0);
				}
				h = fcn_004c6090(p, 0, o->role_230, 0);
			}
		} else {
			h = fcn_004c6090(p, 0, o->role_230, 0);
		}
		while (cm_GetCommandStatus(h) == 0) {
			fcn_00535960();
		}
		q = cm_GetCommandResult(h);
		if (gm_CheckEntityType(p) == 0) {
			s = fcn_005049a0(p);
			if (s != 0) {
				cm_RequestChrMoveToUniverse(q->id, p->id, s->id, "dummy_EINGANG");
			}
		} else {
			cm_RequestChrMoveToUniverse(q->id, p->id, -1, "dummy_EINGANG");
		}
	}
	init_Betrieb(p);
}
