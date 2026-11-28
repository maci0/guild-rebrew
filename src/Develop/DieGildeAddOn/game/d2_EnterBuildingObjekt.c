#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int main_LoopFlags;
extern char* d2_EnteredBuildingEntity;
extern char* d2_EnteredBuildingObjekt;
extern char g_7e2714[];
extern char* lpGebaeudePROT;

/* SIZE 0x24d: building prototype row of lpGebaeudePROT */
typedef struct {
	unsigned char type;
	char rest[0x24c];
} BUILDING_PROTO_VIEW;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* d2_VisitedBuilding;
extern char* d2_InteriorBuilding;
extern char* sv_SelectedBuilding;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern char gm_EntityBlockedField[];
extern char gm_EntityIdField[];
extern char g_1043690[];

char* __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3);
int __cdecl gm_CheckEntityType(void* p);
int __cdecl gm_IsWarehouse(void* p);
int __cdecl init_EnsureObjektSceneContext(void* p);
void __cdecl init_LoadObjektScene(int id);
void __cdecl main_ExitToFrameHandler(void* p);

/* ADDRESS: GOLDTL 0x00526920 */
void __cdecl d2_EnterBuildingObjekt(char* buildingRecord, int objektId, char* entryText)
{
	char* hit;
	char* old;
	int saved;
	BUILDING_PROTO_VIEW* row;
	int n;

	hit = 0;
	if (d2_InsideBuildingActive != 0) {
		return;
	}
	if ((main_LoopFlags & 0x10000) != 0) {
		return;
	}
	if (gm_LocalPlayerSlot != 0xffff && gm_EntityBlockedField[(int) gm_LocalPlayerSlot * 540] != 0) {
		row = &((BUILDING_PROTO_VIEW*) lpGebaeudePROT)[(unsigned char) *buildingRecord];
		if (row->type != 6 && (row->type != 4 || *(int*) (buildingRecord + 0x65) != *(int*) (gm_EntityIdField + (int) gm_LocalPlayerSlot * 540))) {
			return;
		}
	}
	if (d2_VisitedBuilding != 0) {
		hit = d2_VisitedBuilding;
	} else if (d2_InteriorBuilding != 0) {
		hit = d2_InteriorBuilding;
	}
	d2_EnteredBuildingEntity = buildingRecord;
	d2_EnteredBuildingObjekt = fcn_00502cd0(*(int*) (buildingRecord + 0x5d), 1, 1, objektId);
	if (*buildingRecord == 0x47) {
		d2_EnteredBuildingObjekt = fcn_00502cd0(*(int*) (buildingRecord + 0x5d), 1, 0, 0xfd);
	}
	strcpy(g_7e2714, entryText);
	d2_InsideBuildingActive = 1;
	if (d2_EnteredBuildingObjekt != 0 && *(unsigned short*) d2_EnteredBuildingObjekt != 0) {
		if (d2_EnteredBuildingObjekt != sv_SelectedBuilding) {
			if (buildingRecord == hit) {
				if (gm_CheckEntityType(hit) != 0) {
					*(unsigned short*) (buildingRecord + 0x29) = *(unsigned short*) d2_EnteredBuildingObjekt;
					if (sv_SelectedBuilding != 0) {
						d2_DialogCloseRequested = g_774650 - g_774658 + 1;
						return;
					}
					d2_DialogCloseRequested = g_774650 - g_774658;
					return;
				}
			}
			*(unsigned short*) (buildingRecord + 0x29) = *(unsigned short*) d2_EnteredBuildingObjekt;
			old = sv_SelectedBuilding;
			saved = g_774670;
			if (gm_CheckEntityType(buildingRecord) == 0 && gm_IsWarehouse(buildingRecord) == 0) {
				sv_SelectedBuilding = d2_EnteredBuildingObjekt;
				d2_InsideBuildingActive = 0;
				g_774670 = 0;
				n = init_EnsureObjektSceneContext(d2_EnteredBuildingObjekt);
				if (g_1043690[n * 988 + 5] != 0) {
					init_LoadObjektScene(*(unsigned short*) d2_EnteredBuildingObjekt);
				}
				sv_SelectedBuilding = old;
				d2_InsideBuildingActive = 1;
				g_774670 = saved;
			}
			main_ExitToFrameHandler((void*) 0x59a340);
			return;
		}
		if (g_774650 > g_774658) {
			d2_DialogCloseRequested = g_774650 - g_774658;
			return;
		}
		d2_InsideBuildingActive = 0;
		return;
	}
	if (hit == buildingRecord && d2_InteriorBuilding == 0) {
		d2_InsideBuildingActive = 0;
		return;
	}
	main_ExitToFrameHandler((void*) 0x59a340);
}
unsigned char _dpad_7e2708[88];
