#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"
extern char s_Cant_set_SO_RCVBUF_100293e4[];
extern char s_Cant_set_SO_SNDBUF_100293c4[];

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
/* Entity lifecycle (local externs) */
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl gm_InitEntitySlots(void);
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl srv_AcceptConnections(void);
void __cdecl srv_CleanupSockets(void);
int __cdecl srv_ReceivePacketHeader(unsigned int* conn);
void __cdecl srv_LogWinsockError(int err_code);

#include "server_internal.h"

void __cdecl srv_InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl m_ShutdownAllocator();
int __cdecl gm_Open(char*);
int __cdecl srv_CreateListenSocket(int port);
void __cdecl m_init(int);
int __cdecl srv_SendPlayerData(unsigned int*);
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// FUNCTION: GOLDTL 0x4e7600
// SIZE: 90
// cm_ClosePlayerConnection

int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot)
{
	shutdown(player_slot[5], 2);
	closesocket(player_slot[5]);
	*player_slot = 0;
	player_slot[5] = 0xffffffff;
	player_slot[1] = 0;
	memset((char*) player_slot + 0x26420c, 0, 87);
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x500, "Connection dropped.\n", 1);
	return 0;
}

/* Receives a packet header from a client socket. Reads the
 * fixed-size header, validates it, and returns the packet
 * size. Handles partial reads and disconnects. */
