#ifndef EVENT_CALLBACKS_H
#define EVENT_CALLBACKS_H

/* Inferred validator contract and declaration home; the event remains a byte view. */
typedef int (__cdecl* EVENT_CHECK)(char* event);
typedef void (__cdecl* EVENT_RUN)(char* event);

/* First-slot call contract is reconstructed; second/third phase contracts remain open. */
void __cdecl cut_RegisterEventCallbacks(int kind, EVENT_RUN first, void* second, void* third,
    EVENT_CHECK check, unsigned char flag);

void __cdecl cut_RunTobyCutscene(char* event);
void __cdecl cut_RunOfficeSessions(char* event);
void __cdecl cut_RunProzess(char* event);
void __cdecl cut_RunCombatCutscene(char* event);
void __cdecl cut_MainDuell(char* event);
void __cdecl cut_PlayHinrichtung(char* event);
void __cdecl fcn_004e2090(char* event);
void __cdecl cut_PlayBirthCutscene(char* event);
void __cdecl cut_PlayDeathCutscene(char* event);
void __cdecl cut_RunPleiteCutscene(char* event);
void __cdecl cut_RunAuction(char* event);
void __cdecl fcn_004e4180(char* event);

/* Reconstructed court decision callback; other phase-slot contracts remain open. */
void __cdecl cut_PromptProzessChoice(char* participant, int* action);

/* Existing event helpers use word and unsigned-byte access views. */
void __cdecl cut_ExecuteCutscene(int* event);
void __cdecl cut_ResetEventSlots(int* event);
int __cdecl cut_CutsceneReady(int* event);
int __cdecl cut_IsParticipant(int participant, unsigned char* event);
int __cdecl cut_CheckMaster(int* event);

int __cdecl fcn_004dc7d0(char* event);
int __cdecl cut_NotifyCombatCutscene(char* event);
int __cdecl fcn_004e1330(char* event);
int __cdecl cut_NotifyHinrichtung(char* event);
int __cdecl gm_NotifyHochzeit(char* event);
int __cdecl gm_NotifyGeburt(char* event);
int __cdecl cut_CheckDeathCutscene(char* event);
int __cdecl cut_BroadcastCutsceneNotice(char* event);

/* Declaration only: complete allocation extent and storage owner remain unresolved. */
/* ADDRESS: GOLDTL 0x009b0840 */
/* ADDRESS: GOLD 0x0092c500 */
extern char g_9b0840[];

#endif
