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

#endif /* SERVER_INTERNAL_H */
