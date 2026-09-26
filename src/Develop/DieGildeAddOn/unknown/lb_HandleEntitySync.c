/* lb_HandleEntitySync - proper C */

// FUNCTION: SERVER 0x10014bf0
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
	char* dst;
	char* message;

	if ((*(unsigned int*) player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x354, "invalid client state", 1);
		*(char*) msg = 2;
		return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) msg) == -1) ? -1 : 0;
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
	tab = 0x101deb04;
	eid = *(int*) (message + 0x14);
	dst = message + 0x14;
	while (tab < 0x114ffe24) {
		if (*(int*) tab == eid) {
			memcpy(dst, (void*) (0x10442d0c + (unsigned int) i * 0x264264), 0x57);
			return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) message) == -1) ? -1 : 0;
		}
		tab += 0x264264;
		i++;
	}
	*message = 2;
	return (cm_QueuePlayerCommand((unsigned int*) player, (unsigned char*) message) == -1) ? -1 : 0;
}
