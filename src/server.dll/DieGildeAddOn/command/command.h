#ifndef COMMAND_H
#define COMMAND_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Common command module declarations */
extern int __cdecl QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl ClosePlayerConnection(char* player_ptr);

/* Search and lookup */
extern char* __cdecl lb_SearchRecordTable(int record_id);

/* Lobby commands (lobbycommands.c) */
extern int __cdecl lb_ExPlayerlist(unsigned int* param_1, unsigned char* param_2);
extern int __cdecl SendLobbyConfig(unsigned int* param_1, unsigned char* param_2);
extern int __cdecl HandleLobbyCommands(char* player, char* msg);
extern int __cdecl lb_ExLobbyServerCommand(unsigned int* param_1, int param_2);

/* Validation functions (command.c) */
extern int __cdecl cm_ChkMoveCredits(void* param_1, void* param_2);
extern int __cdecl cm_ChkSellObjekt(void* param_1, void* param_2);
extern int __cdecl cm_ChkChangeAttribute(void* param_1, void* param_2);
extern int __cdecl cm_ChkChangeBits(void* param_1, void* param_2);
extern int __cdecl cm_ChkSetGebBesitzer(void* param_1, void* param_2);
extern int __cdecl cm_ChkCutsceneReady(void* param_1, void* param_2);

/* Execution functions (command.c) */
extern int __cdecl cm_ExecCommand(void* param_1, void* param_2);
extern int __cdecl cm_ExAllocRaum(void* param_1, void* param_2);
extern int __cdecl cm_ExAllocObjekt(void* param_1, void* param_2);
extern int __cdecl cm_ExAllocSpieler(void* param_1, void* param_2);
extern int __cdecl cm_ExChangePlayerIdentity(void* param_1, void* param_2);
extern int __cdecl cm_ExFree(void* param_1, void* param_2);
extern int __cdecl cm_ExSellObjekt(void* param_1, void* param_2);
extern int __cdecl cm_ExProdObjekt(void* param_1, void* param_2);
extern int __cdecl cm_ExMoveObjekt(void* param_1, void* param_2);
extern int __cdecl cm_ExClearLagerslot(void* param_1, void* param_2);
extern int __cdecl cm_ExChangeAttribute(void* param_1, void* param_2);
extern int __cdecl cm_ExSetAttribute(void* param_1, void* param_2);
extern int __cdecl cm_ExChangeDesire(void* param_1, void* param_2);
extern int __cdecl cm_ExChangeBits(void* param_1, void* param_2);
extern int __cdecl cm_ExChangeFloat(void* param_1, void* param_2);
extern int __cdecl cm_ExKillSpieler(void* param_1, void* param_2);
extern int __cdecl cm_ExAllocThemaPredigt(void* param_1, void* param_2);
extern int __cdecl cm_ExSetGebBesitzer(void* param_1, void* param_2);
extern int __cdecl cm_ExSetWohnsitz(void* param_1, void* param_2);
extern int __cdecl cm_ExSetGebUpgrade(void* param_1, void* param_2);
extern int __cdecl cm_ExEmployWorker(void* param_1, void* param_2);
extern int __cdecl cm_ExAllocCharacter(void* param_1, void* param_2);
extern int __cdecl cm_ExKillTransporter(void* param_1, void* param_2);
extern int __cdecl cm_ExCreateGeb(void* param_1, void* param_2);

#endif /* COMMAND_H */
