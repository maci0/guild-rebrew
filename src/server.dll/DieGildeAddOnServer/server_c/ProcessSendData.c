// CFLAGS: /O2 /Gd /Ow
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
unsigned int __stdcall timeGetTime(void);

int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessSendData(void);
int __cdecl ReceivePacketHeader(unsigned int* conn);
void __cdecl LogWinsockError(int err_code);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
extern int g_handler_started;
void __cdecl InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl ShutdownMemoryAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl CreateListenSocket(int port);
void __cdecl InitPacketPool(int);
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); 
int __cdecl SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
int GetCommandPayloadSize(unsigned char* cmd_payload);
extern handler_func g_dispatch_table[]; 

// FUNCTION: SERVER 0x1000a860
// ProcessSendData
void __cdecl list_unlink_relink(char* ctx, char* node);

int __cdecl ProcessSendData(void)
{
	unsigned char* p;
	int r;
	unsigned int* pkt;

	p = g_connections;
	do {
		if ((p[0] & 1) != 0) {
			r = SendPlayerData((unsigned int*) p);
			if (r == -1) {
				return -1;
			}
			while (1) {
				pkt = *(unsigned int**) (p + 0x2641f4);
				if (pkt == 0 || (*(unsigned int*) p & 0x100) == 0) {
					break;
				}
				memcpy(p + 0xb1, pkt, 0x99);
				list_unlink_relink((char*) p, *(char**) (p + 0x2641f4));
				*(unsigned int*) p &= ~0x100;
				r = SendPlayerData((unsigned int*) p);
				if (r == -1) {
					return -1;
				}
			}
			if (r == -1) {
				return -1;
			}
		}
		p += 0x264264;
	} while ((int) p < 0x114ffe20);
	return 0;
}
