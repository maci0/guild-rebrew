#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


#pragma pack(push, 2)
// SIZE 0xe






#pragma pack(pop)

#pragma pack(push, 1)
// SIZE 0x27
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x20];
	unsigned short slot;
} Estate;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office;
#pragma pack(pop)

// SIZE 0x8
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
} Unit;

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





// SIZE 0x88
typedef struct {
	char pad0[0x52];
	pos14_7f4c00 stamp;
	char pad60[0x24];
	int event;
} Order;

extern unsigned char* lpGebaeudePROT;

extern unsigned char g_773d75;

extern pos14_7f4c00 gm_GameTime;

Estate* __cdecl gm_StartFilteredEntitySearch(int, int, int);
Unit* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_SendLogAction(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
void __cdecl cm_RequestSetWohnsitz(int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, Order*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_SendTraceEnd(char*);

void __cdecl gm_BuyBuilding(int search, int buyer, int price, Order* o, int notify)
{
	BUILDING_PROTOTYPE* office;
	char msg[0x100];
	Estate* s;
	Unit* u;

	s = gm_StartFilteredEntitySearch(1, 1, search);
	u = gm_LookupEntityRecordById(buyer);
	office = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[s->office];
	cm_SendLogAction("buy_building");
	if (s->slot != 0xffff) {
		io_FormatTextBuffer(msg, 0x17e6, s, u->slot, price);
		he_MessageBoxQuickjump(((ENTITY_RECORD*)g_7f4ca0)[s->slot].entity_id, -1, msg, 0, 0x5ff, s->id, -1, 0, "_NACHRICHTEN_HS_30");
		cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD*)g_7f4ca0)[s->slot].entity_id, buyer, (*(char*)&g_773d75), price);
		cm_SendSetGebBesitzer(s->id, u->id, u->id);
		if (notify != 0 && office->category == 2) {
			cm_RequestSetWohnsitz(u->id, s->id);
		}
	} else {
		cm_RequestMoveCredits(-1, buyer, (*(char*)&g_773d75), price);
		cm_SendSetGebBesitzer(s->id, u->id, u->id);
		if (notify != 0 && office->category == 2) {
			cm_RequestSetWohnsitz(u->id, s->id);
		}
	}
	if (o != 0) {
		o->stamp = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime(&o->stamp, 0, 0, 1);
		o->event = cm_SendSetHE(-1, o);
	}
	cm_RequestChangeBits(s->id, 0x5a, 2, 0, 2);
	cm_SendTraceEnd("buy_building");
}
