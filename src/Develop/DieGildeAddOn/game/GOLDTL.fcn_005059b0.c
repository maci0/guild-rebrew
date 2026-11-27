#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


#pragma pack(push, 1)
// SIZE 0x65
typedef struct {
	unsigned char type;
	int key;
	char pad5[0x20];
	unsigned short owner;
	unsigned short slot;
	char pad29[0x38];
	int placed;
} Estate;

// SIZE 0xe
typedef struct {
	char pad0[0xa];
	int id;
} Link;

// SIZE 0x1d0
typedef struct Model {
	char pad0[0x34];
	struct Model* body;
	char pad38[0x50];
	int res;
	char pad8c[0x98];
	struct Model** parts;
	char pad128[0xa4];
	int visible;
} Model;

// SIZE 0x43
typedef struct {
	unsigned short kind;
	char pad2[8];
	int id;
	char pade[6];
	Link* link;
	char pad18[4];
	int key;
	char pad20[0x1b];
	Model* model;
	char pad3f[4];
} Obj;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	char pad0[2];
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x4c];
	int scene;
	char pad58[0x118];
	Estate* best;
	char pad174[0xa8];
} Entity;

// SIZE 0x170
typedef struct {
	char pad0[0x165];
	char busy;
	char pad166[6];
	int task;
	char pad170[0x44];
	int flags;
} Figure;

extern unsigned char* lpGebaeudePROT;
extern unsigned short* lpObjekteINST;
extern char* lpObjektePROT;
extern char g_7f4ca0[];
extern char* gm_CityEntity;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl hp_RemoveProdEntry(int);
void __cdecl hp_AddProdSetting(Estate*);
void __cdecl gm_UpdateResidenceOwnerDecor(Estate*);
Figure* __cdecl fcn_0050dc90(Estate*);
int __cdecl d3_GetContextIndex(int);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_00402aa0(Model*);
void __cdecl SelectTextureSet(Model*, int, int, int);
void __cdecl fcn_0052dd80(Estate*);
void __cdecl fcn_0052d9d0(Estate*);

void __cdecl gm_AssignBuildingOwner(Estate* building, unsigned short owner, int slot)
{
	char* rec;
	Entity* slot_ent;
	Figure* fig;
	Obj* obj;
	Model* model;
	int saved;
	int sc;
	int i;

	rec = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[building->type];
	building->owner = owner;
	if (slot == 0xffff) {
		return;
	}
	if (building->slot != slot) {
		if (building->slot != 0xffff && ((Entity*)g_7f4ca0)[building->slot].type == 6) {
			hp_RemoveProdEntry(building->key);
		}
		if (((Entity*)g_7f4ca0)[slot].type == 6) {
			hp_AddProdSetting(building);
		}
	}
	if (building->slot != 0xffff && ((Entity*)g_7f4ca0)[building->slot].best == building) {
		((Entity*)g_7f4ca0)[building->slot].best = 0;
	}
	building->slot = slot;
	if (((char)(((BUILDING_PROTOTYPE*)rec)->category)) == 2) {
		gm_UpdateResidenceOwnerDecor(building);
		if (((char)(((BUILDING_PROTOTYPE*)rec)->category)) == 2) {
			if (((Entity*)g_7f4ca0)[building->slot].best == 0 || ((Entity*)g_7f4ca0)[building->slot].best->type <= building->type) {
				((Entity*)g_7f4ca0)[building->slot].best = building;
			}
		}
	}
	if (((Entity*)g_7f4ca0)[slot].type == 6 || ((Entity*)g_7f4ca0)[slot].type == 7) {
		fig = fcn_0050dc90(building);
		if (fig != 0) {
			fig->busy = 0;
			fig->flags &= ~1;
			if (((char)(((BUILDING_PROTOTYPE*)rec)->category)) == 5 || ((char)(((BUILDING_PROTOTYPE*)rec)->category)) == 9) {
				fig->task = 0;
			}
		}
	}
	obj = ((Obj*)lpObjekteINST);
	for (i = 0x5008; i != 0; i--) {
		if (obj->kind != 0 && (*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[obj->kind].kind) == 0x1d && obj->key == building->key) {
			obj->id = ((Entity*)g_7f4ca0)[slot].id;
			if (obj->link != 0) {
				obj->link->id = ((Entity*)g_7f4ca0)[slot].id;
			}
			saved = d3_CurrentContextIndex;
			model = obj->model;
			if (((Entity*)g_7f4ca0)[slot].scene != 0 && (((Entity*)g_7f4ca0)[slot].type == 5 || ((Entity*)g_7f4ca0)[slot].type == 6 || ((Entity*)g_7f4ca0)[slot].type == 7)) {
				sc = ((Entity*)g_7f4ca0)[slot].scene - 0x599;
			} else {
				sc = 0;
			}
			d3_SelectSceneContext(d3_GetContextIndex(model->res), 1);
			if (model->body->visible == 0) {
				fcn_00402aa0(model);
			}
			SelectTextureSet(*model->parts, (*model->parts)->visible, sc, 1);
			d3_SelectSceneContext(saved, 1);
		}
		obj++;
	}
	slot_ent = &((Entity*)g_7f4ca0)[slot];
	if (slot_ent != ((Entity*)gm_CityEntity) && building->placed != 0 && (slot_ent->type == 6 || slot_ent->type == 7 || slot_ent->type == 5)) {
		saved = d3_CurrentContextIndex;
		d3_SelectSceneContext(0, 1);
		fcn_0052dd80(building);
		fcn_0052d9d0(building);
		d3_SelectSceneContext(saved, 1);
		return;
	}
	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	fcn_0052dd80(building);
	d3_SelectSceneContext(saved, 1);
}
