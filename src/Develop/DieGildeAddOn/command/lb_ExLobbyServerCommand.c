/* lb_ExLobbyServerCommand.  Split out of lobbycommands.c: the reference interleaves
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
// FUNCTION: SERVER 0x10014db0
// lb_ExLobbyServerCommand
int __cdecl lb_ExPlayerHasJoined(unsigned int*, unsigned char*);
int __cdecl lb_BroadcastStateChange(unsigned int*, unsigned char*);
int __cdecl lb_ExPlayerRecordBroadcast(unsigned int*, unsigned char*);
int __cdecl lb_HandleEntitySync(unsigned int*, unsigned char*);
int __cdecl cm_RouteCommand(unsigned int*, unsigned char*);

int __cdecl lb_ExLobbyServerCommand(unsigned int* player, unsigned char* msg)
{
	char buf[0x80];

	sprintf(buf, "lb_ExLobbyServerCommand: %i", *(unsigned char*) (msg + 0x10));
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x3a5, buf, 1);
	switch (*(int*) (msg + 0x10)) {
	case 0:
		return lb_ExPlayerlist(player, msg);
	case 1:
		return lb_SendLobbyConfig(player, msg);
	case 2:
		return lb_ExPlayerHasJoined(player, msg);
	case 3:
		return lb_BroadcastStateChange(player, msg);
	case 4:
		return lb_ExPlayerRecordBroadcast(player, msg);
	case 5:
		return lb_HandleEntitySync(player, msg);
	case 6:
		return cm_RouteCommand(player, msg);
	}
	return 1;
}
