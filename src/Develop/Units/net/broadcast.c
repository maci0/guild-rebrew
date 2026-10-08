unsigned int g_broadcast_ff = 0xffffffff;


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>
#include "../Error/error.h"

/* REF 0x10027030: dword 0xffffffff then path then "Sending Broadcast".
 * Anonymous string COMDATs omitted the leading dword and shifted every later
 * .data symbol by -4 (need dictionary, crashdump blob, LogFile, …). */
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

/* Client-only (TL 0x402320, discarded): closes the broadcast socket and marks it closed. The socket is
 * g_broadcast_ff: the client's copy (0x675170) is the same -1 dword at the head of this unit's .data,
 * before its first string; no server code reads it. */
void __cdecl CloseBroadcastSocket(void)
{
	SOCKET s;

	s = (SOCKET) g_broadcast_ff;
	if (s != INVALID_SOCKET) {
		closesocket(s);
		g_broadcast_ff = (unsigned int) INVALID_SOCKET;
	}
}
