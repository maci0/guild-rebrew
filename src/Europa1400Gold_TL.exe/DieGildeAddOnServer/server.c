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

// FUNCTION: GOLDTL 0x41fa00
// SIZE: 8

int __stdcall exit_handler(int a, int b, int c)
{
	return 1;
}

/* Server initialization: creates the main server thread
 * and stores its handle in g_thread_handle. */
