#include "client_packet_queue.h"
// FUNCTION: GOLD 0x004c48e0
// FUNCTION: GOLDTL 0x4c5250



int __cdecl fcn_004c5250(int a1, unsigned short a2, int a3)
{
	char buf[0x9c];

	buf[0] = 0x12;
	*(int*) (buf + 0x10) = a1;
	*(unsigned short*) (buf + 0x14) = a2;
	*(int*) (buf + 0x16) = a3;
	return fcn_004c4330((struct pkt99*) buf);
}
