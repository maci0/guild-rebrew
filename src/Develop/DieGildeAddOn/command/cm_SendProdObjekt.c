#include "Develop/DieGildeAddOn/command/client_packet_queue.h"



/* ADDRESS: GOLDTL 0x004c5250 */
int __cdecl cm_SendProdObjekt(int building_id, unsigned short item_id, int amount)
{
	char buf[0x9c];

	buf[0] = 0x12;
	*(int*) (buf + 0x10) = building_id;
	*(unsigned short*) (buf + 0x14) = item_id;
	*(int*) (buf + 0x16) = amount;
	return cm_EnqueueClientPacket((struct pkt99*) buf);
}
