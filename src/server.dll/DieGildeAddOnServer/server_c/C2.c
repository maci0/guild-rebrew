// FUNCTION: SERVER 0x1000a570
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
int __cdecl lb_ExLobbyServerCommand(unsigned int*, int);

/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl ProcessReceiveData(void);
int __cdecl ReceivePacketHeader(unsigned int* conn);
typedef int(__cdecl* handler_func)(unsigned char* pkt, int param);

extern DWORD WINAPI thread_proc(LPVOID);
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern unsigned char g_connections[]; /* 0x101deb00 */
extern unsigned int g_download_total_size;
extern unsigned int g_download_received;
extern unsigned int g_download_slots[8];
extern unsigned int g_download_buffer;
extern int ReceivePacketHeader(unsigned int* conn);
extern int QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt);

/* ProcessReceiveData: drains the receive buffers of all connected
 * player slots. For each connected slot, loops calling
 * ReceivePacketHeader; when a full CommandPacket arrives, validates
 * the connection state flags (0x80 = packet pending) and dispatches:
 * bulk-transfer setup (cmd 0x08/0x09), lobby commands (0x5f),
 * unexpected-request handling, and queuing via
 * QueueCommandForProcessing. Also services the admin connection at
 * 0x114ffe20. */

// CFLAGS: /O2 /Gd

int __cdecl ProcessReceiveData(void)
{
	char logbuf_hi[256];
	char logbuf_lo[256];
	unsigned char pktbuf[156];
	int ret;
	unsigned int* conn;
	int i;
	unsigned int status;
	unsigned int total;

	for (i = 0, conn = (unsigned int*) 0x101deb00; (int) conn < 0x114ffe20; conn = (unsigned int*) ((char*) conn + 0x264264), i++) {
		if ((*(unsigned char*) conn & 1) != 0) {
			do {
				ret = ReceivePacketHeader(conn);
				if (ret == -1) {
					return -1;
				}
				status = *conn;
				if ((status & 0x80) == 0) {
					break;
				}
				if (status & 2) {
					if (*(unsigned char*) (conn + 6) == 3) {
						conn[0xb] = conn[1];
						conn[0xc] = (*conn & 0x400) ? 1 : 2;
						if (cm_QueuePlayerCommand(conn, (unsigned char*) (conn + 6)) == -1) {
							return -1;
						}
					}
					status = *conn & 0xffffff7d | 0x200;
					goto set_status;
				}
				if (status & 0x200) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
					if (*(unsigned char*) (conn + 6) == 0x5f) {
						if (lb_ExLobbyServerCommand(conn, (int) (conn + 6)) == -1) {
							return -1;
						}
						sprintf(logbuf_lo, "status after lb_ExLobbyServerCommand: %i", *conn);
						LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e5, logbuf_lo, 1);
					}
					*conn = *conn & 0xffffff7f;
					sprintf(logbuf_lo, "leaving lobby branch: %i", *conn);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e9, logbuf_lo, 1);
					goto done_inner;
				}
				if (status & 8) {
					if (*(unsigned char*) (conn + 6) == 8) {
						total = conn[10];
						g_download_total_size = total;
						g_download_received = 0;
						memset(g_download_slots, 0xff, 32);
						g_download_buffer = (unsigned int) m_AllocTracked(total, "srv_LoadBuf");
					}
					else if (*(unsigned char*) (conn + 6) == 9) {
						memcpy((void*) (g_download_buffer + g_download_received), conn + 10, 0x80);
						g_download_received = g_download_received + 0x80;
					}
					if (g_download_received >= g_download_total_size) {
						*conn = *conn & 0xfffffff7;
					}
					status = *conn & 0xffffff7f;
					goto set_status;
				}
				if (status & 4) {
					sprintf(logbuf_hi, "Unexpected Request from connection nr %i", i);
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x609, logbuf_hi, 1);
					*conn = *conn & 0xffffff7f;
					pktbuf[0] = 2;
					if (cm_QueuePlayerCommand(conn, pktbuf) == -1) {
						return -1;
					}
					goto done_inner;
				}
				*((unsigned char*) conn + 0x1b) = (unsigned char) i;
				if (status & 0x10) {
					if (QueueCommandForProcessing(conn, (unsigned char*) &conn[6]) != 0) {
						return -1;
					}
					status = *conn & 0xffffff6f;
					goto set_status;
				}
				if (QueueCommandForProcessing(conn, (unsigned char*) &conn[6]) != 0) {
					return -1;
				}
				status = *conn & 0xffffff7f;
			set_status:
				*conn = status;
			done_inner:;
			} while ((*(unsigned char*) conn & 1) != 0);
			if (ret == -1) {
				return -1;
			}
		}
	}

	while ((*(unsigned char*) 0x114ffe20 & 1) != 0) {
		i = ReceivePacketHeader((unsigned int*) 0x114ffe20);
		if (i == -1) {
			return 0;
		}
		if ((*(unsigned char*) 0x114ffe20 & 0x80) != 0) {
			pktbuf[0] = 2;
			cm_QueuePlayerCommand((unsigned int*) 0x114ffe20, pktbuf);
			cm_ClosePlayerConnection((unsigned int*) 0x114ffe20);
			return 0;
		}
	}
	return 0;
}


void* __cdecl memcpy(void*, const void*, unsigned int);

/* Processes the outgoing send queue. Iterates connected
 * clients and transmits any queued response packets. */
extern int g_listen_socket;
int g_list_head;