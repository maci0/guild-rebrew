#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

typedef struct Req {
	int id;
	unsigned short x4;
} Req;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"










typedef struct Packet {
	int x0;
	unsigned char type;
	char pad5[3];
	int x8;
	int xc;
	char pad10[0x18];
	int x28;
	int x2c;
	int x30;
	short x34;
	unsigned char x36;
	char pad37[0x21];
	int x58;
	char pad5c[0x9c];
} Packet;
// SIZE 0xf8


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);

unsigned short __cdecl gm_RandomMod(int);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl cm_SendCopyEntityData(Packet*);

/* ADDRESS: GOLDTL 0x004ba080 */
int __cdecl fcn_004ba080(Req* r)
{
	char* o;
	float dist;
	char* list[8];
	char buf[0x200];
	int buildingCount;
	int playerCount;
	int i;
	char* e;
	char* building;
	char* player;

	buildingCount = 0;
	player = 0;
	o = gm_LookupEntityRecordById(r->id);
	if (o == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(o, 0x290) != 0) {
		return 0x400;
	}
	e = gm_StartFilteredEntitySearch(1, 3, *(unsigned short*) o);
	if (e == 0) {
		return 0x400;
	}
	do {
		if (buildingCount >= 8) {
			break;
		}
		if (gm_GetBuildingTypeCategory(*(unsigned char*) e) == 1) {
			list[buildingCount] = e;
			buildingCount++;
		}
		e = gm_FindNextFilteredEntity();
	} while (e != 0);
	if (buildingCount == 0) {
		return 0x400;
	}
	playerCount = 0;
	building = list[gm_RandomMod(buildingCount)];
	for (i = 0; i < 768; i++) {
		if (playerCount >= 6) {
			break;
		}
		if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 0 && ((ENTITY_RECORD*)g_7f4ca0)[i].unk_16c == building && ((ENTITY_RECORD*)g_7f4ca0)[i].unk_165[0] != 0) {
			list[playerCount] = (char*) &((ENTITY_RECORD*)g_7f4ca0)[i];
			playerCount++;
		}
	}
	if (playerCount > 2) {
		player = list[gm_RandomMod(playerCount)];
	}
	if (building == 0 || player == 0) {
		return 0x400;
	}
	dist = fcn_0050f980(*(unsigned short*) o, *(unsigned short*) player, 1);
	if (!((float) gm_RandomMod(50) > dist)) {
		return 0x400;
	}
	io_FormatTextBuffer(buf, r->x4 + 0x12e7, (player[9] ? 0x230 : 0x20d) + *(unsigned char*) (player + 0x165),
		*(unsigned short*) player, building);
	fcn_00545d40(*(int*) (o + 4), *(int*) (o + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	{
		Packet msg;

		memset(&msg, 0, sizeof(msg));
		msg.x8 = *(int*) (o + 4);
		msg.xc = *(int*) (building + 1);
		msg.x28 = (*(int*)&gm_GameTime);
		msg.x2c = (*(int*)&g_7f4c04);
		msg.x30 = g_7f4c08;
		msg.type = 0x31;
		msg.x36 = 1;
		msg.x34 = g_7f4c0c;
		msg.x58 = *(int*) (player + 4);
		cm_SendCopyEntityData(&msg);
	}
	return 0;
}
