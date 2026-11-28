


#include "client_packet_queue.h"

void __cdecl cm_RequestModifyHealth(int entityId, int delta)
{
	char buf[0x9c];

	buf[0] = 0x5a;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = delta;
	cm_EnqueueClientPacket((struct pkt99*) buf);
}
