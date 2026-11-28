extern int g_677508;
extern int g_773ddc;
extern int d3_CurrentFloor;
extern int g_6b5c80;
extern int d2_MouseRightBoundary;
extern int d2_MouseBottomBoundary;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ClientModeFlags;
extern int d2_MouseTopBoundary;
extern unsigned char d3snd_AmbientEnabled;
extern char gm_InWorldHud;
extern int g_774950;
extern int gm_GameTimeHour;
extern int g_7f4e10;
extern char gm_EntitySlotTable[];
extern char str_empty[];
extern int gm_GameTime;
extern int g_774650;
extern int g_774658;
extern int g_14ce8d4;
extern int g_14ce8e4;
extern int sv_HoveredBuilding;
extern int d3_ActiveCameraAnimation;
extern int d2_DialogButtonAction;
extern int d2_CurrentElementId;
extern int g_6a25dc;
extern int d2_SelectedBuilding;
extern int g_14ce8dc;
extern int g_14ce8cc;
extern unsigned short d2_CursorStateId;
extern int d2_SuppressOverlay;
extern int g_6772c4;
extern int d2_MouseX;
extern int d2_MouseY;
extern int gm_MarketEntity;
extern int d2_InsideBuildingActive;
extern int d2_EnteredBuildingEntity;
extern int d2_EnteredBuildingObjekt;
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl gm_GetSeason(char*);
void __cdecl d3_ResetWorldSceneState(void);
void __cdecl d3_BuildFloorGeometry(int* a0);
void __cdecl d2_ChooseWappen(void);
void* __cdecl gm_StartFilteredEntitySearch(int, int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl d3_SnapCameraToEntity(int a0);
void __cdecl snd_PlayMarketAmbient(void);
void __cdecl tb_SetCallbackPaused(int a1, int a2);
int __cdecl main_RunFrameLoop(int a1, int a2);
void __cdecl lc_PlayerInJail(void);
void __cdecl d3_UpdateCameraController(void);
void* __cdecl evt_FindScriptById(int a1);
int __cdecl evt_RequestScriptExit(int a1);
void __cdecl gm_UpdateBuildingSmokeEffect(int a0);
void __cdecl d3_HandleCameraLevelKey(void);
void __cdecl d3_FocusCameraOnEntity(int a0);
void __cdecl d2_ShowBuildingMenu(void);
int __cdecl gm_GetEntityUiFlags(int a, int b, int c, int d);
int __cdecl gm_CheckEntityType(void* a0);
int __cdecl d2_DispatchTutorialEvent(int a, int b, int c, int d);
void __cdecl d2_EnterGebaeudeInterior(int a0);
int __cdecl gm_IsWarehouse(void* a0);
void __cdecl gm_RunGebaeudeVisit(int a, int b);
void __cdecl d2_HandleMarketSquareObjects(int a0);
void __cdecl snd_StopMarketAmbient(void);
void __cdecl d2_SetMouseTooltip(char* a);
void __cdecl d2_ShowStatusBanner(char* a);
void __cdecl sv_ResetSelectionState(void);
void __cdecl io_SetMouseCursorPos(int x, int y);

/* ADDRESS: GOLDTL 0x0059a340 */
/* ADDRESS: GOLDDE 0x0057f660 */
void __cdecl d2_RunWorldHudLoop(void)
{
	int v7;
	int savedRight;
	int savedBottom;
	int v5;
	int v6;
	int fx;
	int v10;
	int v11;
	int v8;
	int v9;
	int state;
	unsigned short v13;
	char* p;
	char* v12;
	char c;

	v7 = gm_GetSeason((char*) &gm_GameTime);
	g_677508 = -1;
	d3_ResetWorldSceneState();
	if (g_773ddc) {
		d3_BuildFloorGeometry((int*) d3_CurrentFloor);
		g_773ddc = 0;
	}
	savedRight = d2_MouseRightBoundary;
	savedBottom = d2_MouseBottomBoundary;
	v5 = g_6b5c80;
	v6 = d2_MouseTopBoundary;
	d3snd_AmbientEnabled = 1;
	gm_InWorldHud = 1;
	v13 = gm_LocalPlayerSlot;
	if (gm_ClientModeFlags & 4) {
		v12 = gm_EntitySlotTable + 2;
		do {
			if (*(unsigned short*) (v12 - 2) != 0xffff
				&& *(int*) (v12 + 0x52) == *(int*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot]) + 0x54)
				&& *(unsigned short*) (v12 - 2) != gm_LocalPlayerSlot
				&& (c = *v12, c == 6 || c == 7 || c == 5)
				&& *(unsigned int*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot]) + 0x4) < *(unsigned int*) (v12 + 2)) {
				d2_ChooseWappen();
				v13 = gm_LocalPlayerSlot;
				break;
			}
			v12 += 0x21c;
		} while ((int) v12 < (int) (gm_EntitySlotTable + 0x65402));
	}
	if ((gm_ClientModeFlags & 1) && g_774950 == 1) {
		v8 = (int) gm_StartFilteredEntitySearch(1, 4, v13);
		while (v8) {
			if (v8 != *(int*) (((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot]) + 0x170)) {
				d3_SnapCameraToEntity(v8);
				break;
			}
			v8 = (int) gm_FindNextFilteredEntity();
		}
	}
	snd_PlayMarketAmbient();
	state = 0;
	tb_SetCallbackPaused(0x538060, 0);
	v9 = main_RunFrameLoop(0x59a340, 0x67fff);
	while (v9) {
		g_774658 = g_774650;
		if (*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot].unk_198[0x19]) > 0)
			lc_PlayerInJail();
		d3_UpdateCameraController();

		if (state == 0) {
			fx = gm_GameTimeHour & 0xffff;
			if ((float) fx < *(float*) (v7 * 4 + 0x696540)
				|| *(float*) (v7 * 4 + 0x696550) <= (float) fx) {
				v8 = (int) gm_StartFilteredEntitySearch(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) != -1) {
						v9 = (int) evt_FindScriptById(*(int*) (v8 + 0x95));
						if (v9)
							evt_RequestScriptExit(v9);
						*(int*) (v8 + 0x95) = -1;
					}
					v8 = (int) gm_FindNextFilteredEntity();
				}
				state = 1;
			}
		} else if (state == 1) {
			fx = gm_GameTimeHour & 0xffff;
			if (*(float*) (v7 * 4 + 0x696540) <= (float) fx
				&& (float) fx < *(float*) (v7 * 4 + 0x696550)) {
				v8 = (int) gm_StartFilteredEntitySearch(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) == -1)
						gm_UpdateBuildingSmokeEffect(v8);
					v8 = (int) gm_FindNextFilteredEntity();
				}
				state = 2;
			}
		} else if (state == 2) {
			fx = gm_GameTimeHour & 0xffff;
			if ((float) fx < *(float*) (v7 * 4 + 0x696540)
				|| *(float*) (v7 * 4 + 0x696550) <= (float) fx) {
				v8 = (int) gm_StartFilteredEntitySearch(1, 6);
				while (v8) {
					if (*(int*) (v8 + 0x95) != -1) {
						v9 = (int) evt_FindScriptById(*(int*) (v8 + 0x95));
						if (v9)
							evt_RequestScriptExit(v9);
						*(int*) (v8 + 0x95) = -1;
					}
					v8 = (int) gm_FindNextFilteredEntity();
				}
				state = 3;
			}
		}
		d3_HandleCameraLevelKey();
		if (g_14ce8d4 && !g_14ce8e4 && sv_HoveredBuilding && !d3_ActiveCameraAnimation)
			d3_FocusCameraOnEntity(sv_HoveredBuilding);
		if (d2_DialogButtonAction != -1 && d2_CurrentElementId == g_6a25dc)
			d2_ShowBuildingMenu();
		if (d2_SelectedBuilding) {
			v10 = gm_GetEntityUiFlags(gm_LocalPlayerSlot, d2_SelectedBuilding, 0, 0);
			v9 = d2_SelectedBuilding;
			if (v9 && sv_HoveredBuilding == v9
				&& (g_14ce8dc
					|| (g_14ce8cc && d2_CursorStateId == 0xb))
				&& (v10 & 1)
				&& !(*(unsigned char*) (v9 + 0x5a) & 1)) {
				v11 = gm_CheckEntityType((void*) v9);
				if (v11 && d2_DispatchTutorialEvent(0x1b, v9, 0, 0) == 1)
					d2_EnterGebaeudeInterior(v9);
				else if (!gm_IsWarehouse((void*) v9)
					&& d2_DispatchTutorialEvent(0x19, v9, 0,
						*(unsigned short*) (v9 + 0x29)) == 1)
					gm_RunGebaeudeVisit(v9,
						*(unsigned short*) (v9 + 0x29));
			}
		}
		if (gm_MarketEntity)
			d2_HandleMarketSquareObjects(gm_MarketEntity);
		v9 = d2_EnteredBuildingEntity;
		if (d2_InsideBuildingActive) {
			if (d2_EnteredBuildingObjekt) {
				*(unsigned short*) (v9 + 0x29) =
					*(unsigned short*) d2_EnteredBuildingObjekt;
				if (!
					(*(unsigned char*) (v9 + 0x5a) & 1)) {
					if (*(int*) (v9 + 0x61)
						&& !gm_IsWarehouse((void*) v9))
						d3_SnapCameraToEntity(v9);
					if (gm_CheckEntityType((void*) v9)) {
						d2_EnterGebaeudeInterior(v9);
						goto label_59a83a;
					}
					if (!gm_IsWarehouse((void*) v9)) {
						gm_RunGebaeudeVisit(v9,
							*(unsigned short*) (v9 + 0x29));
						goto label_59a83a;
					}
					if (gm_IsWarehouse((void*) v9)) {
						d3_FocusCameraOnEntity(v9);
						goto label_59a834;
					}
					goto label_59a83a;
				}
			} else {
				d3_FocusCameraOnEntity(v9);
			}
label_59a834:
			d2_InsideBuildingActive = 0;
		}
label_59a83a:
		v9 = main_RunFrameLoop(0x59a340, 0x67fff);
	}
	d3snd_AmbientEnabled = 0;
	gm_InWorldHud = 0;
	snd_StopMarketAmbient();
	d2_SetMouseTooltip(str_empty);
	d2_ShowStatusBanner(str_empty);
	sv_ResetSelectionState();
	d2_CursorStateId = 0;
	d2_SuppressOverlay = 0;
	g_6772c4 = 1;
	io_SetMouseCursorPos(d2_MouseX, d2_MouseY);
	d2_MouseRightBoundary = savedRight;
	d2_MouseBottomBoundary = savedBottom;
	g_6b5c80 = v5;
	d2_MouseTopBoundary = v6;
	main_RunFrameLoop(0, 0x67fff);
}
