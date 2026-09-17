#ifndef SERVER_INTERNAL_H
#define SERVER_INTERNAL_H

#include "../game_common.h"

/* Server Core Lifecycle */
extern int __cdecl srv_Init(int port);
extern int __stdcall ServerMainThread(void* param);

/* Global Initialization */
extern int __cdecl Init(void* param);
extern void __cdecl Exit(void);

/* Command-dispatch handler fn type (212-entry table at 0x1002c3f8).
 * Used by cm_ProcessCommandQueue.c. */
typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

/* Round-trip catalog names.  exit_handler and ServerMainThread are __stdcall,
 * so every cross-TU reference is decorated with @N (DllMain calls
 * _exit_handler@12, Init takes &_ServerMainThread@4).  A FUNCTION
 * definition's catalog name cannot carry the @N suffix, so these LIBRARY
 * markers supply the decorated spelling round-trip resolves against. */
// LIBRARY: SERVER 0x10009310
// _exit_handler@12

// LIBRARY: SERVER 0x100093a0
// _ServerMainThread@4

#endif /* SERVER_INTERNAL_H */
