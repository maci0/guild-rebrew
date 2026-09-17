#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "server_internal.h"

int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
int ahm_GetCommandPayloadSize(unsigned char* cmd_payload);
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

/* Queues a command packet for server-side processing.
 * Copies the packet into the command queue buffer via memcpy. */

// FUNCTION: SERVER 0x1000A8F0
// srv_QueueCommandForProcessing

void* memcpy(void*, const void*, unsigned int);

int __cdecl srv_QueueCommandForProcessing(unsigned int* player_slot, unsigned char* cmd_data)
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
	*(short*) (buf + 1) = ahm_GetCommandPayloadSize((unsigned char*) buf);
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
	*(short*) (buf + 1) = ahm_GetCommandPayloadSize((unsigned char*) buf);
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

