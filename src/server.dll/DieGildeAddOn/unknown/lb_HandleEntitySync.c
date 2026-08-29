/* lb_HandleEntitySync - proper C */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10014bf0
// SYMBOL: _lb_HandleEntitySync
// SIZE: 163

#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);

/* Handles a sync command from a player. If the player's command
 * flags indicate an invalid state, logs it and replies with a
 * "no-op" result. Otherwise scans the entity table for the
 * target entity and copies its record into the message. */

int __cdecl lb_HandleEntitySync(int player, int msg)
{
	int tab;
	int eid;
	int i;
	unsigned int flags;

	flags = *(unsigned int*) player;
	if ((flags & 0x6000) != 0) {
		LogMessageInternal((char*) 0x1002d70c, 0x354, (char*) 0x1002d740, 1);
		*(char*) msg = 2;
		return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1) ? -1 : 0;
	}
	eid = *(int*) ((char*) msg + 0x14);
	tab = 0x101deb04;
	i = 0;
	do {
		if (*(int*) tab == eid) {
			memcpy((char*) msg + 0x14, (void*) (0x10442d0c + (unsigned int) i * 0x264264), 0x57);
			return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1) ? -1 : 0;
		}
		tab += 0x264264;
		i++;
	} while (tab < 0x114ffe24);
	*(char*) msg = 2;
	return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1) ? -1 : 0;
}
