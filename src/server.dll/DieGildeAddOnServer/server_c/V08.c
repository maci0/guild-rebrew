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

/* Connection slot layout: flags/state dword at 0x00, connection id at
 * 0x04, socket at 0x14, and the command packet / receive buffer at 0x18.
 * Slots are 0x264264 bytes apart; the admin connection lives at 0x114ffe20. */
typedef struct conn_slot {
    unsigned int flags;        /* 0x000 */
    unsigned int conn_id;      /* 0x004 */
    unsigned char pad[0x0c];   /* 0x008-0x013 */
    unsigned int socket;       /* 0x014 */
    unsigned char pkt[0x100];  /* 0x018 receive buffer / command packet */
} conn_slot;

// CFLAGS: /O2 /Gd

int __cdecl ProcessReceiveData(void)
{
    char logbuf_hi[256];
    char logbuf_lo[256];
    unsigned char pktbuf[156];
    int ret;
    conn_slot* conn;
    int i;
    unsigned int status;
    unsigned int total;

    for (i = 0, conn = (conn_slot*) 0x101deb00; (int) conn < 0x114ffe20; conn = (conn_slot*) ((char*) conn + 0x264264), i++) {
        if ((conn->flags & 1) != 0) {
            do {
                ret = ReceivePacketHeader((unsigned int*) conn);
                if (ret == -1) {
                    return -1;
                }
                status = conn->flags;
                if ((status & 0x80) == 0) {
                    break;
                }
                if (status & 2) {
                    if (conn->pkt[0] == 3) {
                        *(unsigned int*) (conn->pkt + 0x14) = conn->conn_id;
                        *(unsigned int*) (conn->pkt + 0x18) = (conn->flags & 0x400) ? 1 : 2;
                        if (cm_QueuePlayerCommand((unsigned int*) conn, conn->pkt) == -1) {
                            return -1;
                        }
                    }
                    status = conn->flags & 0xffffff7d | 0x200;
                    goto set_status;
                }
                if (status & 0x200) {
                    LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
                    if (conn->pkt[0] == 0x5f) {
                        if (lb_ExLobbyServerCommand((unsigned int*) conn, (int) conn->pkt) == -1) {
                            return -1;
                        }
                        sprintf(logbuf_lo, "status after lb_ExLobbyServerCommand: %i", conn->flags);
                        LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e5, logbuf_lo, 1);
                    }
                    conn->flags = conn->flags & 0xffffff7f;
                    sprintf(logbuf_lo, "leaving lobby branch: %i", conn->flags);
                    LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5e9, logbuf_lo, 1);
                    goto done_inner;
                }
                if (status & 8) {
                    if (conn->pkt[0] == 8) {
                        total = *(unsigned int*) (conn->pkt + 0x10);
                        g_download_total_size = total;
                        g_download_received = 0;
                        memset(g_download_slots, 0xff, 32);
                        g_download_buffer = (unsigned int) m_AllocTracked(total, "srv_LoadBuf");
                    }
                    else if (conn->pkt[0] == 9) {
                        memcpy((void*) (g_download_buffer + g_download_received), conn->pkt + 0x10, 0x80);
                        g_download_received = g_download_received + 0x80;
                    }
                    if (g_download_received >= g_download_total_size) {
                        conn->flags = conn->flags & 0xfffffff7;
                    }
                    status = conn->flags & 0xffffff7f;
                    goto set_status;
                }
                if (status & 4) {
                    sprintf(logbuf_hi, "Unexpected Request from connection nr %i", i);
                    LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x609, logbuf_hi, 1);
                    conn->flags = conn->flags & 0xffffff7f;
                    pktbuf[0] = 2;
                    if (cm_QueuePlayerCommand((unsigned int*) conn, pktbuf) == -1) {
                        return -1;
                    }
                    goto done_inner;
                }
                conn->pkt[3] = (unsigned char) i;
                if (status & 0x10) {
                    if (QueueCommandForProcessing((unsigned int*) conn, conn->pkt) != 0) {
                        return -1;
                    }
                    status = conn->flags & 0xffffff6f;
                    goto set_status;
                }
                if (QueueCommandForProcessing((unsigned int*) conn, conn->pkt) != 0) {
                    return -1;
                }
                status = conn->flags & 0xffffff7f;
            set_status:
                conn->flags = status;
            done_inner:;
            } while ((conn->flags & 1) != 0);
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
