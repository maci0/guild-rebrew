#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

/* Module-specific external strings and data */
extern char s_D__Develop_DieGildeAddOn_command_1002d70c[];
extern char s_lb_ExLobbyServerCommand___i_1002d858[];

/* Module-specific globals with complex types */
extern PlayerSlot g_player_slots_base[8];
extern short g_record_table[];

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
		LogMessageInternal((char*) 0x1002d70c, 0x244, (char*) 0x1002d740, 1);
		*msg = 2;
		result = cm_QueuePlayerCommand(player, msg);
		return (result + 1 == 0) ? -1 : 0;
	}
	memset(&list, 0, sizeof(list));
	list.count = 0;
	for (conn = (unsigned int*) 0x101deb00; (int) conn < 0x114ffe20; conn = (unsigned int*) ((char*) conn + 0x264264)) {
		if ((*conn & 1) == 0) continue;
		if ((*conn & 0x200) == 0) continue;
		list.ids[list.count] = conn[1];
		list.count++;
	}
	memcpy((char*) msg + 0x14, &list, sizeof(list));
	result = cm_QueuePlayerCommand(player, msg);
	if (result == -1) return -1;
	LogMessageInternal((char*) 0x1002d70c, 0x258, (char*) 0x1002d6f8, 1);
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
		LogMessageInternal((char*) 0x1002d70c, 0x264, (char*) 0x1002d740, 1);
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
		LogMessageInternal((char*) 0x1002d70c, 0x279, (char*) 0x1002d774, 1);
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
	for (conn = (unsigned char*) 0x101deb00; (int) conn < 0x114ffe20; conn += 0x264264) {
		if ((*(unsigned int *) conn & 1) == 0) continue;
		if ((*(unsigned int *) conn & 0x200) == 0) continue;
		result = cm_QueuePlayerCommand((unsigned int*) conn, msg);
		if (result == -1) return -1;
	}
	LogMessageInternal((char*) 0x1002d70c, 0x28c, (char*) 0x1002d758, 1);
	return 0;
}



// FUNCTION: SERVER 0x10014db0
// lb_ExLobbyServerCommand
int __cdecl lb_ExPlayerHasJoined(unsigned int*, unsigned char*);
int __cdecl lb_BroadcastStateChange(unsigned int*, unsigned char*);
int __cdecl fcn_10014af0(unsigned int*, unsigned char*);
int __cdecl lb_HandleEntitySync(unsigned int*, unsigned char*);
int __cdecl cm_RouteCommand(unsigned int*, unsigned char*);

int __cdecl lb_ExLobbyServerCommand(unsigned int* player, unsigned char* msg)
{
	char buf[0x80];

	sprintf(buf, (char*) 0x1002d858, *(unsigned char*) (msg + 0x10));
	LogMessageInternal((char*) 0x1002d70c, 0x3a5, buf, 1);
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
		return fcn_10014af0(player, msg);
	case 5:
		return lb_HandleEntitySync(player, msg);
	case 6:
		return cm_RouteCommand(player, msg);
	}
	return 1;
}

// FUNCTION: SERVER 0x10014af0
int __cdecl fcn_10014af0(unsigned int* player, unsigned char* msg)
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

