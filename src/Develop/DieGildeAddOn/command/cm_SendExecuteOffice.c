


#include "Develop/DieGildeAddOn/command/client_packet_queue.h"

#pragma pack(push, 1)

typedef struct
{
	int a;
	int b;
	int c;
	short d;
	char e;
} Packed15;

#pragma pack(pop)
// SIZE 0xf

/* ADDRESS: GOLDDE 0x004b3c60 */
int __cdecl cm_SendExecuteOffice(char* data)
{
	char buf[0x9c];

	buf[0] = 0x45;
	*(Packed15*) (buf + 0x10) = *(Packed15*) data;
	return cm_EnqueueClientPacket((struct pkt99*) buf);
}
