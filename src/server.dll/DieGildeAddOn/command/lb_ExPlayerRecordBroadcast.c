/* lb_ExPlayerRecordBroadcast.  Split out of lobbycommands.c: the reference interleaves
 * lb_ExPlayerHasJoined / lb_BroadcastStateChange / lb_HandleEntitySync /
 * cm_RouteCommand between these functions, so one object cannot be
 * position-aligned.  Body unchanged.
 */

#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

/* Lobby command 4 -- distribute one player's record to the other clients.
 *
 * Named from evidence, not inferred.  The dispatcher lb_ExLobbyServerCommand
 * (0x10014db0) is a 7-way switch on `*(int*)(msg + 0x10)` and this function is
 * its `case 4`; the sibling cases are lb_ExPlayerlist (0), lb_SendLobbyConfig
 * (1), lb_ExPlayerHasJoined (2), lb_BroadcastStateChange (3),
 * lb_HandleEntitySync (5) and cm_RouteCommand (6).  The reference's own log
 * call at this site pushes 0x1002d740, the string "invalid client state", for
 * the guard below -- so the *validation* half is attested.  The __FILE__ string
 * it passes alongside (0x1002d70c) is
 * "D:\Develop\DieGildeAddOn\command\lobbycommands.c", which confirms the module
 * and therefore the lb_ prefix.
 *
 * The broadcast half is read from the body and is not separately attested: the
 * second loop walks every player slot from 0x101deb00 to 0x114ffe20 in
 * 0x264264 strides and calls cm_QueuePlayerCommand on each surviving
 * connection.  Distinct from case 3's lb_BroadcastStateChange, hence its own
 * name rather than a second caser. */
// FUNCTION: SERVER 0x10014af0
int __cdecl lb_ExPlayerRecordBroadcast(unsigned int* player, unsigned char* msg)
{
	int result;
	unsigned char* conn;
	unsigned char* rec;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal((char*) 0x1002d70c, 0x31d, (char*) 0x1002d740, 1);
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	rec = msg + 0x14;
	if (*(int*) (player + 1) != *(int*) rec) {
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	for (conn = (unsigned char*) 0x101deb00; (int) conn < 0x114ffe20;
	     conn += 0x264264) {
		if ((*(unsigned int*) conn & 1) == 0) continue;
		if ((*(unsigned int*) conn & 0x200) == 0) continue;
		if (conn == (unsigned char*) player) continue;
		if (*(int*) (conn + 0x264218) == *(int*) (rec + 0xc)) {
			*(int*) (rec + 0xc) = *(int*) ((char*) player + 0x264218);
			break;
		}
	}
	*(int*) (rec + 4) = *(int*) ((char*) player + 0x264210);
	memcpy((char*) player + 0x26420c, rec, 0x57);
	for (conn = (unsigned char*) 0x101deb00; (int) conn < 0x114ffe20;
	     conn += 0x264264) {
		if ((*(unsigned int*) conn & 1) == 0) continue;
		if ((*(unsigned int*) conn & 0x200) == 0) continue;
		result = cm_QueuePlayerCommand((unsigned int*) conn, msg);
		if (result == -1) return -1;
	}
	return 0;
}
