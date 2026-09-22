// FUNCTION: SERVER 0x100147b0
#include <stdio.h>
#include <string.h>
#include "../command.h"
#include "../../../Units/Error/error.h"

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
		LogMessageInternal((char*) 0x1002d70c, 0x29a, (char*) 0x1002d740, 1);
		msg[0] = 2;
		return cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1 ? -1 : 0;
	} else if ((flags & 0x2000) == 0) {
		LogMessageInternal((char*) 0x1002d70c, 0x2a4, (char*) 0x1002d740, 1);
		msg[0] = 2;
		return cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1 ? -1 : 0;
	} else {
		goto join;
	}

join:
	count = 0;
	for (slot = (PlayerSlot*) 0x101deb00;
	     (int) slot < 0x114ffe20;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200) && !(flags & 0x2000)) {
			count++;
		}
	}
	if (count >= g_max_players) {
		LogMessageInternal((char*) 0x1002d70c, 0x2b1, (char*) 0x1002d848, 1);
		msg[0] = 2;
		if (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1) {
			return -1;
		}
		cm_ClosePlayerConnection((unsigned int*) player);
		return 0;
	}

	m14 = msg + 0x14;
	slot = (PlayerSlot*) 0x101deb00;
	*(unsigned int*) (m14 + 4) = 0;
	for (; (int) slot < 0x114ffe20;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200) && (char*) slot != player &&
		    *(int*) ((char*) slot + 0x264218) == *(int*) (m14 + 0xc)) {
			arr[0] = 0; arr[1] = 0; arr[2] = 0; arr[3] = 0;
			arr[4] = 0; arr[5] = 0; arr[6] = 0; arr[7] = 0;
			for (slot_cursor = arr, slot2 = (PlayerSlot*) 0x101deb00;
			     (int) slot2 < 0x114ffe20;
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

	sprintf(buf, (char*) 0x1002d81c, *(unsigned int*) player);
	LogMessageInternal((char*) 0x1002d70c, 0x2dd, buf, 1);
	memcpy((char*) player + 0x26420c, m14, 87);
	sprintf(buf, (char*) 0x1002d7f0, *(unsigned int*) player);
	LogMessageInternal((char*) 0x1002d70c, 0x2e2, buf, 1);
	*(unsigned int*) player &= ~0x2000;
	sprintf(buf, (char*) 0x1002d7b4, *(unsigned int*) player);
	LogMessageInternal((char*) 0x1002d70c, 0x2e7, buf, 1);

	for (slot = (PlayerSlot*) 0x101deb00;
	     (int) slot < 0x114ffe20;
	     slot = (PlayerSlot*) ((char*) slot + 0x264264)) {
		flags = slot->flags;
		if ((flags & 1) && (flags & 0x200)) {
			if (cm_QueuePlayerCommand((unsigned int*) slot, (unsigned char*) msg) == -1) {
				return -1;
			}
		}
	}

	sprintf(buf, (char*) 0x1002d788, *(unsigned int*) player);
	LogMessageInternal((char*) 0x1002d70c, 0x2ef, buf, 1);
	return 0;
}
