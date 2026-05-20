#ifndef COMMAND_H
#define COMMAND_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Common command module declarations */
extern int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl cm_ClosePlayerConnection(char* player_ptr);

/* Search and lookup */
extern char* __cdecl lb_SearchRecordTable(int record_id);

/* Lobby commands (lobbycommands.c) */
extern int __cdecl lb_ExPlayerlist(unsigned int* cmd, unsigned char* result);
extern int __cdecl lb_SendLobbyConfig(unsigned int* cmd, unsigned char* result);
extern int __cdecl lb_HandleLobbyCommands(char* player, char* msg);
extern int __cdecl lb_ExLobbyServerCommand(unsigned int* cmd, int result);

/* Validation functions (command.c) */
extern int __cdecl cm_ChkMoveCredits(void* cmd, void* result);
extern int __cdecl cm_ChkSellObjekt(void* cmd, void* result);
extern int __cdecl cm_ChkChangeAttribute(void* cmd, void* result);
extern int __cdecl cm_ChkChangeBits(void* cmd, void* result);
extern int __cdecl cm_ChkSetGebBesitzer(void* cmd, void* result);
extern int __cdecl cm_ChkCutsceneReady(void* cmd, void* result);

/* Execution functions (command.c) */
extern int __cdecl cm_ExecCommand(void* cmd, void* result);
extern int __cdecl cm_ExAllocRaum(void* cmd, void* result);
extern int __cdecl cm_ExAllocObjekt(void* cmd, void* result);
extern int __cdecl cm_ExAllocSpieler(void* cmd, void* result);
extern int __cdecl cm_ExChangePlayerIdentity(void* cmd, void* result);
extern int __cdecl cm_ExFree(void* cmd, void* result);
extern int __cdecl cm_ExSellObjekt(void* cmd, void* result);
extern int __cdecl cm_ExProdObjekt(void* cmd, void* result);
extern int __cdecl cm_ExMoveObjekt(void* cmd, void* result);
extern int __cdecl cm_ExClearLagerslot(void* cmd, void* result);
extern int __cdecl cm_ExChangeAttribute(void* cmd, void* result);
extern int __cdecl cm_ExSetAttribute(void* cmd, void* result);
extern int __cdecl cm_ExChangeDesire(void* cmd, void* result);
extern int __cdecl cm_ExChangeBits(void* cmd, void* result);
extern int __cdecl cm_ExChangeFloat(void* cmd, void* result);
extern int __cdecl cm_ExKillSpieler(void* cmd, void* result);
extern int __cdecl cm_ExAllocThemaPredigt(void* cmd, void* result);
extern int __cdecl cm_ExSetGebBesitzer(void* cmd, void* result);
extern int __cdecl cm_ExSetWohnsitz(void* cmd, void* result);
extern int __cdecl cm_ExSetGebUpgrade(void* cmd, void* result);
extern int __cdecl cm_ExEmployWorker(void* cmd, void* result);
extern int __cdecl cm_ExAllocCharacter(void* cmd, void* result);
extern int __cdecl cm_ExKillTransporter(void* cmd, void* result);
extern int __cdecl cm_ExCreateGeb(void* cmd, void* result);

#endif /* COMMAND_H */
