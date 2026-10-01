extern unsigned char g_connections[9 * 0x264264];
/* lb_ExPlayerlist / lb_SendLobbyConfig.  Split out of lobbycommands.c: the reference interleaves
 * lb_ExPlayerHasJoined / lb_BroadcastStateChange / lb_HandleEntitySync /
 * cm_RouteCommand between these functions, so one object cannot be
 * position-aligned.  Body unchanged.
 */

#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

/* Lobby handler: sends the current player list to a client.
 * Iterates player slots and writes connection info into the
 * response packet. */
// FUNCTION: SERVER 0x100145e0
// lb_ExPlayerlist
// SIZE 0x24
typedef struct { int count; int ids[8]; } PlayerList9;

int __cdecl lb_ExPlayerlist(unsigned int* player, unsigned char* msg)
{
	PlayerList9 list;
	unsigned int* conn;
	int result;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x244, "invalid client state", 1);
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	memset(&list, 0, sizeof(list));
	list.count = 0;
	for (conn = (unsigned int*) (int) g_connections; (int) conn < (int) (g_connections + 0x1321320); conn = (unsigned int*) ((char*) conn + 0x264264)) {
		if ((*conn & 1) == 0) continue;
		if ((*conn & 0x200) == 0) continue;
		list.ids[list.count] = conn[1];
		list.count++;
	}
	memcpy((char*) msg + 0x14, &list, sizeof(list));
	result = cm_QueuePlayerCommand(player, msg);
	if (result == -1) return -1;
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x258, "Got lb_ExPlayerlist", 1);
	return 0;
}


/* Lobby handler: sends the lobby configuration (map, rules,
 * game settings) to a requesting client. */

// FUNCTION: SERVER 0x100146c0
// lb_SendLobbyConfig
int __cdecl lb_SendLobbyConfig(unsigned int* player, unsigned char* msg)
{
	int value;
	int result;
	unsigned char* conn;
	unsigned char* rec;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x264, "invalid client state", 1);
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	if (*(int *) ((char *) player + 4) != *(int *) (msg + 0x14)) {
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	if ((unsigned int) *(int *) (msg + 0x18) > 1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x279, "invalid client data", 1);
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	value = *(int *) (msg + 0x18);
	*(int *) ((char *) player + 0x264210) = value;
	if (value != 0) {
		*player |= 0x800;
	} else {
		*player &= ~0x800;
	}
	for (conn = (unsigned char*) (int) g_connections; (int) conn < (int) (g_connections + 0x1321320); conn += 0x264264) {
		if ((*(unsigned int *) conn & 1) == 0) continue;
		if ((*(unsigned int *) conn & 0x200) == 0) continue;
		result = cm_QueuePlayerCommand((unsigned int*) conn, msg);
		if (result == -1) return -1;
	}
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x28c, "Got lb_ExPlayerReadyStatus", 1);
	return 0;
}
