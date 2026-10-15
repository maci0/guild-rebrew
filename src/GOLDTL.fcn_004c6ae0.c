


#include "client_packet_queue.h"

void __cdecl fcn_004c6ae0(int a1, int a2)
{
	char buf[0x9c];

	buf[0] = 0x5a;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	fcn_004c4330((struct pkt99*) buf);
}
