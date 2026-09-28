#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "server_internal.h"

int __stdcall ServerMainThread(void* lpThreadParameter);

/* This TU's initialised data leads the server block; nothing names these
 * symbols (ServerMainThread and srv_Init address the game path buffer by
 * its raw address), but they must occupy this exact span. */
// DATA: SERVER 0x1002956c
char s_This_is_Gilde_talking__can_you_h[] = "This is Gilde talking, can you hear me?";
// DATA: SERVER 0x10029594
char g_game_path[0x104] = "\\project\\DieGilde\\game\\";
// DATA: SERVER 0x10029698
char g_game_path_default[0x104] = "\\project\\DieGilde\\game\\";
// GLOBAL: SERVER 0x1002979c
int g_server_flag = 1;

// GLOBAL: SERVER 0x10034680
int g_handler_started = 0;
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// GLOBAL: SERVER 0x11764094
void* g_thread_handle = 0;
// FUNCTION: GOLDTL 0x41fa00
// SIZE: 8
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
