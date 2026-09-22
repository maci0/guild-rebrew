#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

// FUNCTION: GOLDTL 0x4f9300
// SIZE: 240
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

