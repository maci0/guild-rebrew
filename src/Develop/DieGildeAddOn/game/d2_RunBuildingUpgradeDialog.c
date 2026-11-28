#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_placement.h"

/* Message object handed to fcn_004c5530: 0xf8 bytes, same field layout the
 * other packet builders in this unit store into. */
typedef struct GOLDTL_Msg5c30 {
	int f0;                     /* 0x00 */
	unsigned char f4;           /* 0x04 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c */
	char pad10[0x18];
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	char pad37[0x21];
	int f58;                    /* 0x58 */
	char pad5c[0x9c];
} GOLDTL_Msg5c30;               /* SIZE 0xf8 */

/* Entity type record, stride 0x24d. */
typedef struct GOLDTL_EntType5c30 {
	char pad[0x247];
	unsigned char f247;
	unsigned char f248;
	char pad249[4];
} GOLDTL_EntType5c30;

/* One player/house slot, stride 0x21c. */
#include "Develop/DieGildeAddOn/game/entity_record.h"





extern unsigned char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern pos14_7f4c00 gm_GameTime;

extern double g_664e60;

int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_CanBuildBuildingType(int, int);
int __cdecl gm_GetTypeProductValue(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowModalMessageBox(void*, int);
int __cdecl gm_CheckEntityStock(void*, int, char);
int __cdecl gm_SearchTable67(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void* __cdecl gm_GetGuildHall(int);
int __cdecl gm_FindBuildingTreasury(unsigned char*);
int __cdecl d2_CheckFundsAndNotify(int, int, int, char);
void __cdecl cm_SendLogAction(char*);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_SendTraceEnd(char*);
int __cdecl fcn_0065f220(const char*, const char*);

/* ADDRESS: GOLDTL 0x005c30e0 */
void __cdecl d2_RunBuildingUpgradeDialog(unsigned char* buildingEntry)
{
	int quotedCost;
	GOLDTL_Msg5c30 msg;
	LC_GEBAEUDE_BAUPLATZ bp;
	char buf[0x200];
	char text[0x400];
	BUILDING_PROTOTYPE* rec;
	int kind;
	int m;
	int id;

	rec = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*(unsigned char*) buildingEntry];
	id = *(int*) (buildingEntry + 1);
	if (rec->level >= rec->level_limit) {
		io_FormatTextBuffer(buf, 0x17d7);
		d2_ShowModalMessageBox(buf, 0);
		return;
	}
	kind = gm_GetBuildingTypeCategory(*(unsigned char*) buildingEntry);
	if (gm_AllEntitiesControllable == 0) {
		if (kind == 1 || kind == 4 || kind == 8) {
			if (gm_CanBuildBuildingType(*(unsigned char*) buildingEntry + 1, gm_LocalPlayerSlot) != 1) {
				io_FormatTextBuffer(buf, 0x17d6);
				d2_ShowModalMessageBox(buf, 0);
				return;
			}
		} else {
			if (gm_CanBuildBuildingType(*(unsigned char*) buildingEntry + 1, gm_LocalPlayerSlot) != 1) {
				io_FormatTextBuffer(buf, 0x17d9);
				d2_ShowModalMessageBox(buf, 0);
				return;
			}
		}
	}
	lc_GetGebaeudeBauplatz(&bp, buildingEntry);
	if (bp.node != 0) {
		lc_GetBauplatzPrefix(*(unsigned char*) buildingEntry + 1, (char*) &msg);
		if (strstr((char*) &msg, bp.node) == 0) {
			io_FormatTextBuffer(buf, 0x17d8, *(unsigned char*) buildingEntry * 14 + 0x49c);
			d2_ShowModalMessageBox(buf, 0);
			return;
		}
	} else {
		lc_GetBauplatzPrefix(*(unsigned char*) buildingEntry + 1, (char*) &msg);
		if (fcn_0065f220((char*) &msg, bp.name) != 0) {
			io_FormatTextBuffer(buf, 0x17d8, *(unsigned char*) buildingEntry * 14 + 0x49c);
			d2_ShowModalMessageBox(buf, 0);
			return;
		}
	}
	quotedCost = (int) (gm_GetTypeProductValue(*(unsigned char*) buildingEntry + 1) * g_664e60);
	io_FormatTextBuffer(buf, 0x17d5, quotedCost, buildingEntry, *(unsigned char*) buildingEntry * 14 + 0x49c);
	if (kind != 3 && kind != 5) {
		if (d2_ShowModalMessageBox(buf, 0x11) == 0) {
			return;
		}
		if (gm_CheckEntityStock(&((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot], quotedCost,
		                 (char) gm_ActiveTownIndex) == 0) {
			return;
		}
		m = gm_SearchTable67(id);
		if (*(unsigned short*) (buildingEntry + 0x5a) & 0x400) {
			return;
		}
		if (!m) {
			return;
		}
		memset(&msg, 0, sizeof msg);
		msg.f4 = 0x1e;
		msg.f8 = ((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
		msg.fc = *(int*) (buildingEntry + 1);
		msg.f36 = 1;
		msg.f28 = gm_GameTime.a;
		msg.f2c = gm_GameTime.b;
		msg.f30 = gm_GameTime.c;
		msg.f34 = gm_GameTime.d;
		msg.f58 = msg.fc;
		cm_SendLogAction(g_67e968);
		cm_RequestMoveCredits(-1, ((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id,
		             (char) gm_ActiveTownIndex, quotedCost);
		cm_SendCopyEntityData((char*) &msg);
		cm_SendTraceEnd(g_67e968);
		io_FormatTextBuffer(text, 0x17da, *(unsigned char*) buildingEntry * 14 + 0x49c);
		d2_ShowModalMessageBox(text, 4);
		return;
	}
	if (kind == 3) {
		id = *(int*) ((char*) gm_GetGuildHall(1) + 0x5d);
		m = fcn_00502cd0(id, 2, 6, 0, 0x115);
		if (d2_ShowModalMessageBox(buf, 0x11) == 0) {
			return;
		}
	} else {
		m = gm_FindBuildingTreasury(buildingEntry);
		if (d2_ShowModalMessageBox(buf, 0x11) == 0) {
			return;
		}
		if (m == 0) {
			return;
		}
	}
	if (d2_CheckFundsAndNotify(m, *(int*) (m + 0x14), quotedCost, (char) gm_ActiveTownIndex) == 0) {
		return;
	}
	memset(&msg, 0, sizeof msg);
	msg.f4 = 0x1e;
	msg.f58 = *(int*) (buildingEntry + 1);
	msg.f34 = gm_GameTime.d;
	msg.f36 = 1;
	msg.fc = *(int*) (buildingEntry + 1);
	msg.f8 = ((ENTITY_RECORD*) gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id;
	msg.f30 = gm_GameTime.c;
	msg.f2c = gm_GameTime.b;
	msg.f28 = gm_GameTime.a;
	cm_SendLogAction(g_67e968);
	cm_RequestMoveCredits(-1, *(int*) (m + 2), (char) gm_ActiveTownIndex, quotedCost);
	cm_SendCopyEntityData((char*) &msg);
	cm_SendTraceEnd(g_67e968);
}
