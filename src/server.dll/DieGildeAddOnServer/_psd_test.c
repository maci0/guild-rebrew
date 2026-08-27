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

extern DWORD WINAPI thread_proc(LPVOID);
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

/* Queues a command packet for server-side processing.
 * Copies the packet into the command queue buffer via memcpy. */

// FUNCTION: SERVER 0x1000A8F0
// QueueCommandForProcessing

void* memcpy(void*, const void*, unsigned int);

int __cdecl QueueCommandForProcessing(unsigned int* player_slot, unsigned char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) ((int) player_slot + 0x2641f8);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x671, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) ((int) player_slot + 0x2641f8) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) ((int) player_slot + 0x2641f0);
	if (tail != 0) {
		while (*(int*) (tail + 0x95) != 0) {
			tail = *(int*) (tail + 0x95);
		}
		*(int*) (buf + 0x91) = tail;
		*(int*) (buf + 0x95) = 0;
		*(char**) (tail + 0x95) = buf;
		return 0;
	}
	*(int*) (buf + 0x91) = 0;
	*(int*) (buf + 0x95) = 0;
	*(char**) ((int) player_slot + 0x2641f0) = buf;
	return 0;
}

/* Queues a player command for processing. Wraps the command
 * with player slot info and adds to the processing queue. */

// FUNCTION: SERVER 0x1000A9A0
// cm_QueuePlayerCommand
void* memcpy(void*, const void*, unsigned int);

int __cdecl cm_QueuePlayerCommand(unsigned int* player_slot, unsigned char* cmd_data)
{
	char* buf;
	int tail;

	buf = *(char**) ((int) player_slot + 0x2641fc);
	if (buf == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x6b0, "Commandbuffer full!", 1);
		return -1;
	}
	*(int*) ((int) player_slot + 0x2641fc) = *(int*) (buf + 0x95);
	memcpy(buf, cmd_data, 0x99);
	*(short*) (buf + 1) = get_command_type(buf);
	tail = *(int*) ((int) player_slot + 0x2641f4);
	if (tail != 0) {
		while (*(int*) (tail + 0x95) != 0) {
			tail = *(int*) (tail + 0x95);
		}
		*(int*) (buf + 0x91) = tail;
		*(int*) (buf + 0x95) = 0;
		*(char**) (tail + 0x95) = buf;
		return 0;
	}
	*(int*) (buf + 0x91) = 0;
	*(int*) (buf + 0x95) = 0;
	*(char**) ((int) player_slot + 0x2641f4) = buf;
	return 0;
}

/* Unlinks a node from its current position in a doubly-linked
 * list and relinks it at the head. Used for LRU ordering. */

// FUNCTION: SERVER 0x1000AA50
// list_unlink_relink
void __cdecl list_unlink_relink(char* ctx, char* node)
{
	int prev;
	int next;
	prev = *(int*) (node + 0x91);
	if (prev) {
		next = *(int*) (node + 0x95);
		*(int*) (prev + 0x95) = next;
	}
	else {
		next = *(int*) (node + 0x95);
		*(int*) (ctx + 0x2641f4) = next;
	}
	next = *(int*) (node + 0x95);
	if (next) {
		prev = *(int*) (node + 0x91);
		*(int*) (next + 0x91) = prev;
	}
	*(int*) (node + 0x91) = 0;
	prev = *(int*) (ctx + 0x2641fc);
	*(int*) (node + 0x95) = prev;
	*(int*) (ctx + 0x2641fc) = (int) node;
}

/* Processes all queued commands in order. Dequeues each
 * command, dispatches to the appropriate Chk/Ex handler
 * pair, and writes response data back to clients. */

