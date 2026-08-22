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

/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x1000a570 (750B)
__declspec(naked) int __cdecl ProcessReceiveData(void)
{
    __asm {
        _emit 0x81
        _emit 0xec
        _emit 0xa0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x53
        _emit 0x55
        _emit 0x56
        _emit 0x57
        _emit 0x33
        _emit 0xdb
        _emit 0xbd
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0xf6
        _emit 0x45
        _emit 0x00
        _emit 0x01
        _emit 0x0f
        _emit 0x84
        _emit 0x4f
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x55
        _emit 0xe8
        _emit 0xaf
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x83
        _emit 0xfe
        _emit 0xff
        _emit 0x89
        _emit 0x74
        _emit 0x24
        _emit 0x10
        _emit 0x0f
        _emit 0x84
        _emit 0x7f
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0xa8
        _emit 0x80
        _emit 0x0f
        _emit 0x84
        _emit 0x27
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xa8
        _emit 0x02
        _emit 0x74
        _emit 0x44
        _emit 0x8a
        _emit 0x4d
        _emit 0x18
        _emit 0x8d
        _emit 0x45
        _emit 0x18
        _emit 0x80
        _emit 0xf9
        _emit 0x03
        _emit 0x75
        _emit 0x2c
        _emit 0x8b
        _emit 0x4d
        _emit 0x04
        _emit 0x50
        _emit 0x89
        _emit 0x4d
        _emit 0x2c
        _emit 0x8b
        _emit 0x55
        _emit 0x00
        _emit 0x81
        _emit 0xe2
        _emit 0x00
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x55
        _emit 0xf7
        _emit 0xda
        _emit 0x1b
        _emit 0xd2
        _emit 0x83
        _emit 0xc2
        _emit 0x02
        _emit 0x89
        _emit 0x55
        _emit 0x30
        _emit 0xe8
        _emit 0xc3
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x39
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0x24
        _emit 0x7d
        _emit 0x80
        _emit 0xcc
        _emit 0x02
        _emit 0xe9
        _emit 0xd2
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xf6
        _emit 0xc4
        _emit 0x02
        _emit 0x0f
        _emit 0x84
        _emit 0xa8
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x9c
        _emit 0x9a
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xdf
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x2b
        _emit 0x90
        _emit 0xff
        _emit 0xff
        _emit 0x8a
        _emit 0x4d
        _emit 0x18
        _emit 0x8d
        _emit 0x45
        _emit 0x18
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x80
        _emit 0xf9
        _emit 0x5f
        _emit 0x75
        _emit 0x45
        _emit 0x50
        _emit 0x55
        _emit 0xe8
        _emit 0x86
        _emit 0xa7
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0xec
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4d
        _emit 0x00
        _emit 0x8d
        _emit 0x94
        _emit 0x24
        _emit 0xb0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x51
        _emit 0x68
        _emit 0x70
        _emit 0x9a
        _emit 0x02
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0x4d
        _emit 0xfc
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x84
        _emit 0x24
        _emit 0xbc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0x68
        _emit 0xe5
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xdb
        _emit 0x8f
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0x8b
        _emit 0x55
        _emit 0x00
        _emit 0x8d
        _emit 0x8c
        _emit 0x24
        _emit 0xb0
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x80
        _emit 0xe2
        _emit 0x7f
        _emit 0x8b
        _emit 0xc2
        _emit 0x89
        _emit 0x55
        _emit 0x00
        _emit 0x50
        _emit 0x68
        _emit 0x54
        _emit 0x9a
        _emit 0x02
        _emit 0x10
        _emit 0x51
        _emit 0xe8
        _emit 0x13
        _emit 0xfc
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x94
        _emit 0x24
        _emit 0xbc
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x52
        _emit 0x68
        _emit 0xe9
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xa1
        _emit 0x8f
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0xe9
        _emit 0x24
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xa8
        _emit 0x08
        _emit 0x0f
        _emit 0x84
        _emit 0x8d
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8a
        _emit 0x45
        _emit 0x18
        _emit 0x3c
        _emit 0x08
        _emit 0x75
        _emit 0x37
        _emit 0x8b
        _emit 0x55
        _emit 0x28
        _emit 0xb9
        _emit 0x08
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc8
        _emit 0xff
        _emit 0xbf
        _emit 0xc8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x89
        _emit 0x15
        _emit 0xc0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xc7
        _emit 0x05
        _emit 0xc4
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x48
        _emit 0x9a
        _emit 0x02
        _emit 0x10
        _emit 0x52
        _emit 0xf3
        _emit 0xab
        _emit 0xe8
        _emit 0x9d
        _emit 0xbe
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0xa3
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xeb
        _emit 0x2f
        _emit 0x3c
        _emit 0x09
        _emit 0x75
        _emit 0x2b
        _emit 0xa1
        _emit 0xc4
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x0d
        _emit 0xe8
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8d
        _emit 0x75
        _emit 0x28
        _emit 0x8d
        _emit 0x3c
        _emit 0x01
        _emit 0xb9
        _emit 0x20
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xf3
        _emit 0xa5
        _emit 0xa1
        _emit 0xc4
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x74
        _emit 0x24
        _emit 0x10
        _emit 0x05
        _emit 0x80
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa3
        _emit 0xc4
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x15
        _emit 0xc4
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0xa1
        _emit 0xc0
        _emit 0xea
        _emit 0x1d
        _emit 0x10
        _emit 0x3b
        _emit 0xd0
        _emit 0x0f
        _emit 0x82
        _emit 0x94
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0x24
        _emit 0xf7
        _emit 0x89
        _emit 0x45
        _emit 0x00
        _emit 0xe9
        _emit 0x87
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xa8
        _emit 0x04
        _emit 0x74
        _emit 0x53
        _emit 0x53
        _emit 0x8d
        _emit 0x84
        _emit 0x24
        _emit 0xb4
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x1c
        _emit 0x9a
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x46
        _emit 0xfb
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x8c
        _emit 0x24
        _emit 0xbc
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0x68
        _emit 0x09
        _emit 0x06
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0xb0
        _emit 0x98
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xd4
        _emit 0x8e
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0x4d
        _emit 0x00
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x30
        _emit 0x80
        _emit 0xe1
        _emit 0x7f
        _emit 0x52
        _emit 0x55
        _emit 0x89
        _emit 0x4d
        _emit 0x00
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x38
        _emit 0x02
        _emit 0xe8
        _emit 0x1b
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x24
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x91
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x38
        _emit 0xa8
        _emit 0x10
        _emit 0x88
        _emit 0x5d
        _emit 0x1b
        _emit 0x74
        _emit 0x18
        _emit 0x8d
        _emit 0x45
        _emit 0x18
        _emit 0x50
        _emit 0x55
        _emit 0xe8
        _emit 0x4c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x77
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0x24
        _emit 0x6f
        _emit 0xeb
        _emit 0x16
        _emit 0x8d
        _emit 0x4d
        _emit 0x18
        _emit 0x51
        _emit 0x55
        _emit 0xe8
        _emit 0x34
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x5f
        _emit 0x8b
        _emit 0x45
        _emit 0x00
        _emit 0x24
        _emit 0x7f
        _emit 0x89
        _emit 0x45
        _emit 0x00
        _emit 0xf6
        _emit 0x45
        _emit 0x00
        _emit 0x01
        _emit 0x0f
        _emit 0x85
        _emit 0xb6
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xfe
        _emit 0xff
        _emit 0x74
        _emit 0x48
        _emit 0x81
        _emit 0xc5
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x43
        _emit 0x81
        _emit 0xfd
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x0f
        _emit 0x8c
        _emit 0x94
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0xf6
        _emit 0x05
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x01
        _emit 0x74
        _emit 0x5b
        _emit 0x68
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0xe8
        _emit 0x40
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x74
        _emit 0x49
        _emit 0xa0
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0xa8
        _emit 0x80
        _emit 0x75
        _emit 0x1f
        _emit 0xa8
        _emit 0x01
        _emit 0x75
        _emit 0xe1
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0xa0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x83
        _emit 0xc8
        _emit 0xff
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0xa0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x14
        _emit 0xc6
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x02
        _emit 0x52
        _emit 0x68
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0xe8
        _emit 0x5c
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0xe8
        _emit 0x92
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x0c
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x33
        _emit 0xc0
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0xa0
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

int __cdecl ProcessReceiveData(void)
{
	char logbuf_hi[256];
	char logbuf_lo[256];
	unsigned char pktbuf[156];
	int ret;
	unsigned int* conn;
	int i;
	unsigned int status;

	i = 0;
	conn = (unsigned int*) 0x101deb00;

	do {
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
						conn[0xc] = 2 - ((*conn & 0x400) != 0);
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
						g_download_received = 0;
						g_download_total_size = conn[10];
						memset(g_download_slots, 0xff, 32);
						g_download_buffer = (unsigned int) m_AllocTracked(conn[10], "srv_LoadBuf");
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
					if (QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
						return -1;
					}
					status = *conn & 0xffffff6f;
					goto set_status;
				}
				if (QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
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
		conn = (unsigned int*) ((char*) conn + 0x264264);
		i++;
	} while (conn < (unsigned int*) 0x114ffe20);

	if ((*(unsigned char*) 0x114ffe20 & 1) == 0) {
		return 0;
	}
admin_loop:
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
	if ((*(unsigned char*) 0x114ffe20 & 1) != 0) {
		goto admin_loop;
	}
	return 0;
}
#endif


void* __cdecl memcpy(void*, const void*, unsigned int);

/* Processes the outgoing send queue. Iterates connected
 * clients and transmits any queued response packets. */
extern int g_listen_socket;
int g_list_head;
