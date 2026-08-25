// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10014a50
// lb_BroadcastStateChange

#include "../../../Units/Error/error.h"

int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);

/* Broadcasts a connection-state change to all active lobby
 * connections. Returns 0 on success, -1 on failure. */

int __cdecl lb_BroadcastStateChange(unsigned int* a, unsigned int* b, unsigned char* c)
{
	unsigned int status;
	unsigned int* conn;

	status = *a;
	if (status & 0x6000) {
		LogMessageInternal((char*) 0x1002d70c, 0x2fc, (char*) 0x1002d740, 1);
		*(unsigned char*) b = 2;
		return cm_QueuePlayerCommand(a, (unsigned char*) b) == -1 ? -1 : 0;
	}

	*a = status | 0x3000;
	*(unsigned int*) ((char*) b + 0x14) = a[1];
	if (*a & 0x400) {
		*(unsigned int*) ((char*) b + 0x18) = 1;
	} else {
		*(unsigned int*) ((char*) b + 0x18) = 0;
	}

	for (conn = (unsigned int*) 0x101deb00;
	     (int) conn < 0x114ffe20;
	     conn = (unsigned int*) ((char*) conn + 0x264264)) {
		status = *conn;
		if ((status & 1) && (status & 0x200)) {
			if (cm_QueuePlayerCommand(conn, (unsigned char*) b) == -1) {
				return -1;
			}
		}
	}
	return 0;
}
