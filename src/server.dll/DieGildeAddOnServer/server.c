#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
unsigned int __stdcall timeGetTime(void);

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
/* Entity lifecycle (local externs) */
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl gm_InitEntitySlots(void);
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl srv_AcceptConnections(void);
void __cdecl srv_CleanupSockets(void);
int __cdecl ProcessSendData(void);
int __cdecl srv_ReceivePacketHeader(unsigned int* conn);
void __cdecl srv_LogWinsockError(int err_code);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

int __stdcall ServerMainThread(void* lpThreadParameter);
extern int g_handler_started;
void __cdecl srv_InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl m_ShutdownAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl srv_CreateListenSocket(int port);
void __cdecl m_init(int);
int __cdecl srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
int __cdecl srv_SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
int ahm_GetCommandPayloadSize(unsigned char* cmd_payload);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// FUNCTION: SERVER 0x10009310
// SIZE: 8
int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}

/* Server initialization: creates the main server thread
 * and stores its handle in g_thread_handle. */

// FUNCTION: SERVER 0x10009320
// Init

void* g_thread_handle;

int __cdecl Init(LPVOID param)
{
	g_thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ServerMainThread, param, 0, (LPDWORD) &param);
	return g_thread_handle != 0;
}

/* Server shutdown: signals the main thread to stop,
 * terminates it, and closes the handle. */

// FUNCTION: SERVER 0x10009350
// Exit

void __cdecl Exit(void)
{
	if (!g_thread_handle) {
		return;
	}
	g_handler_started = 1;
	do {
		Sleep(10);
	} while (g_handler_started);
	TerminateThread(g_thread_handle, 0);
	CloseHandle(g_thread_handle);
}

/* Main server thread entry point. Runs the game loop:
 * initializes systems, accepts connections, processes
 * commands, advances simulation, and handles I/O. */

