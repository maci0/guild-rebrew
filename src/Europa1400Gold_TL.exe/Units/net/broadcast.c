/* Sends a broadcast packet to all connected clients via UDP.
 * Iterates player slots and transmits the packet data. */

// FUNCTION: GOLDTL 0x5c86b0
// SIZE: 191
// SendBroadcastPacket

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>
#include "../Error/error.h"

// SIZE 0x10 — struct sockaddr_in (Winsock system struct)
void __cdecl SendBroadcastPacket(int port, char* buf)
{
	SOCKET s;
	struct sockaddr_in bind_addr;
	struct sockaddr_in broadcast_addr;
	int broadcast_enable;

	broadcast_enable = 1;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*) &broadcast_enable, 4);

	bind_addr.sin_family = AF_INET;
	bind_addr.sin_addr.s_addr = htonl(0);
	bind_addr.sin_port = htons(0);
	bind(s, (struct sockaddr*) &bind_addr, 16);

	broadcast_addr.sin_family = AF_INET;
	broadcast_addr.sin_addr.s_addr = htonl(0xFFFFFFFF);
	broadcast_addr.sin_port = htons((unsigned short) port);
	sendto(s, buf, 0x6a, 0, (struct sockaddr*) &broadcast_addr, 16);

	closesocket(s);

	LogMessageInternal("D:\\Develop\\Units\\net\\broadcast.c", 0x14f, "Sending Broadcast", 1);
}
