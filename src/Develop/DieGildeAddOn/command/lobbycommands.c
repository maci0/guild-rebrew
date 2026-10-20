extern unsigned char g_connections[0x264264];
#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"
extern int __cdecl srv_PutConnSCommand(unsigned int* player, unsigned char* data);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);

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
		result = srv_PutConnSCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	memset(&list, 0, sizeof(list));
	list.count = 0;
	for (conn = (unsigned int*) g_connections; (int) conn < (int) g_connections + 0x1321320; conn = (unsigned int*) ((char*) conn + 0x264264)) {
		if ((*conn & 1) == 0) continue;
		if ((*conn & 0x200) == 0) continue;
		list.ids[list.count] = conn[1];
		list.count++;
	}
	memcpy((char*) msg + 0x14, &list, sizeof(list));
	result = srv_PutConnSCommand(player, msg);
	if (result == -1) return -1;
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x258, "Got lb_ExPlayerlist", 1);
	return 0;
}


/* Lobby handler: sends the lobby configuration (map, rules,
 * game settings) to a requesting client. */

int __cdecl lb_ExPlayerReadyStatus(unsigned int* player, unsigned char* msg)
{
	int value;
	int result;
	unsigned char* conn;
	unsigned char* rec;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x264, "invalid client state", 1);
		*msg = 2;
		result = srv_PutConnSCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	if (*(int *) ((char *) player + 4) != *(int *) (msg + 0x14)) {
		*msg = 2;
		result = srv_PutConnSCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	if ((unsigned int) *(int *) (msg + 0x18) > 1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x279, "invalid client data", 1);
		*msg = 2;
		result = srv_PutConnSCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	value = *(int *) (msg + 0x18);
	*(int *) ((char *) player + 0x264210) = value;
	if (value != 0) {
		*player |= 0x800;
	} else {
		*player &= ~0x800;
	}
	for (conn = (unsigned char*) g_connections; (int) conn < (int) g_connections + 0x1321320; conn += 0x264264) {
		if ((*(unsigned int *) conn & 1) == 0) continue;
		if ((*(unsigned int *) conn & 0x200) == 0) continue;
		result = srv_PutConnSCommand((unsigned int*) conn, msg);
		if (result == -1) return -1;
	}
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x28c, "Got lb_ExPlayerReadyStatus", 1);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

extern int g_max_players;

/* Lobby handler: sends the current player list to a client.
 * Iterates player slots and writes connection info into the
 * response packet. */

int __cdecl lb_ExPlayerHasJoined(char* player, char* msg)
{
	PlayerSlot* slot;
	PlayerSlot* slot2;
	unsigned int flags;
	int count;
	int* slot_cursor;
	int arr[8];
	char buf[0x100];
	char* m14;

	flags = *(unsigned int*) player;
	if ((flags & 0x4000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x29a, "invalid client state", 1);
		msg[0] = 2;
		return srv_PutConnSCommand((unsigned int*) player, (unsigned char*) msg) == -1 ? -1 : 0;
	} else if ((flags & 0x2000) == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2a4, "invalid client state", 1);
		msg[0] = 2;
		return srv_PutConnSCommand((unsigned int*) player, (unsigned char*) msg) == -1 ? -1 : 0;
	} else {
		goto join;
	}

