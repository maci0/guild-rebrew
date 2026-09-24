// GLOBAL: SERVER 0x117640c4
int g_list_head;
// FUNCTION: SERVER 0x1000a570
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* Command layer (local externs — server.header uses different signatures) */
int __cdecl cm_QueuePlayerCommand(unsigned int* player, unsigned char* data);
int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot);
int __cdecl lb_ExLobbyServerCommand(unsigned int*, int);

/* Entity lifecycle (local externs) */
/* Network functions (local externs — signatures differ from net.h) */
int __cdecl srv_LoadBuf(void);
#include "../server_internal.h"

int __cdecl srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
extern int srv_ReceivePacketHeader(unsigned int* conn);
extern int srv_QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt);

/* srv_LoadBuf: drains the receive buffers of all connected
 * player slots. For each connected slot, loops calling
 * srv_ReceivePacketHeader; when a full CommandPacket arrives, validates
 * the connection state flags (0x80 = packet pending) and dispatches:
 * bulk-transfer setup (cmd 0x08/0x09), lobby commands (0x5f),
 * unexpected-request handling, and queuing via
 * srv_QueueCommandForProcessing. Also services the admin connection at
 * 0x114ffe20.
 *
 * Byte-exact at the link (750/750 masked). Load-bearing shapes:
 *   - The slot walk starts at the named `g_connections` and compares against
 *     `(int) (g_connections + 8 * 0x264264)`. With a literal-address start
 *     the scheduler (c2 0x10727977) orders the pktbuf byte store after the
 *     unexpected-request `*conn` store, which then ties `push ebp` on
 *     priority and issues first on sequence. The `(int)` casts keep the
 *     signed `jl`.
 *   - cmd-3 arm: stores through conn, flag read and call through
 *     `header = pkt - 0x18`, no `volatile` (a volatile read orders the
 *     pushes behind it).
 *   - Scratch registers (eax/ecx/edx) come from c2's pick cursor
 *     (fcn.10721c0f), which advances once per picked temporary across the
 *     whole function; copies into a named variable's register do not
 *     advance it. The cmd-3 tail stores `*conn` directly and the memcpy
 *     addends are plain locals so the picks, and every later scratch
 *     register, land where the reference has them.
 *   - Download arm 8: both global stores plain and issued before the memset,
 *     so the rep stosd sinks below the two pushes.
 *   - The per-arm slot store `conn+0x1b = i` stops c2 hoisting the shared
 *     srv_QueueCommandForProcessing prefix.
 *   - Admin loop: one cached flag byte feeds both flag tests, and all three
 *     exits share one `xor eax,eax` epilogue. */


int __cdecl srv_LoadBuf(void)
{
	char logbuf_hi[256];
	char logbuf_lo[256];
	unsigned char pktbuf[156];
	int ret;
	unsigned int* conn;
	int i;
	unsigned int status;
	unsigned char admin_flags;

	for (i = 0, conn = (unsigned int*) g_connections; (int) conn < (int) (g_connections + 8 * 0x264264); conn = (unsigned int*) ((char*) conn + 0x264264), i++) {
		if ((*(unsigned char*) conn & 1) != 0) {
			do {
				ret = srv_ReceivePacketHeader(conn);
				if (ret == -1) {
					return -1;
				}
				status = *conn;
				if ((status & 0x80) == 0) {
					break;
				}
				if (status & 2) {
					unsigned char* pkt;
					unsigned int* header;
					/* Stores through conn, the 0x400 flag read and the call
					 * through header (pkt - 0x18): c2 keeps conn[1], both stores
					 * and the read on ebp, and cannot prove the read independent
					 * of the [ebp+0x2c] store, so it stays after it without
					 * `volatile`. A volatile read also orders the pushes behind
					 * it, which kept `push eax` out of cycle 0. */
					pkt = (unsigned char*) conn + 0x18;
					if (*pkt == 3) {
						status = conn[1];
						header = (unsigned int*) (pkt - 0x18);
						conn[0xb] = status;
						conn[0xc] = (*header & 0x400) ? 1 : 2;
						if (cm_QueuePlayerCommand(header, pkt) == -1) {
							return -1;
						}
					}
					/* Stored here rather than through `status`: the load is then
					 * a scratch pick (c2 fcn.10721c0f) instead of a copy into
					 * status's register, which advances the pick cursor once and
					 * gives the lobby sprintfs the reference's ecx/edx. */
					*conn = *conn & 0xffffff7d | 0x200;
					goto done_inner;
				}
				if (status & 0x200) {
					LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
					if (*(unsigned char*) (conn + 6) == 0x5f) {
						if (lb_ExLobbyServerCommand(conn, (int) ((unsigned char*) conn + 0x18)) == -1) {
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
						unsigned int total;
						total = conn[10];
						/* Both stores plain and issued before the memset: that is
						 * what lets msvc6 sink the rep stosd below the two pushes
						 * the way the original does. Making either store volatile,
						 * or moving the memset first, rotates the registers here
						 * and in the memcpy arm below. */
						g_download_total_size = total;
						g_download_received = 0;
						memset((void*) 0x101deac8, 0xff, 32);
						g_download_buffer = (unsigned int) m_AllocTracked(total, "srv_LoadBuf");
					}
					else if (*(unsigned char*) (conn + 6) == 9) {
						unsigned int rec;
						unsigned int buf;
						/* Both addends in plain locals, received first: the two
						 * loads are scratch picks (eax, ecx) ahead of the source
						 * lea, giving `lea edi,[ecx+eax]`, and they advance the
						 * pick cursor twice, which puts every later scratch
						 * register in the reference's order. Volatile locals made
						 * them non-advancing copies; inline reads load into edi
						 * and emit `add edi,ecx`. */
						rec = g_download_received;
						buf = g_download_buffer;
						memcpy((void*) (buf + rec), conn + 10, 0x80);
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
				/* The slot store is duplicated per arm rather than issued once
				 * above the test: that is what stops msvc6 hoisting the shared
				 * srv_QueueCommandForProcessing prefix, so each arm keeps the
				 * original's own `mov [ebp+0x1b],bl` / `lea` / `push` / `call`. */
				if (status & 0x10) {
					*((unsigned char*) conn + 0x1b) = (unsigned char) i;
					if (srv_QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
						return -1;
					}
					status = *conn & 0xffffff6f;
					goto set_status;
				}
				*((unsigned char*) conn + 0x1b) = (unsigned char) i;
				if (srv_QueueCommandForProcessing(conn, (unsigned char*) (conn + 6)) != 0) {
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

	/* One byte load feeds both flag tests: the original checks 0x80 before
	 * looping back on bit 0, so the loop condition is re-tested at the bottom
	 * off the same `mov al`. All three exits of this loop share the single
	 * `xor eax,eax` epilogue below. */
	while ((*(unsigned char*) 0x114ffe20 & 1) != 0) {
		if (srv_ReceivePacketHeader((unsigned int*) 0x114ffe20) == -1) {
			goto done;
		}
		admin_flags = *(unsigned char*) 0x114ffe20;
		if ((admin_flags & 0x80) != 0) {
			pktbuf[0] = 2;
			cm_QueuePlayerCommand((unsigned int*) 0x114ffe20, pktbuf);
			cm_ClosePlayerConnection((unsigned int*) 0x114ffe20);
			goto done;
		}
	}
done:
	return 0;
}
