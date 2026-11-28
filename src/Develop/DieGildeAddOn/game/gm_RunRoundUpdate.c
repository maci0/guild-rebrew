void __cdecl main_RunGameLoop();
extern char g_85a0a4[];
__declspec(dllimport) void __stdcall Sleep(unsigned long);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl d3_DeinitUniverse();
int __cdecl d3_InitUniverse();
int __cdecl d3_SelectSceneContext();
int __cdecl d2_RenderAndPresentFrame();
int __cdecl d2_SetBackdropResource();
int __cdecl d2_AddElementToWindow();
int __cdecl d2_LoadForm();
int __cdecl d2_CenterForm();
int __cdecl d2_DestroyForm();
int __cdecl d2_GetWindowListItem();
int __cdecl d2_CreateGuiWindow();
int __cdecl d2_SetElementEnabled();
int __cdecl d2_SetForm();
int __cdecl d2_ClearSurface();
int __cdecl ai_RollNpcActionFlags();
int __cdecl gm_ReplenishOfficeCandidates();
int __cdecl hst_ShowDueHistoryScroll();
int __cdecl plt_UpdatePlantStages();
int __cdecl d3snd_QueueSound();
int __cdecl cm_RequestCopyEntityData();
int __cdecl cut_ResetEventSlots();
char __cdecl cut_RunPendingCutscenes(int);
int __cdecl srv_FormatStatEntity();
int __cdecl amt_UpdateAllOffices();
int __cdecl cm_PruneCompletedStraftaten();
int __cdecl gm_UpdateAllTitles();
int __cdecl gm_PushCityHistorySample();
int __cdecl gm_UpdateEconomyStats();
int __cdecl gm_GetDisasterState();
void __cdecl gm_InitDisasterState(int, int, int, float);
int __cdecl gm_UpdateDisasterState();
int __cdecl gm_UpdateBuildingSubsidies();
int __cdecl gm_CollectAllTaxes();
int __cdecl gm_AdvanceRoundCounters();
int __cdecl gm_UpdateActiveEntities();
int __cdecl gm_PackGameTime();
int __cdecl gm_UpdateAllTownSeasonPrices();
int __cdecl gm_FindNextFilteredEntity();
int __cdecl gm_StartFilteredEntitySearch();
int __cdecl init_AllocateGebaeudeSceneSlot();
int __cdecl io_AppendText();
int __cdecl fcn_00522c0();
int __cdecl d2_ShowModalMessageBox();
int __cdecl main_ExitToFrameHandler();
int __cdecl sv_WaitForNetworkSync();
int __cdecl main_RunFrameLoop();
int __cdecl gm_ApplyHourlyEntityUpdates();
int __cdecl gm_UpdateOwnerBuildings();
int __cdecl CheckGameDisc();
int __cdecl main_PlayOutroMovie();
int __cdecl he_DispatchFlaggedEvents();
int __cdecl he_TickEventDeals();
int __cdecl he_TickApEvents();
int __cdecl ai_SpawnRoundImmigrants();
int __cdecl he_RunDailyActionMaintenance();
int __cdecl fcn_005490d0();
int __cdecl io_FormatTextBuffer();
int __cdecl d2_CreateScrollPerga();
int __cdecl cm_StepCommandQueue();
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct ResetProto { unsigned char kind; unsigned char rest[0x24c]; } ResetProto;
extern int g_6a3420; extern int g_774954; extern char g_774965; extern int nt_ClientSocket; extern int d2_SuppressOverlay; extern double g_662cc0;
extern int g_1040480; extern int g_1040484; extern int g_1040488; extern int g_104048c; extern int d2_ScreenHeight; extern int g_1040494;
/* ADDRESS: GOLDTL 0x00543080 */
/* ADDRESS: GOLDDE 0x00529910 */
void __cdecl gm_RunRoundUpdate(void)
{
	int savedSpeed;
	int tmpVal;
	unsigned char* bldPtr;
	unsigned int* ptr;
	int tmpIdx;
	int loopStat;
	char messageText[256];
	char timeBuf[12];
	char* entPtr;
	Rec24_99f5a0 st;
	BUILDING_PROTOTYPE* proto;

	tmpIdx = -1;
	savedSpeed = *(unsigned char*) &d3snd_AmbientEnabled;
	gm_UpdateBuildingGridStats();
	loopStat = 0;
	do {
		srv_FormatStatEntity(&((ENTITY_RECORD*) gm_EntitySlotTable)[loopStat]);
		*(unsigned int*) &((ENTITY_RECORD*) gm_EntitySlotTable)[loopStat].unk_198[0x30] &= 0xe0874703;
		((ENTITY_RECORD*) gm_EntitySlotTable)[loopStat].entity_flags &= 0x3d31ffc7;
		if (((ENTITY_RECORD*) gm_EntitySlotTable)[loopStat].entity_state == 6) {
			tmpIdx = loopStat;
		}
		loopStat += 1;
	} while (loopStat < 768);
	*(short*) &gm_LocalPlayerSlot = (short) tmpIdx;
	he_DispatchFlaggedEvents();
	if (!(gm_ClientModeFlags & 4) && (unsigned short) gm_RandomMod(10) > 6) {
		loopStat = CheckGameDisc();
		while (loopStat != 1) {
			d2_SuppressOverlay = 0;
			*(int*) &main_LoopFlags = 0x24087;
			io_FormatTextBuffer(messageText, 0x79);
			if (!d2_ShowModalMessageBox(messageText, 1)) {
				g_774954 = 1;
				main_ExitToFrameHandler((int) main_RunGameLoop);
				return;
			}
			d2_RenderAndPresentFrame();
			Sleep(1000);
			loopStat = CheckGameDisc();
		}
	}
	*(int*) &main_LoopFlags = 0x24087;
	if (gm_ClientModeFlags & 4) {
		sv_WaitForNetworkSync(0x24087);
	}
	cut_ResetEventSlots(0);
	if (cut_RunPendingCutscenes(tmpIdx) && g_6a3420) {
		g_1040488 = 0;
		g_1040480 = g_1040494;
		g_1040484 = 0;
		g_104048c = d2_ScreenHeight;
		d2_ClearSurface(*(int*) &d2_ScreenSurface);
		d2_SetBackdropResource(0x79d);
	}
	he_TickEventDeals();
	he_TickApEvents();
	if (g_6a3420) {
		tmpVal = d2_LoadForm(0, 0, ((int) &g_6a3420 + 0xf8c));
		d2_CenterForm(tmpVal, 3);
		d2_SetForm(tmpVal, 1);
		io_AppendText(0x7d);
		gm_PackGameTime(((int) &d3_BuildingCategorySceneIndices + 0x1100), timeBuf);
		d2_SetForm(tmpVal, 0);
		d2_DestroyForm(tmpVal);
	}
	bldPtr = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	while (bldPtr) {
		proto = &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[*bldPtr];
		if (*bldPtr == 0x1e) {
			tmpIdx = init_AllocateGebaeudeSceneSlot(bldPtr);
			if (tmpIdx != -1) {
				tmpVal = d3_CurrentContextIndex;
				d3_SelectSceneContext((int) *(char*) (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*bldPtr].category + (unsigned long)&d3_BuildingCategorySceneIndices), 1);
				d3_InitUniverse(3);
				plt_UpdatePlantStages(*(unsigned int*) &bldPtr[0x71]);
				d3_DeinitUniverse(3);
				d3_SelectSceneContext(tmpVal, 1);
			}
		} else if (proto->category == 7) {
			*(int*)(bldPtr + 0x69) = 0;
		}
		bldPtr = (unsigned char*) gm_FindNextFilteredEntity();
	}
	tmpIdx = 0;
	gm_UpdateAllTownSeasonPrices();
	gm_PushCityHistorySample();
	if ((*(int*) &nt_NetSyncFlags & 8) || nt_ClientSocket == -1) {
		cm_PruneCompletedStraftaten();
		cm_StepCommandQueue();
		Sleep(100);
		entPtr = (char*) ((int) &gm_EntityIdField + 0x4);
		do {
			if (*(unsigned short*) &entPtr[-8] != 0xffff && *entPtr) {
				gm_UpdateOwnerBuildings(tmpIdx);
			}
			entPtr = &entPtr[0x21c];
			tmpIdx += 1;
		} while ((int) entPtr < ((int) &g_85a0a4 + 0x4));
		cm_StepCommandQueue();
		Sleep(100);
		gm_UpdateActiveEntities();
		cm_StepCommandQueue();
		Sleep(100);
		gm_RefreshEntityChainStats();
		cm_StepCommandQueue();
		Sleep(100);
		gm_AdvanceRoundCounters(3);
		gm_UpdateBuildingSubsidies();
		cm_StepCommandQueue();
		Sleep(100);
		gm_CollectAllTaxes();
		amt_UpdateAllOffices();
		cm_StepCommandQueue();
		Sleep(100);
		he_RunDailyActionMaintenance();
		fcn_005490d0();
		cm_StepCommandQueue();
		Sleep(100);
		gm_UpdateAllTitles();
		cm_StepCommandQueue();
		Sleep(100);
		ai_RollNpcActionFlags();
		cm_StepCommandQueue();
		Sleep(100);
		gm_UpdateEconomyStats();
		gm_GetDisasterState(&st);
		if (st.head == -1) {
			gm_InitDisasterState(1, 0x3f800000, 0x3f000000, (float)(10.0 - (double)(4 - gm_DifficultyLevel) * g_662cc0));
		} else {
			gm_UpdateDisasterState();
		}
		ai_SpawnRoundImmigrants();
		cm_StepCommandQueue();
		Sleep(100);
		ptr = (unsigned int*) &gm_EntityIdField;
		do {
			cm_RequestCopyEntityData(0xffffffff, *ptr, 0, 3);
			ptr = &ptr[0x87];
		} while ((int) ptr < (int) &g_85a0a4);
		cm_RequestCopyEntityData(0xffffffff, 0xffffffff, 0, 4);
		gm_ReplenishOfficeCandidates();
	} else {
		gm_AdvanceRoundCounters(2);
	}
	ptr = (unsigned int*) ((int) &gm_EntityIdField + 0x1e8);
	do {
		*ptr = 0;
		ptr = &ptr[0x87];
	} while ((int) ptr < ((int) &g_85a0a4 + 0x1e8));
	if (g_6a3420) {
		if (g_774965 && !(gm_ClientModeFlags & 4)) {
			tmpVal = d2_CreateScrollPerga();
			d2_SetForm(tmpVal, 2);
			io_AppendText(0x7d);
			d2_SetForm(tmpVal, 1);
			io_AppendText(0x1ba0, *(int*) &gm_LocalPlayerSlot & 0xffff, *(int*) &gm_LocalPlayerSlot & 0xffff);
			d3snd_QueueSound(0xfffffff9, 0, ((int) &g_6a3420 + 0xf6c), 0xffffffff, 0);
			tmpIdx = main_RunFrameLoop((int) gm_RunRoundUpdate, 0x66087);
			while (tmpIdx) {
				if (*(int*) &d2_DialogButtonAction == 2) {
					d2_DialogCloseRequested = 1;
				}
				tmpIdx = main_RunFrameLoop((int) gm_RunRoundUpdate, 0x66087);
			}
			d2_DestroyForm(tmpVal);
			main_PlayOutroMovie();
			g_774954 = 1;
		}
		if (g_6a3420 && !g_774954) {
			if (!(*(int*) &nt_NetSyncFlags & 8) && nt_ClientSocket != -1) {
				hst_ShowDueHistoryScroll(0);
			} else {
				hst_ShowDueHistoryScroll(1);
			}
		}
	}
	if ((*(int*) &nt_NetSyncFlags & 8) || nt_ClientSocket == -1) {
		gm_ApplyHourlyEntityUpdates();
	}
	*(char*) &d3snd_AmbientEnabled = (char) savedSpeed;
}
