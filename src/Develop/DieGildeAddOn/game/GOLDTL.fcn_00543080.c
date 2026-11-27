__declspec(dllimport) void __stdcall Sleep(unsigned long);
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl fcn_0043a9c0();
int __cdecl fcn_0043aa30();
int __cdecl d3_SelectSceneContext();
int __cdecl fcn_0046ac30();
int __cdecl fcn_00469e30();
int __cdecl d2_AddElementToWindow();
int __cdecl fcn_00470820();
int __cdecl fcn_00471d80();
int __cdecl d2_DestroyForm();
int __cdecl d2_GetWindowListItem();
int __cdecl fcn_00472380();
int __cdecl fcn_00472640();
int __cdecl d2_SetForm();
int __cdecl fcn_00476970();
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
int __cdecl fcn_004f5830();
int __cdecl gm_UpdateAllBuildingLevels();
int __cdecl fcn_004facb0();
int __cdecl fcn_004fb390();
int __cdecl gm_GetDisasterState();
void __cdecl gm_InitDisasterState(int, int, int, float);
int __cdecl gm_UpdateDisasterState();
int __cdecl fcn_004fcc20();
int __cdecl gm_CollectAllTaxes();
int __cdecl gm_AdvanceRoundCounters();
int __cdecl gm_UpdateActiveEntities();
int __cdecl gm_PackGameTime();
int __cdecl fcn_005016c0();
int __cdecl gm_FindNextFilteredEntity();
int __cdecl gm_StartFilteredEntitySearch();
int __cdecl init_AllocateGebaeudeSceneSlot();
int __cdecl io_AppendText();
int __cdecl fcn_00522c0();
int __cdecl fcn_00526120();
int __cdecl main_ExitToFrameHandler();
int __cdecl sv_WaitForNetworkSync();
int __cdecl main_RunFrameLoop();
int __cdecl gm_ApplyHourlyEntityUpdates();
int __cdecl gm_UpdateOwnerBuildings();
int __cdecl fcn_005435d0();
int __cdecl main_PlayOutroMovie();
int __cdecl he_DispatchFlaggedEvents();
int __cdecl fcn_0053f100();
int __cdecl fcn_00546f80();
int __cdecl fcn_00547770();
int __cdecl he_RunDailyActionMaintenance();
int __cdecl fcn_005490d0();
int __cdecl io_FormatTextBuffer();
int __cdecl d2_CreateScrollPerga();
int __cdecl cm_StepCommandQueue();
int __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
typedef struct ResetProto { unsigned char kind; unsigned char rest[0x24c]; } ResetProto;
extern int g_6a3420; extern int g_774954; extern char g_774965; extern int g_14cbca0; extern int d2_SuppressOverlay; extern double g_662cc0;
extern int g_1040480; extern int g_1040484; extern int g_1040488; extern int g_104048c; extern int d2_ScreenHeight; extern int g_1040494;
/* ADDRESS: GOLDTL 0x00543080 */
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
	savedSpeed = *(unsigned char*) &g_772d10;
	gm_UpdateBuildingGridStats();
	loopStat = 0;
	do {
		srv_FormatStatEntity(&((ENTITY_RECORD*) g_7f4ca0)[loopStat]);
		*(unsigned int*) &((ENTITY_RECORD*) g_7f4ca0)[loopStat].unk_198[0x30] &= 0xe0874703;
		((ENTITY_RECORD*) g_7f4ca0)[loopStat].entity_flags &= 0x3d31ffc7;
		if (((ENTITY_RECORD*) g_7f4ca0)[loopStat].entity_state == 6) {
			tmpIdx = loopStat;
		}
		loopStat += 1;
	} while (loopStat < 768);
	*(short*) &g_774970 = (short) tmpIdx;
	he_DispatchFlaggedEvents();
	if (!(g_7747b0 & 4) && (unsigned short) gm_RandomMod(10) > 6) {
		loopStat = fcn_005435d0();
		while (loopStat != 1) {
			d2_SuppressOverlay = 0;
			*(int*) &main_LoopFlags = 0x24087;
			io_FormatTextBuffer(messageText, 0x79);
			if (!fcn_00526120(messageText, 1)) {
				g_774954 = 1;
				main_ExitToFrameHandler(0x5438c0);
				return;
			}
			fcn_0046ac30();
			Sleep(1000);
			loopStat = fcn_005435d0();
		}
	}
	*(int*) &main_LoopFlags = 0x24087;
	if (g_7747b0 & 4) {
		sv_WaitForNetworkSync(0x24087);
	}
	cut_ResetEventSlots(0);
	if (cut_RunPendingCutscenes(tmpIdx) && g_6a3420) {
		g_1040488 = 0;
		g_1040480 = g_1040494;
		g_1040484 = 0;
		g_104048c = d2_ScreenHeight;
		fcn_00476970(*(int*) &g_77250c);
		fcn_00469e30(0x79d);
	}
	fcn_0053f100();
	fcn_00546f80();
	if (g_6a3420) {
		tmpVal = fcn_00470820(0, 0, 0x6a43ac);
		fcn_00471d80(tmpVal, 3);
		d2_SetForm(tmpVal, 1);
		io_AppendText(0x7d);
		gm_PackGameTime(0x7f4c00, timeBuf);
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
				d3_SelectSceneContext((int) *(char*) (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*bldPtr].category + (unsigned long)&g_7f3b00), 1);
				fcn_0043aa30(3);
				plt_UpdatePlantStages(*(unsigned int*) &bldPtr[0x71]);
				fcn_0043a9c0(3);
				d3_SelectSceneContext(tmpVal, 1);
			}
		} else if (proto->category == 7) {
			*(int*)(bldPtr + 0x69) = 0;
		}
		bldPtr = (unsigned char*) gm_FindNextFilteredEntity();
	}
	tmpIdx = 0;
	fcn_005016c0();
	fcn_004facb0();
	if ((*(int*) &g_77494c & 8) || g_14cbca0 == -1) {
		fcn_004f5830();
		cm_StepCommandQueue();
		Sleep(100);
		entPtr = (char*) 0x7f4ca8;
		do {
			if (*(unsigned short*) &entPtr[-8] != 0xffff && *entPtr) {
				gm_UpdateOwnerBuildings(tmpIdx);
			}
			entPtr = &entPtr[0x21c];
			tmpIdx += 1;
		} while ((int) entPtr < 0x85a0a8);
		cm_StepCommandQueue();
		Sleep(100);
		gm_UpdateActiveEntities();
		cm_StepCommandQueue();
		Sleep(100);
		fcn_004fd0a0();
		cm_StepCommandQueue();
		Sleep(100);
		gm_AdvanceRoundCounters(3);
		fcn_004fcc20();
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
		gm_UpdateAllBuildingLevels();
		cm_StepCommandQueue();
		Sleep(100);
		ai_RollNpcActionFlags();
		cm_StepCommandQueue();
		Sleep(100);
		fcn_004fb390();
		gm_GetDisasterState(&st);
		if (st.head == -1) {
			gm_InitDisasterState(1, 0x3f800000, 0x3f000000, (float)(10.0 - (double)(4 - g_7747b4) * g_662cc0));
		} else {
			gm_UpdateDisasterState();
		}
		fcn_00547770();
		cm_StepCommandQueue();
		Sleep(100);
		ptr = (unsigned int*) &g_7f4ca4;
		do {
			cm_RequestCopyEntityData(0xffffffff, *ptr, 0, 3);
			ptr = &ptr[0x87];
		} while ((int) ptr < 0x85a0a4);
		cm_RequestCopyEntityData(0xffffffff, 0xffffffff, 0, 4);
		gm_ReplenishOfficeCandidates();
	} else {
		gm_AdvanceRoundCounters(2);
	}
	ptr = (unsigned int*) 0x7f4e8c;
	do {
		*ptr = 0;
		ptr = &ptr[0x87];
	} while ((int) ptr < 0x85a28c);
	if (g_6a3420) {
		if (g_774965 && !(g_7747b0 & 4)) {
			tmpVal = d2_CreateScrollPerga();
			d2_SetForm(tmpVal, 2);
			io_AppendText(0x7d);
			d2_SetForm(tmpVal, 1);
			io_AppendText(0x1ba0, *(int*) &g_774970 & 0xffff, *(int*) &g_774970 & 0xffff);
			d3snd_QueueSound(0xfffffff9, 0, 0x6a438c, 0xffffffff, 0);
			tmpIdx = main_RunFrameLoop(0x543080, 0x66087);
			while (tmpIdx) {
				if (*(int*) &g_100f1dc == 2) {
					g_774654 = 1;
				}
				tmpIdx = main_RunFrameLoop(0x543080, 0x66087);
			}
			d2_DestroyForm(tmpVal);
			main_PlayOutroMovie();
			g_774954 = 1;
		}
		if (g_6a3420 && !g_774954) {
			if (!(*(int*) &g_77494c & 8) && g_14cbca0 != -1) {
				hst_ShowDueHistoryScroll(0);
			} else {
				hst_ShowDueHistoryScroll(1);
			}
		}
	}
	if ((*(int*) &g_77494c & 8) || g_14cbca0 == -1) {
		gm_ApplyHourlyEntityUpdates();
	}
	*(char*) &g_772d10 = (char) savedSpeed;
}
