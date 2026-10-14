#include "client_packet_queue.h"
/* ADDRESS: GOLD 0x004c4880 */
/* ADDRESS: GOLDTL 0x004c51f0 */



int __cdecl fcn_004c51f0(int a1, int a2, short a3, int a4, char a5, int a6)
{
	char buf[0x9c];

	buf[0] = 0x11;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(short*) (buf + 0x18) = a3;
	*(char*) (buf + 0x1e) = a5;
	*(int*) (buf + 0x1f) = a4;
	*(int*) (buf + 0x23) = a6;
	return fcn_004c4330((struct pkt99*) buf);
}
