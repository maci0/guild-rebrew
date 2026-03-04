#ifndef NET_H
#define NET_H

#include "../../game_common.h"

/* Socket Management */
extern int __cdecl CreateListenSocket(int port);
extern void __cdecl CleanupSockets(void);
extern int __cdecl AcceptConnections(int listen_socket);

/* Packet Processing */
extern int __cdecl ReceivePacketHeader(int socket, void* header);
extern int __cdecl ProcessReceiveData(int socket, unsigned char* data, int size);
extern int __cdecl ProcessSendData(int socket, unsigned char* data, int size);

/* Broadcast */
extern int __cdecl SendBroadcastPacket(unsigned char* data, int size);

/* Winsock helpers */
extern void __cdecl LogWinsockError(char* msg, int error_code);

#endif /* NET_H */
