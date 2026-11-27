#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include <string.h>

struct CUTSCENE_EVENT_SLOT {
	int id;
	char rest[0x110];
};

extern char cut_Cutscenes[];

void __cdecl fcn_004da170(void);
void __cdecl fcn_004dc5f0(void);
void __cdecl cut_HandleOfficeSessionEvent(void);
void __cdecl cut_HandleProzessEvent(void);
void __cdecl cut_SelectDuellResponse(void);
void __cdecl fcn_004e1900(void);
void __cdecl fcn_004e1950(void);
void __cdecl fcn_004e3de0(void);
void __cdecl cut_HandleAuctionEvent(void);
void __cdecl cut_MainDuell(char*);

/* ADDRESS: GOLDTL 0x004e7160 */
void __cdecl cut_RegisterEventCallbacks(int idx, EVENT_RUN runEvent, void* a3, void* a4, EVENT_CHECK checkEvent, unsigned char a6)
{
	int o;

	o = idx * 20;
	*(EVENT_RUN*) (g_9b0840 + o) = runEvent;
	*(void**) (g_9b0840 + 4 + o) = a3;
	*(void**) (g_9b0840 + 8 + o) = a4;
	*(EVENT_CHECK*) (g_9b0840 + 0x10 + o) = checkEvent;
	*(unsigned char*) (g_9b0840 + 0xc + o) = a6;
}

/* ADDRESS: GOLDTL 0x004e71a0 */
void __cdecl cut_InitCutsceneRegistry(void)
{
	int i;

	memset(((struct CUTSCENE_EVENT_SLOT*)cut_Cutscenes), 0, sizeof(struct CUTSCENE_EVENT_SLOT[96]));
	for (i = 0; i < 96; i++)
		((struct CUTSCENE_EVENT_SLOT*)cut_Cutscenes)[i].id = -1;
	cut_RegisterEventCallbacks(0, cut_RunTobyCutscene, (void*) fcn_004e1950, 0, 0, 0);
	cut_RegisterEventCallbacks(1, cut_RunOfficeSessions, (void*) fcn_004dc5f0, (void*) cut_HandleOfficeSessionEvent, 0, 0);
	cut_RegisterEventCallbacks(2, cut_RunProzess, (void*) cut_PromptProzessChoice, (void*) cut_HandleProzessEvent, cut_NotifyProzess, 0);
	cut_RegisterEventCallbacks(3, cut_RunCombatCutscene, (void*) fcn_004da170, 0, cut_NotifyCombatCutscene, 1);
	cut_RegisterEventCallbacks(4, cut_MainDuell, (void*) fcn_004e1900, (void*) cut_SelectDuellResponse, cut_NotifyDuell, 0);
	cut_RegisterEventCallbacks(5, cut_PlayHinrichtung, 0, 0, cut_NotifyHinrichtung, 0);
	cut_RegisterEventCallbacks(6, fcn_004e2090, 0, 0, gm_NotifyHochzeit, 0);
	cut_RegisterEventCallbacks(7, cut_PlayBirthCutscene, 0, 0, gm_NotifyGeburt, 0);
	cut_RegisterEventCallbacks(8, cut_PlayDeathCutscene, 0, 0, cut_CheckDeathCutscene, 0);
	cut_RegisterEventCallbacks(9, cut_RunPleiteCutscene, 0, 0, 0, 0);
	cut_RegisterEventCallbacks(10, cut_RunAuction, (void*) fcn_004e3de0, (void*) cut_HandleAuctionEvent, cut_BroadcastCutsceneNotice, 1);
	cut_RegisterEventCallbacks(11, fcn_004e4180, 0, 0, 0, 0);
	cut_ResetEventSlots(0);
}
