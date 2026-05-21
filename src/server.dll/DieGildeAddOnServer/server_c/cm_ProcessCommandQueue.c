#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
unsigned int __stdcall timeGetTime(void);

/* Command layer (local externs — server.c uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl cm_ProcessCommandQueue(void);
int __cdecl lb_ExLobbyServerCommand(unsigned int*, int);

/* Entity lifecycle (local externs) */
void __cdecl gm_ResetAllEntities(void);
void __cdecl gm_CleanupAllEntities(void);
void __cdecl gm_CleanupObjectEntities(void);
void __cdecl gm_InitEntitySlots(void);
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl AcceptConnections(void);
void __cdecl CleanupSockets(void);
int __cdecl ProcessReceiveData(void);
int __cdecl ProcessSendData(void);
int __cdecl ReceivePacketHeader(unsigned int* conn);
int __cdecl SendBroadcastPacket(unsigned char* data, int size);
void __cdecl LogWinsockError(int err_code);

typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
extern int g_stop_flag;
void __cdecl InitBuildingTypeTable(void);
void __cdecl RecvGameSavegame(void);
int __cdecl srv_Init(void);
int __cdecl AdvanceGameClock(int* clock_state, int a2, int a3, int a4);
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10);
void __cdecl _seterrormode(int value);
void __cdecl ShutdownMemoryAllocator();
int __cdecl gm_Open(char*, char*);
int __cdecl sub_1001a299(char*, char*);
int __cdecl CreateListenSocket(int port);
void __cdecl InitPacketPool(int);
extern int g_net_socket;
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
;
;
int __cdecl SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
extern unsigned int g_player_slots;
short __cdecl get_command_type(char*);
int __cdecl ahm_ProcessEntityChain(unsigned char* node);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
;
extern unsigned char g_connections[]; /* 0x101deb00 */
;

;
;
;
;
;
;

/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// STUB: SERVER 0x1000aac0
// cm_ProcessCommandQueue

int __cdecl cm_ProcessCommandQueue(void)
{
	unsigned int* slot;
	unsigned char* node;
	unsigned char* type5;
	unsigned char* next_save;
	unsigned char* next_field;
	volatile int result;
	int valid;
	unsigned int player_idx;
	unsigned char* conn;
	unsigned int i;

	for (slot = (unsigned int*) 0x10442cf0; (unsigned int) slot < 0x11764010;
		slot = (unsigned int*) ((unsigned char*) slot + 0x264264)) {
		node = (unsigned char*) slot[0];
		type5 = 0;

		while (node != 0) {
			next_save = *(unsigned char**) (node + 0x95);
			next_field = node + 0x95;
			valid = 1;

			if (type5 != 0) {
				if (*(unsigned char*) node != 6) {
					goto advance;
				}
				result = ahm_ProcessEntityChain(type5);
				if (result == 0) {
					valid = 0;
				}
				next_save = *(unsigned char**) (type5 + 0x95);
				next_field = type5 + 0x95;
				node = type5;
				type5 = 0;
				if (valid == 0) {
					goto advance;
				}
			}
			else {
				if (*(unsigned char*) node == 5) {
					type5 = node;
					goto advance;
				}
			}

			/* Unlink node from pending list */
			if (node == (unsigned char*) slot[0]) {
				slot[0] = (unsigned int) next_save;
			}
			else {
				*(unsigned int*) (*(unsigned int*) (node + 0x91) + 0x95) = *(unsigned int*) next_field;
				*(unsigned int*) (*(unsigned int*) next_field + 0x91) = *(unsigned int*) (node + 0x91);
			}
			*(unsigned int*) (node + 0x91) = 0;
			*(unsigned int*) next_field = slot[2];
			slot[2] = (unsigned int) node;

			if (*(unsigned char*) node >= 0x6a) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOnServer\\server.c",
					0x756,
					"Command-Type out of Range!\n",
					1
				);
				goto advance;
			}

			if (*(unsigned char*) node == 0x20 && node[0x10] == 0x0e) {
				player_idx = (unsigned int) node[3];
				if ((g_connections[player_idx * 0x264264] & 0x40) != 0) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x72e, "Multisync!!!", 1);
				}
			}

			result = g_dispatch_table[(unsigned int) *(unsigned char*) node](node, 0);

			if (0 != result) {
				player_idx = (unsigned int) node[3];
				if ((g_connections[player_idx * 0x264264] & 1) == 0) {
					goto advance;
				}
				*(unsigned char*) node = 2;
				result = cm_QueuePlayerCommand((unsigned int*) &g_connections[player_idx * 0x264264], node);
				if (result != -1) {
					goto advance;
				}
				return -1;
			}

			/* Handler returned 0 */
			if (*(char*) node == 0x20 && node[0x10] == 0x0e) {
				player_idx = (unsigned int) node[3];
				memcpy((void*) (player_idx * 0x264264 + 0x10442c54), node, 153);
				goto advance;
			}

			player_idx = (unsigned int) node[3];
			conn = &g_connections[player_idx * 0x264264];
			if ((*conn & 1) != 0) {
				result = cm_QueuePlayerCommand((unsigned int*) conn, node);
				if (result == -1) {
					return -1;
				}
			}

			*(int*) (node + 4) = -1;
			i = 0;
			conn = &g_connections[0];
			do {
				if (i != (unsigned int) node[3] && (*conn & 1) != 0) {
					result = cm_QueuePlayerCommand((unsigned int*) conn, node);
					if (result == -1) {
						return -1;
					}
				}
				conn += 0x264264;
				i++;
			} while ((int) conn < 0x114ffe20);

		advance:
			node = next_save;
		}

	}

	return 0;
}

/* Logs a Winsock error by error code. Maps WSA error codes
 * to human-readable strings and passes to the log system. */
