extern char g_85a224[];
#include "Develop/client_types.h"
typedef struct { unsigned char kind, unknown01[0x24c]; } BuildingProto5167c0;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;
extern char* g_7f3b24;
extern char* g_7f3ee0;
extern char gm_EntitySlotTable[];
extern char s_6a1fdc[];
extern char* d2_VisitedBuilding;
extern char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;
extern char d3_GfxDetails;
extern char d3_CurrentSeason;
extern char g_6b8061;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int evt_ActiveContextId;
extern int g_6b86d8;
extern int d3_ActiveScene;
extern float g_67a964;

int __cdecl gm_GetSeason(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned short* __cdecl gm_QueryEntities(int, int, ...);
void __cdecl d3_SetInteriorLightingDefaults(void);
void __cdecl d3_SetExteriorLightingDefaults(void);
char* __cdecl d3_FindSceneObject(char*, int, char*, char*);
char __cdecl d3_SetSubtreeVisible(int, unsigned char);
int __cdecl gm_CheckEntityType(char*);
void __cdecl d3_TraverseSceneObjects(int, int, int, void (__cdecl*)(void));
void __cdecl d3_ShowPflanzenMapEntries(int);
void __cdecl ch_CollectContextCharacters(char*);
void __cdecl gm_UpdateResidenceOwnerDecor(char*);
int __cdecl d3_GetContextIndex(int);
void __cdecl ch_SetVisible(char*, int);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
void __cdecl d3_UpdateEntityTextureVariant(char*);
void __cdecl ch_AssignHeadIcon(char*);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl ch_UpdateAttachedModelPosition(char*, int);
void __cdecl d3_ApplyVegetationTextureSet(void);
void __cdecl d3_ApplySeasonTextureSet(void);
void __cdecl d3_UpdateBuildingSlotVisibility(void);
void __cdecl d3_InitGateNodeFlags(void);

/* ADDRESS: GOLDTL 0x005167c0 */
/* ADDRESS: GOLDDE 0x00501230 */
void __cdecl d3_UpdateBuildingView(unsigned char* building, int queryId)
{
	int mode;
	int type;
	int count;
	int i;
	BUILDING_PROTOTYPE* rec;
	unsigned char* entity;
	unsigned char* obj;
	unsigned char** p;

	mode = gm_GetSeason(&(*(char*) &gm_GameTime));
	gm_GetBuildingTypeCategory(*building);
	rec = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building];
	entity = (unsigned char*) gm_QueryEntities(*(int*) (building + 0x5d), 1, 0, queryId);
	if (entity != 0 && *(unsigned short*) entity != 0xfd) {
		type = ((signed char*) init_SceneContextIndices)[*(unsigned short*) entity];
		g_7f3b24 = (char*) entity;
		d3_SetInteriorLightingDefaults();
	} else {
		type = d3_BuildingCategorySceneIndices[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building].category];
		g_7f3b24 = 0;
		d3_SetExteriorLightingDefaults();
	}
	if (d3_CurrentContextIndex != type
	    || (d2_VisitedBuilding != 0 && (unsigned char*) d2_VisitedBuilding != building)
	    || (d2_InteriorBuilding != 0 && (unsigned char*) d2_InteriorBuilding != building)) {
		return;
	}
	obj = (unsigned char*) d3_FindSceneObject(0, 0x180, 0, s_6a1fdc);
	if (obj != 0) {
		if (!d3_GfxDetails) {
			d3_SetSubtreeVisible((int) obj, 0);
		} else {
			d3_SetSubtreeVisible((int) obj, 1);
		}
	}
	g_67530c = *(int*) (building + 1);
	if (sv_SelectedBuilding != 0) {
		evt_ActiveContextId = *(int*) (sv_SelectedBuilding + 2);
	} else {
		evt_ActiveContextId = *(int*) (building + 1);
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
	g_6b8061 = 0;
	g_67a964 = 1.0f;
	g_6b86d8 = 0x800;
	if (gm_CheckEntityType((char*) building)) {
		d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xc0, d3_ApplyVegetationTextureSet);
		d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xc0, d3_ApplySeasonTextureSet);
	}
	if (*building == 0x1e && queryId == 0xfd) {
		d3_ShowPflanzenMapEntries(*(int*) (building + 0x71));
	}
	g_7f3ee0 = (char*) building;
	ch_CollectContextCharacters((char*) building);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x1e0, d3_UpdateBuildingSlotVisibility);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x20, d3_InitGateNodeFlags);
	gm_UpdateResidenceOwnerDecor((char*) building);
	i = 0;
	if (rec->category == 0x16) {
		count = 8;
	} else {
		count = (rec->category == 1) ? 4 : 8;
	}
	p = (unsigned char**) ch_CharacterSlots;
	do {
		obj = *p;
		if (obj != 0 && d3_GetContextIndex(*(int*) (obj + 0x88)) == type) {
			if (*(int*) (obj + 0x2c) != *(int*) (building + 1)
			    && *(int*) (obj + 0x30) != *(int*) (entity + 2)) {
				ch_SetVisible((char*) obj, 0);
			} else {
				ch_SetVisible((char*) obj, 1);
				ch_PlaceOnGround((char*) obj, 0);
			}
		}
		p++;
	} while ((int) p < ((int) &ch_CharacterSlots + 0xc00));
	p = (unsigned char**) (gm_EntitySlotTable + 0x184);
	do {
		obj = *p;
		if (obj != 0 && d3_GetContextIndex(*(int*) (obj + 0x88)) == type) {
			obj = *p;
			if ((*(int*) (obj + 0x2c) == *(int*) (building + 1)
			     || *(int*) (obj + 0x30) == *(int*) (entity + 2))
			    && i < count) {
				ch_SetVisible((char*) obj, 1);
				ch_PlaceOnGround((char*) *p, 0);
				d3_UpdateEntityTextureVariant((char*) p - 0x184);
				ch_AssignHeadIcon((char*) p - 0x184);
				i++;
			} else {
				ch_SetVisible((char*) obj, 0);
			}
		}
		p = (unsigned char**) ((char*) p + 0x21c);
	} while ((int) p < (int) &g_85a224);
	p = (unsigned char**) gm_QueryEntities(0, 2, 7, 4, 0x1d);
	while (p != 0) {
		obj = (unsigned char*) *(void**) ((char*) p + 0x3b);
		if (*(int*) (obj + 0x88) == d3_ActiveScene && *(int*) (obj + 0x2c) == *(int*) (building + 1)) {
			ch_SetVisible((char*) obj, 1);
			ch_PlaceOnGround((char*) obj, 0);
			ch_UpdateAttachedModelPosition((char*) obj, 1);
		} else if (*(int*) (obj + 0x88) == d3_ActiveScene) {
			ch_SetVisible((char*) obj, 0);
		}
		p = (unsigned char**) gm_NextEntityQueryMatch();
	}
}