join:
	count = 0;
	for (slot = (PlayerSlot*) g_connections;
	     (int) slot < (int) g_connections + 0x1321320;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200) && !(flags & 0x2000)) {
			count++;
		}
	}
	if (count >= g_max_players) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2b1, "Game is full", 1);
		msg[0] = 2;
		if (srv_PutConnSCommand((unsigned int*) player, (unsigned char*) msg) == -1) {
			return -1;
		}
		cm_ClosePlayerConnection((unsigned int*) player);
		return 0;
	}

	m14 = msg + 0x14;
	slot = (PlayerSlot*) g_connections;
	*(unsigned int*) (m14 + 4) = 0;
	for (; (int) slot < (int) g_connections + 0x1321320;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200) && (char*) slot != player &&
		    *(int*) ((char*) slot + 0x264218) == *(int*) (m14 + 0xc)) {
			arr[0] = 0; arr[1] = 0; arr[2] = 0; arr[3] = 0;
			arr[4] = 0; arr[5] = 0; arr[6] = 0; arr[7] = 0;
			for (slot_cursor = arr, slot2 = (PlayerSlot*) g_connections;
			     (int) slot2 < (int) g_connections + 0x1321320;
			     slot2 = (PlayerSlot*) ((char*) slot2 + 0x264264), slot_cursor++) {
				flags = slot2->flags;
				if ((flags & 1) && (flags & 0x200) && (char*) slot2 != player) {
					if (*(int*) ((char*) slot2 + 0x264218) >= 0 &&
					    *(int*) ((char*) slot2 + 0x264218) < 8) {
						*slot_cursor = 1;
					}
				}
			}
			count = 0;
			while (count < 8) {
				if (arr[count] == 0) {
					*(unsigned int*) (m14 + 0xc) = count;
					break;
				}
				count++;
			}
			break;
		}
	}

	sprintf(buf, "lb_ExPlayerHasJoined: before <<memcpy>>: %i", *(unsigned int*) player);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2dd, buf, 1);
	memcpy((char*) player + 0x26420c, m14, 87);
	sprintf(buf, "lb_ExPlayerHasJoined: after <<memcpy>>: %i", *(unsigned int*) player);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2e2, buf, 1);
	*(unsigned int*) player &= ~0x2000;
	sprintf(buf, "lb_ExPlayerHasJoined: before <<srv_PutConnSCommand>>: %i", *(unsigned int*) player);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2e7, buf, 1);

	for (slot = (PlayerSlot*) g_connections;
	     (int) slot < (int) g_connections + 0x1321320;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200)) {
			if (srv_PutConnSCommand((unsigned int*) slot, (unsigned char*) msg) == -1) {
				return -1;
			}
		}
	}

	sprintf(buf, "lb_ExPlayerHasJoined: status on exit: %i", *(unsigned int*) player);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2ef, buf, 1);
	return 0;
}


#include "../../Units/Error/error.h"

int __cdecl srv_PutConnSCommand(unsigned int* player, unsigned char* data);

/* Broadcasts a connection-state change to all active lobby
 * connections. Returns 0 on success, -1 on failure. */

int __cdecl lb_BroadcastStateChange(unsigned int* a, unsigned int* b, unsigned char* c)
{
	unsigned int status;
	unsigned int* conn;

	status = *a;
	if (status & 0x6000) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x2fc, "invalid client state", 1);
		*(unsigned char*) b = 2;
		return srv_PutConnSCommand(a, (unsigned char*) b) == -1 ? -1 : 0;
	}

	*a = status | 0x3000;
	*(unsigned int*) ((char*) b + 0x14) = a[1];
	if (*a & 0x400) {
		*(unsigned int*) ((char*) b + 0x18) = 1;
	} else {
		*(unsigned int*) ((char*) b + 0x18) = 0;
	}

	for (conn = (unsigned int*) g_connections;
	     (int) conn < (int) g_connections + 0x1321320;
	     conn = (unsigned int*) ((char*) conn + 0x264264)) {
		status = *conn;
		if ((status & 1) && (status & 0x200)) {
			if (srv_PutConnSCommand(conn, (unsigned char*) b) == -1) {
				return -1;
			}
		}
	}
	return 0;
}


extern char g_679060[];
void __cdecl fcn_0051af00(void*, int, int);
int __cdecl fcn_005d78e0(char*, char*);

/* arg1 = packet (byte +2 kind, +0x166, +0x1c8 flags), arg2 = player record
 * (state +0, payload +0x14, entity +0x21c). */
