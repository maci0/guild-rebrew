#include <string.h>
extern char* lpObjektePROT;
extern float g_664138, g_662a7c, g_662a6c;
extern char g_67e330[];
#pragma pack(push, 1)
typedef struct {
    unsigned char unknown000[0x22], count;
    unsigned short entries[0x40];
    unsigned char unknown0a3[0x1aa];
} BuildingProto487470;
#pragma pack(pop)
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int lpGebaeudePROT;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char gm_EntitySlotTable[];
extern char gm_SlotTableKindView[];
extern unsigned char gm_ActiveTownIndex;
unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_GetEntityMood(unsigned char* e);
int __cdecl gm_CalculateGebaeudeValue(int, int);
char* __cdecl gm_QueryEntities(int, int, int, int, ...);
float __cdecl eval_ObjektPreis2Credits(int id, int pct);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_SendTraceEnd(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_SendCopyEntityData(void*);
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* Picks a trade partner for the selected market stall and sends the offer.
 * The candidate list of the stall belongs to the entity table row of the
 * current shop; the first pass prefers a partner that the guild filter does
 * not already lock out, the fallback pass only accepts the first free one. */
/* ADDRESS: GOLDTL 0x00487470 */
void __cdecl ai_BuyStallGoods(char* actor)
{
	unsigned int found;
	int cand;
	float amountf;
	unsigned char pkt2[0xf8];
	unsigned char pkt1[0xf8];
	char* p;
	BUILDING_PROTOTYPE* row;
	char* building;
	char* other;
	int i;
	int id;
	int amount;
	char kind;
	unsigned short w;
	unsigned short* entry;

	found = 0;
	cand = 0xfd;
	if (*(unsigned char*) (actor + 0x1c8) & 8) {
		return;
	}
	if ((short) gm_GameTimeHour != 7 && (short) gm_GameTimeHour != 0xc && (short) gm_GameTimeHour != 0x12) {
		*(int*) (actor + 0x1b4) &= ~0x400;
		return;
	}
	if (*(int*) (actor + 0x1b4) & 0x400) {
		return;
	}
	p = (char*) *(int*) (actor + 0x16c);
	*(int*) (actor + 0x1b4) |= 0x400;
	kind = (char)((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (p + 0x27)].entity_state;
	if (kind != 6 && kind != 7) {
		return;
	}
	if (!(*(int*) (actor + 0x1b4) & 8)) {
		return;
	}
	if (gm_GetEntityMood((unsigned char*) p) < gm_RandomMod(0x14) + 0x4b) {
		amountf = (float) gm_CalculateGebaeudeValue(*(int*)(actor + 0x16c), 100) * g_664138 * g_664138;
		if (g_662a7c > amountf) {
			amountf = 128.0f;
		}
		if ((float) *(int*) (actor + 0x1b8) * g_662a6c > amountf) {
			memset(pkt1, 0, 0xf8);
			p = *(char**)(actor + 0x16c);
			pkt1[4] = 0x1c;
			*(int*) (pkt1 + 0xc) = -1;
			pkt1[0x36] = 1;
			*(int*) (pkt1 + 8) = ((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*) (p + 0x27)].entity_id;
			*(int*) (pkt1 + 0x58) = *(int*) (p + 1);
			*(int*) (pkt1 + 0x5c) = 100 - *(char*) (p + 0x5c);
			cm_SendLogAction(g_67e330);
			p = *(char**)(actor + 0x16c);
			cm_RequestMoveCredits(-1,
						 ((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*) (p + 0x27)].entity_id,
						 (char) gm_ActiveTownIndex,
						 (int) amountf);
			cm_SendCopyEntityData(pkt1);
			cm_SendTraceEnd(g_67e330);
			p = *(char**)(actor + 0x16c);
			other = gm_GetEntityTableEntry(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (p + 0x27)]));
			if (other != 0) {
				*(int*) (other + 0x44) = (int) ((float) *(int*) (other + 0x44) + amountf);
			}
			*(int*) (actor + 0x1b8) = (int) ((float) *(int*) (actor + 0x1b8) - amountf);
		}
	}
	p = (char*) *(int*) (actor + 0x16c);
	id = *(unsigned char*) p;
	row = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[id];
	if (row->component_count > 0) {
		i = 0;
		entry = row->components;
		do {
			if (found != 0) {
				goto have;
			}
			w = *entry;
			if (w & 0x7fff) {
				id = w & 0x7fff;
				kind = *(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id]));
				if (kind != 2 && kind != 6) {
					if (cand != 0xfd && gm_QueryEntities(*(int*) (*(int*) (actor + 0x16c) + 0x5d), 2, 6, 0, id) == 0) {
						found = *entry & 0x7fff;
					}
				} else {
					cand = id;
				}
			}
			i++;
			entry++;
		} while (i < row->component_count);
		if (found != 0) {
			goto have;
		}
	}
	i = 0;
	cand = 0;
	if (row->component_count <= 0) {
		return;
	}
	entry = row->components;
	do {
		if (found != 0) {
			goto have;
		}
		w = *entry;
		if (w & 0x7fff) {
			id = w & 0x7fff;
			kind = *(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id]));
			if (kind != 2 && kind != 6) {
				if (cand == 0xfd && gm_QueryEntities(*(int*) (*(int*) (actor + 0x16c) + 0x5d), 2, 6, 0, id) == 0) {
					found = *entry & 0x7fff;
				}
			} else {
				cand = id;
			}
		}
		i++;
		entry++;
	} while (i < row->component_count);
	if (found == 0) {
		return;
	}

have:
	p = gm_QueryEntities(*(int*) (*(int*) (actor + 0x16c) + 0x5d), 1, 0, cand);
	if (p != 0) {
		amount = (int) eval_ObjektPreis2Credits(found, 100);
		if (*(int*) (actor + 0x1b8) > amount * 3) {
			memset(pkt2, 0, 0xf8);
			building = *(char**)(actor + 0x16c);
			pkt2[4] = 2;
			*(int*) (pkt2 + 8) = ((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*) (building + 0x25)].entity_id;
			*(int*) (pkt2 + 0xc) = *(int*) (building + 1);
			*(int*) (pkt2 + 0x28) = gm_GameTime;
			*(int*) (pkt2 + 0x2c) = gm_GameTimeHour;
			*(int*) (pkt2 + 0x30) = gm_GameTimeSliceDword;
			*(unsigned short*) (pkt2 + 0x34) = gm_GameTimeTailWord;
			pkt2[0x36] = 1;
			*(unsigned short*) (pkt2 + 0x58) = (unsigned short) found;
			*(int*) (pkt2 + 0x5c) = *(int*) (p + 2);
			*(int*) (pkt2 + 0x64) = 1;
			other = gm_GetEntityTableEntry(((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (building + 0x25)]));
			if (other != 0) {
				*(int*) (other + 0x40) = *(int*) (other + 0x40) + amount;
			}
			cm_SendLogAction((char*) 0x67e31c);
			building = *(char**)(actor + 0x16c);
			cm_RequestMoveCredits(-1,
						 ((ENTITY_RECORD*)0x7f4ca0)[*(unsigned short*) (building + 0x25)].entity_id,
						 (char) gm_ActiveTownIndex,
						 amount);
			cm_SendCopyEntityData(pkt2);
			cm_SendTraceEnd((char*) 0x67e31c);
			*(int*) (actor + 0x1b8) = *(int*) (actor + 0x1b8) - amount;
		}
	}
	*(int*) (actor + 0x1c8) |= 8;
}
