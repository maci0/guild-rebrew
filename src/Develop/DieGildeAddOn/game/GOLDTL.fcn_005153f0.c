#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#pragma pack(push, 1)
// SIZE 0xa9
typedef struct {
	unsigned char office;
	int id;
	char pad5[0xa4];
} Player;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x222];
	unsigned char level;
	char pad224[0x29];
} Office;
#pragma pack(pop)


extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
#include "client_packet_builder.h"
extern unsigned char g_773d75;



void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
int __cdecl fcn_004c6090(Player*, int, int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

void __cdecl gm_InitStartingBuildingsAndWorkers(void)
{
	int i;
	ENTITY_RECORD* ent;
	Player* inst;

	ent = ((ENTITY_RECORD*)g_7f4ca0);
	for (i = 0; i < 0x300; i++) {
		if (ent->entity_state == 6) {
			break;
		}
		ent++;
	}
	for (inst = ((Player*)lpGebaeudeINST);; inst++) {
		if (inst->office == 0) {
			continue;
		}
		if (gm_GetBuildingTypeCategory(inst->office) == 1 || gm_GetBuildingTypeCategory(inst->office) == 4 || gm_GetBuildingTypeCategory(inst->office) == 2
			|| ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category == 0x13 || ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category == 4
			|| ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category == 0x10 || ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category == 5
			|| ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category == 9) {
			if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].category != 0xb) {
				int value = 0xfa00;

				cm_BeginPacketFieldDelta((char*) inst, inst->id);
				cm_AppendPacketFieldDelta(4, 1, (char*) inst - g_aed32c + 0x39, &value);
				cm_RequestChangeAttribute();
				cm_SendSetGebBesitzer(inst->id, ent->entity_id, ent->entity_id);
				fcn_004c6090(inst, 1, 0, ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[inst->office].worker_kind[0]);
				cm_SendSellObjekt(inst->id, -1, 0x135, 1, (*(char*)&g_773d75), 0);
			}
		}
	}
}