int __cdecl lb_ExPlayerRecordBroadcast(unsigned int* player, unsigned char* msg)
{
	int state;
	int ent;

	state = *(int*) msg;
	if (state == 3 || state == 1) {
		if (*((char*) player + 2) == 6) {
			fcn_0051af00((char*) msg + 0x14, (int) g_679060, 0x1dce);
		}
		if (*((char*) player + 0x166) != 0x18) {
			return 1;
		}
		if (*(int*) ((char*) player + 0x1c8) & 0x200) {
			return 9;
		}
		if (*(int*) msg == 3) {
			fcn_005d78e0((char*) player, (char*) msg);
		}
		return 2;
	}
	if (state == 4 || state == 2) {
		ent = 0;
		if (*(int*) ((char*) player + 0x1c8) & 0x100) {
			ent = *(int*) ((char*) msg + 0x21c);
			if (ent != 0) {
				if (*(unsigned char*) (ent + 0x166) != 0x18) {
					return 1;
				}
				if (state == 4) {
					fcn_005d78e0((char*) player, (char*) msg);
					return 0xa;
				}
				if (*((char*) player + 2) == 6) {
					fcn_0051af00((char*) msg + 0x14, (int) g_679060, 0x1dce);
				}
				return 0xa;
			}
		}
		return 1;
	}
	return 1;
}

#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl srv_PutConnSCommand(unsigned int* player, unsigned char* data);

/* Handles a sync command from a player. If the player's command
 * flags indicate an invalid state, logs it and replies with a
 * "no-op" result. Otherwise scans the entity table for the
 * target entity and copies its record into the message. */

int __cdecl lb_HandleEntitySync(int player, int msg)
{
	int tab;
	int eid;
	int i;
	char* dst;
	char* message;

	if ((*(unsigned int*) player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x354, "invalid client state", 1);
		*(char*) msg = 2;
		return (srv_PutConnSCommand((unsigned int*) player, (unsigned char*) msg) == -1) ? -1 : 0;
	}
	/* Reading msg into message before the counters emits the target's schedule:
	 * the reload (`mov edx,[esp+0x14]`) first, then `xor ecx,ecx` and the
	 * table constant, then the two edx-relative reads.  A volatile pin on
	 * msg holds the reload in place but drags both edx-relative reads ahead
	 * of the constants (152/163); a plain read lets msvc6 sink them past the
	 * constants, which is what the target does.  `while` rather than
	 * `do/while` gives the single-compare loop with the `jl` back-edge. */
	message = (char*) msg;
	i = 0;
	tab = (int) g_connections + 4;
	eid = *(int*) (message + 0x14);
	dst = message + 0x14;
	while (tab < (int) g_connections + 0x1321324) {
		if (*(int*) tab == eid) {
			memcpy(dst, (void*) ((int) g_connections + 0x26420c + (unsigned int) i * 0x264264), 0x57);
			return (srv_PutConnSCommand((unsigned int*) player, (unsigned char*) message) == -1) ? -1 : 0;
		}
		tab += 0x264264;
		i++;
	}
	*message = 2;
	return (srv_PutConnSCommand((unsigned int*) player, (unsigned char*) message) == -1) ? -1 : 0;
}

int __cdecl cm_RouteCommand(unsigned int* player, unsigned char* msg)
{
	unsigned int* conn;
	int i;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x37b, "invalid client state", 1);
		*msg = 2;
		return (srv_PutConnSCommand(player, msg) + 1 == 0) ? -1 : 0;
	}
	if (*(unsigned int*) (msg + 0x18) != 0) {
		for (i = 0, conn = (unsigned int*) (g_connections + 4); (int) conn < (int) g_connections + 0x1321324;
		     conn = (unsigned int*) ((char*) conn + 0x264264), i++) {
			if (*conn == *(unsigned int*) (msg + 0x18)) {
				if (srv_PutConnSCommand(
				        (unsigned int*) ((char*) g_connections + i * 0x264264), msg)
				    == -1)
					return -1;
				if (*(unsigned int*) ((char*) g_connections + 4 + i * 0x264264)
				        != *(unsigned int*) ((char*) player + 4)
				    && srv_PutConnSCommand(player, msg) == -1)
					return -1;
				return 0;
			}
		}
		*msg = 2;
		return (srv_PutConnSCommand(player, msg) + 1 == 0) ? -1 : 0;
	}
	for (conn = (unsigned int*) g_connections; (int) conn < (int) g_connections + 0x1321320;
	     conn = (unsigned int*) ((char*) conn + 0x264264)) {
		if ((*conn & 1) == 0)
			continue;
		if ((*conn & 0x200) == 0)
			continue;
		if (srv_PutConnSCommand(conn, msg) == -1)
			return -1;
	}
	return 0;
}

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
		return lb_ExPlayerReadyStatus(player, msg);
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
