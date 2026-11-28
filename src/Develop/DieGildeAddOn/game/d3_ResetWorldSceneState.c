

// SIZE 0x230
typedef struct Obj {
	char pad0[0x2c];
	int owner;
	char pad30[4];
	struct Obj* body;
	char pad38[0x50];
	int model;
	char pad8c[0x140];
	int visible;
	char pad1d0[0x5c];
	struct Obj* rider;
} Obj;

// SIZE 0x21c
typedef struct {
	char pad0[0x184];
	Obj* obj;
	char pad188[0x94];
} Entity;

// SIZE 0xa4
typedef struct {
	char pad0[0x88];
	float zoom;
	char pos[0x14];
	int angle;
} View;

// SIZE 0x8c
typedef struct {
	char pad0[0x84];
	char pos[4];
	int angle;
} Camera;

typedef void (__cdecl* Notify)(void*, int, void*, int);

// SIZE 0x218
typedef struct {
	char pad0[0x210];
	Notify notify;
	char arg[4];
} Hook;

// SIZE 0x3cc
typedef struct {
	char pad0[0x3c8];
	Hook* hook;
} Scene;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/d3_camera.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char d3_CurrentSeason;
extern int d3_ActiveScene;
extern int d3_CurrentFloor;
extern int g_77666c;
extern char g_6b8061;
extern int evt_ActiveContextId;
extern float g_67a964;
extern char g_6b859b;

int __cdecl gm_GetSeason(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl d3_SetNodePosition(Camera*, char*);
void __cdecl d3_SetCameraHeightFraction(float);
void __cdecl d3_SetObjectRotation(Camera*, char*);
int __cdecl d3_GetContextIndex(int);
void __cdecl ch_EnsureCharacterMeshes(Obj*);
void __cdecl ch_SetVisible(Obj*, int);
void __cdecl d3_UpdateEntityTextureVariant(Entity*);
void __cdecl d3_TraverseSceneObjects(Scene*, int, int, void (__cdecl*)(void));
void __cdecl d3_ApplyVegetationTextureSet(void);
void __cdecl d3_ApplySeasonTextureSet(void);
void __cdecl d3_SetExteriorLightingDefaults(void);
void __cdecl d3_UpdateTerrainSeasonTextures(void);
void __cdecl d3_UpdateSceneDetailLevel(int, int);
void __cdecl d3_UpdateDaylightPhase(char*);
#include "Develop/Units/d3/d3_d3d.h"

/* ADDRESS: GOLDDE 0x005019d0 */
void __cdecl d3_ResetWorldSceneState(void)
{
	int mode;
	View* view;
	int i;

	mode = gm_GetSeason(&(*(char*)&gm_GameTime));
	if (d3_CurrentContextIndex != 0) {
		return;
	}
	view = (View*) gm_GetEntityTableEntry((char*) (&((Entity*)gm_EntitySlotTable)[gm_LocalPlayerSlot]));
	if (view != 0 && view->zoom != -1.0f) {
		d3_SetNodePosition(((Camera*)d3_ActiveCamera), view->pos);
		d3_SetCameraHeightFraction(view->zoom);
		((Camera*)d3_ActiveCamera)->angle = view->angle;
		d3_SetObjectRotation(((Camera*)d3_ActiveCamera), ((Camera*)d3_ActiveCamera)->pos);
	} else {
		d3_SetCameraHeightFraction(0.33f);
	}
	for (i = 0; i < 768; i++) {
		if (((Entity*)gm_EntitySlotTable)[i].obj != 0 && d3_GetContextIndex(((Entity*)gm_EntitySlotTable)[i].obj->model) == 0 && ((Entity*)gm_EntitySlotTable)[i].obj->owner == -1) {
			if (((Entity*)gm_EntitySlotTable)[i].obj->body->visible == 0
				|| (((Entity*)gm_EntitySlotTable)[i].obj->rider != 0 && ((Entity*)gm_EntitySlotTable)[i].obj->rider->visible == 0)) {
				ch_EnsureCharacterMeshes(((Entity*)gm_EntitySlotTable)[i].obj);
			}
			ch_SetVisible(((Entity*)gm_EntitySlotTable)[i].obj, 1);
			d3_UpdateEntityTextureVariant(&((Entity*)gm_EntitySlotTable)[i]);
		}
	}
	if (mode == 1) {
		d3_CurrentSeason = 1;
	} else if (mode == 0) {
		d3_CurrentSeason = 0;
	} else if (mode == 2) {
		d3_CurrentSeason = 2;
	} else if (mode == 3) {
		d3_CurrentSeason = 3;
	}
	d3_TraverseSceneObjects((*(Scene**)&d3_ActiveScene), 0, 0xe0, d3_ApplyVegetationTextureSet);
	d3_TraverseSceneObjects((*(Scene**)&d3_ActiveScene), 0, 0xc0, d3_ApplySeasonTextureSet);
	d3_SetExteriorLightingDefaults();
	if ((*(Scene**)&d3_ActiveScene) != 0 && (*(Scene**)&d3_ActiveScene)->hook != 0 && (*(Scene**)&d3_ActiveScene)->hook->notify != 0) {
		(*(Scene**)&d3_ActiveScene)->hook->notify((*(Scene**)&d3_ActiveScene), 4, (*(Scene**)&d3_ActiveScene)->hook->arg, 0);
	}
	d3_UpdateTerrainSeasonTextures();
	d3_UpdateSceneDetailLevel(d3_CurrentFloor, 0);
	g_6b8061 = 1;
	evt_ActiveContextId = 0;
	g_67a964 = 1.0f - (unsigned char) g_77666c * 0.01f;
	d3_UpdateDaylightPhase(&(*(char*)&gm_GameTime));
	if (g_6b859b != 0) {
		d3_PrecacheAllSceneTextures(0);
	} else {
		d3_PrecacheAllSceneTextures(1);
	}
}
