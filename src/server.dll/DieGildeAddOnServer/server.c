#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
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
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessSendData(void);
int __cdecl ReceivePacketHeader(unsigned int* conn);
void __cdecl LogWinsockError(int err_code);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

int __cdecl ServerMainThread(void* lpThreadParameter);
extern int g_stop_flag;
void __cdecl InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl ShutdownMemoryAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl CreateListenSocket(int port);
void __cdecl InitPacketPool(int);
extern int g_net_socket;
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
int __cdecl SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
short __cdecl get_command_type(char*);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern unsigned char g_connections[]; /* 0x101deb00 */
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// FUNCTION: SERVER 0x10009310
// exit_handler
int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}

/* Server initialization: creates the main server thread
 * and stores its handle in g_thread_handle. */

// FUNCTION: SERVER 0x10009320
// Init

HANDLE g_thread_handle;

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
	g_stop_flag = 1;
	do {
		Sleep(10);
	} while (g_stop_flag);
	TerminateThread(g_thread_handle, 0);
	CloseHandle(g_thread_handle);
}

/* Main server thread entry point. Runs the game loop:
 * initializes systems, accepts connections, processes
 * commands, advances simulation, and handles I/O. */

