


#include "Develop/DieGildeAddOn/command/client_packet_queue.h"

/* ADDRESS: GOLDDE 0x004b42e0 */
void __cdecl cm_RequestModifyHealth(int entityId, int delta)
{
	char buf[0x9c];

	buf[0] = 0x5a;
	*(int*) (buf + 0x10) = entityId;
	*(int*) (buf + 0x14) = delta;
	cm_EnqueueClientPacket((struct pkt99*) buf);
}
