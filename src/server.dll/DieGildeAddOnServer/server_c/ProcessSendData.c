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
int __cdecl srv_AcceptConnections(void);
void __cdecl srv_CleanupSockets(void);
int __cdecl ProcessSendData(void);
int __cdecl srv_ReceivePacketHeader(unsigned int* conn);
void __cdecl srv_LogWinsockError(int err_code);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
extern int g_handler_started;
void __cdecl srv_InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl m_ShutdownAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl srv_CreateListenSocket(int port);
void __cdecl m_InitPacketPool(int);
int __cdecl srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); 
int __cdecl srv_SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
int ahm_GetCommandPayloadSize(unsigned char* cmd_payload);
extern handler_func g_dispatch_table[]; 

// FUNCTION: SERVER 0x1000a860
// ProcessSendData
void __cdecl list_unlink_relink(char* ctx, char* node);

int __cdecl ProcessSendData(void)
{
	unsigned char* slot_cursor;
	int result;
	unsigned int* pkt;

	slot_cursor = g_connections;
	do {
		if ((slot_cursor[0] & 1) != 0) {
			result = srv_SendPlayerData((unsigned int*) slot_cursor);
			if (result == -1) {
				return -1;
			}
			while (1) {
				pkt = *(unsigned int**) (slot_cursor + 0x2641f4);
				if (pkt == 0 || (*(unsigned int*) slot_cursor & 0x100) == 0) {
					break;
				}
				memcpy(slot_cursor + 0xb1, pkt, 0x99);
				list_unlink_relink((char*) slot_cursor, *(char**) (slot_cursor + 0x2641f4));
				*(unsigned int*) slot_cursor &= ~0x100;
				result = srv_SendPlayerData((unsigned int*) slot_cursor);
				if (result == -1) {
					return -1;
				}
			}
			if (result == -1) {
				return -1;
			}
		}
		slot_cursor += 0x264264;
	} while ((int) slot_cursor < 0x114ffe20);
	return 0;
}
