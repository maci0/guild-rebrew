#include "Develop/DieGildeAddOn/command/client_packet_queue.h"



/* ADDRESS: GOLDTL 0x004c51f0 */
int __cdecl cm_SendSellObjekt(int targetId, int buildingId, short itemId, int amount, char marketId, int flags)
{
	char buf[0x9c];

	buf[0] = 0x11;
	*(int*) (buf + 0x10) = targetId;
	*(int*) (buf + 0x14) = buildingId;
	*(short*) (buf + 0x18) = itemId;
	*(char*) (buf + 0x1e) = marketId;
	*(int*) (buf + 0x1f) = amount;
	*(int*) (buf + 0x23) = flags;
	return cm_EnqueueClientPacket((struct pkt99*) buf);
}
