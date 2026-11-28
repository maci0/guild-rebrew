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
extern int d3_ActiveScene;
extern char* gm_CityEntity;
extern unsigned char gm_ActiveTownIndex;
extern char gm_TownTable[];
extern int d3_CurrentFloor;

void __cdecl gm_LoadCityIniData(char*, int);
void __cdecl d3_SelectSceneContext(int, int);
char __cdecl d3_LoadCityScene(char*);
void __cdecl srv_InitBuildingTypeTable(void);
void __cdecl cm_InitCrimeRecords(void);
int __cdecl main_GetLanguage(void);
void* __cdecl d3_FindSceneObject(int, int, int, char*);

void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl gm_BindBuildingSceneObjects(void);
void __cdecl d3_ResolveSceneObjectProtoId(void);
void __cdecl d3_InheritSceneNodeData(void);
void __cdecl d3_PlaceBuildingProxyBoxes(char*);
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
void __cdecl gm_UpdateAllTownSeasonPrices(void);
void __cdecl gm_InitTownGoodsTable(int);
void __cdecl gm_UpdateMarketStockSlots(int);
int __cdecl d3sm_CreateMap(Device*, int, int);

int __cdecl gm_LoadCityMap(char* map)
{
	void* folder;
	int h;
	int i;
	void* s;

	gm_NextEntityId = 1;
	gm_LoadCityIniData(map, 0);
	d3_SelectSceneContext(0, 0);
	if (d3_LoadCityScene(map) == 0) {
		return 1;
	}
	srv_InitBuildingTypeTable();
	cm_InitCrimeRecords();
	if (main_GetLanguage() != 0) {
		folder = d3_FindSceneObject(0, 0x100, 0, "ordner_CITIES_GER");
	} else {
		folder = d3_FindSceneObject(0, 0x100, 0, "ordner_CITIES_INT");
	}
	if (folder != 0) {
		d3_DestroyObject((D3_OBJECT*) (folder));
	}
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x140, gm_BindBuildingSceneObjects);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x40, d3_ResolveSceneObjectProtoId);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x20, d3_InheritSceneNodeData);
	d3_PlaceBuildingProxyBoxes("bk_BRUNNEN");
	d3_PlaceBuildingProxyBoxes("bk_GEFAENGNIS");
	d3_PlaceBuildingProxyBoxes("bk_HANDWERK");
	d3_PlaceBuildingProxyBoxes("bk_KIRCHE_KL");
	d3_PlaceBuildingProxyBoxes("bk_KIRCHE_MT");
	d3_PlaceBuildingProxyBoxes("bk_KIRCHE_GR");
	d3_PlaceBuildingProxyBoxes("bk_RATHAUS");
	d3_PlaceBuildingProxyBoxes("bk_STADTWACHE");
	d3_PlaceBuildingProxyBoxes("bk_WIRTSHAUS_KL");
	d3_PlaceBuildingProxyBoxes("bk_WIRTSHAUS_GR");
	d3_PlaceBuildingProxyBoxes("bk_WOHNSITZ_KL");
	d3_PlaceBuildingProxyBoxes("bk_WOHNSITZ_GR");
	d3_PlaceBuildingProxyBoxes("bk_ZUNFTHAUS");
	d3_PlaceBuildingProxyBoxes("bk_RAUBRITTERFESTE");
	d3_PlaceBuildingProxyBoxes("bk_DOMIZIL");
	d3_PlaceBuildingProxyBoxes("bk_STATUEN");
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
	cm_RequestMoveCredits((*(Figure**)&gm_CityEntity)->id, -1, (*(char*)&gm_ActiveTownIndex), 200000000);
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		ls_ID2Ptr();
	}
	cm_EndCommandSync();
	for (i = 1; i < 4; i++) {
		if (((Variant*)gm_TownTable)[i].used != 0) {
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
	gm_UpdateAllTownSeasonPrices();
	for (i = 0; i < 4; i++) {
		if (((Variant*)gm_TownTable)[i].name[0] == 0) {
			break;
		}
		gm_InitTownGoodsTable(i);
	}
	cm_BeginCommandSync();
	gm_UpdateMarketStockSlots((unsigned char) (*(char*)&gm_ActiveTownIndex));
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_StepCommandQueue();
	}
	d3_SelectSceneContext(1, 0);
	d3_SelectSceneContext(0, 0);
	if (((Device*)d3_CurrentFloor)->kind == 0x80) {
		((Scene*) d3_ActiveScene)->view = d3sm_CreateMap(((Device*)d3_CurrentFloor), 0x100, 2);
	} else if (((Device*)d3_CurrentFloor)->kind == 0x40) {
		((Scene*) d3_ActiveScene)->view = d3sm_CreateMap(((Device*)d3_CurrentFloor), 0x80, 2);
	} else {
		((Scene*) d3_ActiveScene)->view = d3sm_CreateMap(((Device*)d3_CurrentFloor), 0x100, 2);
	}
	return 0;
}
