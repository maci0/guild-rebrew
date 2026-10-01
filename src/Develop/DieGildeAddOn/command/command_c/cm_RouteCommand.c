extern unsigned char g_connections[9 * 0x264264];
/* Command-layer router: refuses commands from clients flagged 0x6000, routes a
 * reply addressed to one connection (msg+0x18) to that connection's slot, and
 * otherwise queues the command to every ready player slot.  Restored from
 * lobby_c/lb_BroadcastStateChange.c.bak, the only copy left after that TU was
 * split; no live file defined it. */

extern int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);

// FUNCTION: SERVER 0x10014ca0
int __cdecl cm_RouteCommand(unsigned int* player, unsigned char* msg)
{
	unsigned int* conn;
	int i;

	if ((*player & 0x6000) != 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\lobbycommands.c", 0x37b, "invalid client state", 1);
		*msg = 2;
		return (cm_QueuePlayerCommand(player, msg) + 1 == 0) ? -1 : 0;
	}
	if (*(unsigned int*) (msg + 0x18) != 0) {
		for (i = 0, conn = (unsigned int*) (int) (g_connections + 0x4); (int) conn < (int) (g_connections + 0x1321324);
		     conn = (unsigned int*) ((char*) conn + 0x264264), i++) {
			if (*conn == *(unsigned int*) (msg + 0x18)) {
				if (cm_QueuePlayerCommand(
				        (unsigned int*) ((char*) (int) g_connections + i * 0x264264), msg)
				    == -1)
					return -1;
				if (*(unsigned int*) ((char*) (int) (g_connections + 0x4) + i * 0x264264)
				        != *(unsigned int*) ((char*) player + 4)
				    && cm_QueuePlayerCommand(player, msg) == -1)
					return -1;
				return 0;
			}
		}
		*msg = 2;
		return (cm_QueuePlayerCommand(player, msg) + 1 == 0) ? -1 : 0;
	}
	for (conn = (unsigned int*) (int) g_connections; (int) conn < (int) (g_connections + 0x1321320);
	     conn = (unsigned int*) ((char*) conn + 0x264264)) {
		if ((*conn & 1) == 0)
			continue;
		if ((*conn & 0x200) == 0)
			continue;
		if (cm_QueuePlayerCommand(conn, msg) == -1)
			return -1;
	}
	return 0;
}
