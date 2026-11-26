#include "client_types.h"
typedef struct { unsigned char kind, unknown01[0x24c]; } BuildingProto5167c0;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;
extern char* g_7f3b24;
extern char* g_7f3ee0;
extern char g_7f4ca0[];
extern char s_6a1fdc[];
extern char* g_7746c4;
extern char* g_7746c8;
extern char* g_7746cc;
extern char g_776664;
extern char g_773dd4;
extern char g_6b8061;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6791c8;
extern int g_6b86d8;
extern int g_67a370;
extern float g_67a964;

int __cdecl gm_GetSeason(char*);
int __cdecl gm_GetBuildingTypeCategory(int);
unsigned short* __cdecl fcn_00502cd0(int, int, ...);
void __cdecl fcn_00516b70(void);
void __cdecl fcn_00516be0(void);
char* __cdecl fcn_00445600(char*, int, char*, char*);
char __cdecl d3_SetSubtreeVisible(int, unsigned char);
int __cdecl gm_CheckEntityType(char*);
void __cdecl d3_TraverseSceneObjects(int, int, int, void (__cdecl*)(void));
void __cdecl fcn_004bd150(int);
void __cdecl ch_CollectContextCharacters(char*);
void __cdecl gm_UpdateResidenceOwnerDecor(char*);
int __cdecl d3_GetContextIndex(int);
void __cdecl ch_SetVisible(char*, int);
#include "Develop/DieGildeAddOn/game/ch_ground.h"
void __cdecl fcn_004fdcf0(char*);
void __cdecl fcn_004fdfe0(char*);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl ch_UpdateAttachedModelPosition(char*, int);
void __cdecl fcn_00516550(void);
void __cdecl fcn_005165b0(void);
void __cdecl d3_UpdateBuildingSlotVisibility(void);
void __cdecl fcn_00515ef0(void);

/* ADDRESS: GOLDTL 0x005167c0 */
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
	entity = (unsigned char*) fcn_00502cd0(*(int*) (building + 0x5d), 1, 0, queryId);
	if (entity != 0 && *(unsigned short*) entity != 0xfd) {
		type = ((signed char*) init_SceneContextIndices)[*(unsigned short*) entity];
		g_7f3b24 = (char*) entity;
		fcn_00516b70();
	} else {
		type = g_7f3b00[((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*building].category];
		g_7f3b24 = 0;
		fcn_00516be0();
	}
	if (d3_CurrentContextIndex != type
	    || (g_7746c4 != 0 && (unsigned char*) g_7746c4 != building)
	    || (g_7746c8 != 0 && (unsigned char*) g_7746c8 != building)) {
		return;
	}
	obj = (unsigned char*) fcn_00445600(0, 0x180, 0, s_6a1fdc);
	if (obj != 0) {
		if (!g_776664) {
			d3_SetSubtreeVisible((int) obj, 0);
		} else {
			d3_SetSubtreeVisible((int) obj, 1);
		}
	}
	g_67530c = *(int*) (building + 1);
	if (g_7746cc != 0) {
		g_6791c8 = *(int*) (g_7746cc + 2);
	} else {
		g_6791c8 = *(int*) (building + 1);
	}
	if (mode == 1) {
		g_773dd4 = 1;
	} else if (mode == 0) {
		g_773dd4 = 0;
	} else if (mode == 2) {
		g_773dd4 = 2;
	} else if (mode == 3) {
		g_773dd4 = 3;
	}
	g_6b8061 = 0;
	g_67a964 = 1.0f;
	g_6b86d8 = 0x800;
	if (gm_CheckEntityType((char*) building)) {
		d3_TraverseSceneObjects(g_67a370, 0, 0xc0, fcn_00516550);
		d3_TraverseSceneObjects(g_67a370, 0, 0xc0, fcn_005165b0);
	}
	if (*building == 0x1e && queryId == 0xfd) {
		fcn_004bd150(*(int*) (building + 0x71));
	}
	g_7f3ee0 = (char*) building;
	ch_CollectContextCharacters((char*) building);
	d3_TraverseSceneObjects(g_67a370, 0, 0x1e0, d3_UpdateBuildingSlotVisibility);
	d3_TraverseSceneObjects(g_67a370, 0, 0x20, fcn_00515ef0);
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
	} while ((int) p < 0x14d0c20);
	p = (unsigned char**) (g_7f4ca0 + 0x184);
	do {
		obj = *p;
		if (obj != 0 && d3_GetContextIndex(*(int*) (obj + 0x88)) == type) {
			obj = *p;
			if ((*(int*) (obj + 0x2c) == *(int*) (building + 1)
			     || *(int*) (obj + 0x30) == *(int*) (entity + 2))
			    && i < count) {
				ch_SetVisible((char*) obj, 1);
				ch_PlaceOnGround((char*) *p, 0);
				fcn_004fdcf0((char*) p - 0x184);
				fcn_004fdfe0((char*) p - 0x184);
				i++;
			} else {
				ch_SetVisible((char*) obj, 0);
			}
		}
		p = (unsigned char**) ((char*) p + 0x21c);
	} while ((int) p < 0x85a224);
	p = (unsigned char**) fcn_00502cd0(0, 2, 7, 4, 0x1d);
	while (p != 0) {
		obj = (unsigned char*) *(void**) ((char*) p + 0x3b);
		if (*(int*) (obj + 0x88) == g_67a370 && *(int*) (obj + 0x2c) == *(int*) (building + 1)) {
			ch_SetVisible((char*) obj, 1);
			ch_PlaceOnGround((char*) obj, 0);
			ch_UpdateAttachedModelPosition((char*) obj, 1);
		} else if (*(int*) (obj + 0x88) == g_67a370) {
			ch_SetVisible((char*) obj, 0);
		}
		p = (unsigned char**) gm_NextEntityQueryMatch();
	}
}
