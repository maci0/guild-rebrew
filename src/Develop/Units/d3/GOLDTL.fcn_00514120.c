#include "Develop/Units/d3/d3_object.h"



#include <string.h>

// SIZE 0x2f4
typedef struct {
	char name[0x54];
	short used;
	char pad56[0x2f4 - 0x56];
} Variant;

// SIZE 0x40
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
	char pad8[0x28];
	char name[0x10];
} Figure;

// SIZE 0xb4
typedef struct {
	char pad0[0xb0];
	int view;
} Scene;

// SIZE 0x4
typedef struct {
	int kind;
} Device;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;
extern char* gm_CityEntity;
extern unsigned char g_773d75;
extern char g_868060[];
extern int g_6b8300;

void __cdecl fcn_00517250(char*, int);
void __cdecl d3_SelectSceneContext(int, int);
char __cdecl fcn_00510b70(char*);
void __cdecl srv_InitBuildingTypeTable(void);
void __cdecl cm_InitCrimeRecords(void);
int __cdecl fcn_0051e070(void);
void* __cdecl d3_FindSceneObject(int, int, int, char*);

void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl gm_BindBuildingSceneObjects(void);
void __cdecl d3_ResolveSceneObjectProtoId(void);
void __cdecl fcn_00510b40(void);
void __cdecl fcn_00513d40(char*);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_RequestAllocRaum(int, int, int, int);
int __cdecl cm_RequestAllocSpieler(int, int, int, short, int, unsigned char, int, int);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_FlushCommandQueue(void);
void __cdecl cm_PollCommandQueue(void);
void __cdecl ls_ID2Ptr(void);
void* __cdecl gm_FindNextFilteredEntity(void);
Figure* __cdecl cm_GetCommandResult(int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl gm_InitChurchAndGuildStocks(void);
void __cdecl gm_InitializeShopInventory(void);
void __cdecl cm_StepCommandQueue(void);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_AssignBuildingOwner(void*, int, int);
void* __cdecl gm_AddObjekt(void);
void __cdecl fcn_005016c0(void);
void __cdecl fcn_005016f0(int);
void __cdecl gm_UpdateMarketStockSlots(int);
int __cdecl fcn_0045b700(Device*, int, int);

int __cdecl gm_LoadCityMap(char* map)
{
	void* folder;
	int h;
	int i;
	void* s;

	gm_NextEntityId = 1;
	fcn_00517250(map, 0);
	d3_SelectSceneContext(0, 0);
	if (fcn_00510b70(map) == 0) {
		return 1;
	}
	srv_InitBuildingTypeTable();
	cm_InitCrimeRecords();
	if (fcn_0051e070() != 0) {
		folder = d3_FindSceneObject(0, 0x100, 0, "ordner_CITIES_GER");
	} else {
		folder = d3_FindSceneObject(0, 0x100, 0, "ordner_CITIES_INT");
	}
	if (folder != 0) {
		d3_DestroyObject((D3_OBJECT*) (folder));
	}
	d3_TraverseSceneObjects(g_67a370, 0, 0x140, gm_BindBuildingSceneObjects);
	d3_TraverseSceneObjects(g_67a370, 0, 0x40, d3_ResolveSceneObjectProtoId);
	d3_TraverseSceneObjects(g_67a370, 0, 0x20, fcn_00510b40);
	fcn_00513d40("bk_BRUNNEN");
	fcn_00513d40("bk_GEFAENGNIS");
	fcn_00513d40("bk_HANDWERK");
	fcn_00513d40("bk_KIRCHE_KL");
	fcn_00513d40("bk_KIRCHE_MT");
	fcn_00513d40("bk_KIRCHE_GR");
	fcn_00513d40("bk_RATHAUS");
	fcn_00513d40("bk_STADTWACHE");
	fcn_00513d40("bk_WIRTSHAUS_KL");
	fcn_00513d40("bk_WIRTSHAUS_GR");
	fcn_00513d40("bk_WOHNSITZ_KL");
	fcn_00513d40("bk_WOHNSITZ_GR");
	fcn_00513d40("bk_ZUNFTHAUS");
	fcn_00513d40("bk_RAUBRITTERFESTE");
	fcn_00513d40("bk_DOMIZIL");
	fcn_00513d40("bk_STATUEN");
	cm_BeginCommandSync();
	cm_RequestAllocRaum(0x44, -1, 0, 0);
	cm_RequestAllocRaum(0x45, -1, 0, 0);
	h = cm_RequestAllocSpieler(0xa, -1, -1, 0x12, -1, 0, 0, 1);
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	cm_BeginCommandSync();
	(*(Figure**)&gm_CityEntity) = cm_GetCommandResult(h);
	strcpy((*(Figure**)&gm_CityEntity)->name, "STADT");
	cm_RequestMoveCredits((*(Figure**)&gm_CityEntity)->id, -1, (*(char*)&g_773d75), 200000000);
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	cm_EndCommandSync();
	for (i = 1; i < 4; i++) {
		if (((Variant*)g_868060)[i].used != 0) {
			cm_RequestMoveCredits((*(Figure**)&gm_CityEntity)->id, -1, (char) i, 200000000);
		}
	}
	gm_InitChurchAndGuildStocks();
	cm_BeginCommandSync();
	gm_InitializeShopInventory();
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_StepCommandQueue();
	}
	for (s = gm_StartFilteredEntitySearch(1, 5, 0x1c); s != 0; s = gm_FindNextFilteredEntity()) {
		gm_AssignBuildingOwner(s, (*(Figure**)&gm_CityEntity)->slot, (*(Figure**)&gm_CityEntity)->slot);
	}
	fcn_005016c0();
	for (i = 0; i < 4; i++) {
		if (((Variant*)g_868060)[i].name[0] == 0) {
			break;
		}
		fcn_005016f0(i);
	}
	cm_BeginCommandSync();
	gm_UpdateMarketStockSlots((unsigned char) (*(char*)&g_773d75));
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_StepCommandQueue();
	}
	d3_SelectSceneContext(1, 0);
	d3_SelectSceneContext(0, 0);
	if (((Device*)g_6b8300)->kind == 0x80) {
		((Scene*) g_67a370)->view = fcn_0045b700(((Device*)g_6b8300), 0x100, 2);
	} else if (((Device*)g_6b8300)->kind == 0x40) {
		((Scene*) g_67a370)->view = fcn_0045b700(((Device*)g_6b8300), 0x80, 2);
	} else {
		((Scene*) g_67a370)->view = fcn_0045b700(((Device*)g_6b8300), 0x100, 2);
	}
	return 0;
}
