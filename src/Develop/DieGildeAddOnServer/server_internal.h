#ifndef SERVER_INTERNAL_H
#define SERVER_INTERNAL_H

#include "../game_common.h"

/* Server Core Lifecycle */
extern int __cdecl srv_Init(int port);
extern int __stdcall ServerMainThread(void* param);

/* Global Initialization */
extern int __cdecl Init(void* param);
extern void __cdecl Exit(void);

/* Handler type for two adjacent 106-entry tables at 0x1002c3f8 and 0x1002c5a0.
 * Used by server.c; the tables have separate storage identities. */
typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

/* DllMain and ServerMainThread are __stdcall, so cross-TU references
 * carry the @N decoration: the CRT entry calls _DllMain@12 and Init
 * takes &_ServerMainThread@4. Their managed FUNCTION rows record
 * these decorated symbols; the comments below are name references.
 * This header supplies no LIBRARY bindings for these functions. */

// _DllMain@12


// _ServerMainThread@4

#endif /* SERVER_INTERNAL_H */
