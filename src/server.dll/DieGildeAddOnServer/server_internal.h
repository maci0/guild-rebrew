#ifndef SERVER_INTERNAL_H
#define SERVER_INTERNAL_H

#include "../game_common.h"

/* Server Core Lifecycle */
extern int __cdecl srv_Init(int port);
extern int __stdcall ServerMainThread(void* param);
extern int __cdecl srv_RecvGame(void);

/* Global Initialization */
extern void __cdecl Init(void);
extern void __cdecl Exit(void);

#endif /* SERVER_INTERNAL_H */
