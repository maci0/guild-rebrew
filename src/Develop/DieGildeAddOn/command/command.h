#ifndef COMMAND_H
#define COMMAND_H

#include "../../game_common.h"
#include "../../game_structs.h"

/* Common command module declarations */
extern int __cdecl srv_PutConnSCommand(unsigned int* player, unsigned char* data);
extern void __cdecl cm_ClosePlayerConnection(char* player_ptr);

/* Lobby commands (lobbycommands.c) */
extern int __cdecl lb_ExPlayerlist(unsigned int* cmd, unsigned char* result);
extern int __cdecl lb_ExPlayerReadyStatus(unsigned int* cmd, unsigned char* result);
extern int __cdecl lb_ExLobbyServerCommand(unsigned int* cmd, int result);
extern int __cdecl lb_ExPlayerRecordBroadcast(unsigned int* player, unsigned char* msg);

#endif /* COMMAND_H */
