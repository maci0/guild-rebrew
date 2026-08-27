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

// FUNCTION: SERVER 0x1000ad40
// LogWinsockError

void __cdecl LogWinsockError(int err_code)
{
	char buf[256];

	switch (err_code) {
	case 0x276d:
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x769, "WSANOTINITIALISED", 1);
		return;
	case 0x2742:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76b,
			"WSAENETDOWN: The network subsystem has failed!",
			1
		);
		return;
	case 0x271e:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76d,
			"WSAEFAULT: The buf parameter is not completely contained in a valid part of the user address space",
			1
		);
		return;
	case 0x2749:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x76f,
			"WSAENOTCONN: The socket is not connected.",
			1
		);
		return;
	case 0x2714:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x771,
			"WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.",
			1
		);
		return;
	case 0x2734:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x773,
			"WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still "
			"processing a callback function.",
			1
		);
		return;
	case 0x2744:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x775,
			"WSAENETRESET: The connection has been broken due to the keep-alive activity detecting a failure while the "
			"operation was in progress.",
			1
		);
		return;
	case 0x2736:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x777,
			"WSAENOTSOCK: The descriptor is not a socket.",
			1
		);
		return;
	case 0x273d:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x779,
			"WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB "
			"data is not supported in the communication domain associated with this socket, or the socket is "
			"unidirectional and supports only send operations.",
			1
		);
		return;
	case 0x274a:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77b,
			"WSAESHUTDOWN: The socket has been shut down; it is not possible to receive on a socket after shutdown has "
			"been invoked with how set to SD_RECEIVE or SD_BOTH.",
			1
		);
		return;
	case 0x2733:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77d,
			"WSAEWOULDBLOCK: The socket is marked as nonblocking and the receive operation would block.",
			1
		);
		return;
	case 0x2738:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x77f,
			"WSAEMSGSIZE: The message was too large to fit into the specified buffer and was truncated.",
			1
		);
		return;
	case 0x2726:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x781,
			"WSAEINVAL: The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was "
			"specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or "
			"negative.",
			1
		);
		return;
	case 0x2745:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x783,
			"WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other failure. The application "
			"should close the socket as it is no longer usable.",
			1
		);
		return;
	case 0x274c:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x785,
			"WSAETIMEDOUT: The connection has been dropped because of a network failure or because the peer system "
			"failed to respond.",
			1
		);
		return;
	case 0x2746:
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOnServer\\server.c",
			0x787,
			"WSAECONNRESET: The virtual circuit was reset by the remote side executing a hard or abortive close. The "
			"application should close the socket as it is no longer usable. On a UPD-datagram socket this error would "
			"indicate that a previous send operation resulted in an ICMP >Port Unreachable< message.",
			1
		);
		return;
	default:
		sprintf(buf, "Unbekannter WinsockError %d", err_code);
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x789, buf, 1);
		return;
	}
}

/* Initializes the building type lookup table (42 entries, 0x18 bytes
 * each, base g_office_slots = 0x101de5a0). Zeroes the table, stamps
 * id=i / unk=-1 / unk2=-1 per entry, then assigns each entry's type code
 * (bytes at +0x8) from the 1,1,2,3,4,4,5,6,7,7,... sequence.
 *
 * STATUS: PROVEN (semantic proof, byte-blocked). The target's leading
 * memset uses the dest-alignment prelude (lea ecx,[edi+edi*2]; and ecx,3;
 * sub ebx,ecx; jle; rep stosb/stosd/stosb) with the count spilled to
 * [ebp-4] and an ebp frame. No C formulation or flag/toolchain
 * combination (msvc4.0-7.0, SP1-SP6, ~45 shapes, 96-flag sweep)
 * reproduces it — msvc6 always emits `mov ecx,0xfc; rep stosd` for the
 * constant count, so the function compiles to 334B (261/372 matching);
 * everything after the memset (loop + 42 constant stores with their
 * mov al,N grouping) is byte-identical. See docs/msvc6-allocator.md
 * "m_PoolAlloc / InitBuildingTypeTable — blocked (alignment-prefixed
 * memset)".
 *
 * Re-verified 2026-08-27: ~130 further probes (base 6.0 + SP1-SP6 ×
 * /Og- /Oi /Oy- /O1 /Ox /G6, param-operand and struct-copy memsets,
 * volatile/address-taken counts and dests, full-function bodies through
 * `rebrew test`) confirm 261/372 / 334B is the ceiling — every variant
 * compiles to the plain dword+tail memset. The prelude appears in the
 * target only when the count is memory-resident; msvc6's inliner emits
 * the plain form for any C shape.
 *
 * Promoted to PROVEN via `rebrew prove 0x1000b040` (2026-08-27) with
 * 252 --watch-va (every dword of the 0x3f0-byte table) and
 * --loop-bound 400: for void functions the prover skips the EAX/EDX
 * comparison (undefined at exit) and compares only the watched memory;
 * the DIR32 patch preserves each operand's addend (symbol_va + addend)
 * and no longer writes compiled offsets into the original blob. The
 * high loop bound is required because angr's LoopSeer counts each
 * rep-stosd iteration — the memset alone is 252 iterations. */

extern char g_office_slots[];

// FUNCTION: SERVER 0x1000b040
// InitBuildingTypeTable

void __cdecl InitBuildingTypeTable(void)
{
	char* p;
	int i;

	memset(g_office_slots, 0, 0x3f0);
	i = 0;
	p = g_office_slots + 4;
	do {
		*(p - 4) = (char) i;
		*(int*) p = -1;
		*(int*) (p + 0x10) = -1;
		p += 0x18;
		i++;
	} while ((int) p < (int) (g_office_slots + 0x3f4));

	*(unsigned char*) (g_office_slots + 0x8) = 0x1;
	*(unsigned char*) (g_office_slots + 0x20) = 0x1;
	*(unsigned char*) (g_office_slots + 0x38) = 0x2;
	*(unsigned char*) (g_office_slots + 0x50) = 0x3;
	*(unsigned char*) (g_office_slots + 0x68) = 0x4;
	*(unsigned char*) (g_office_slots + 0x80) = 0x4;
	*(unsigned char*) (g_office_slots + 0x98) = 0x5;
	*(unsigned char*) (g_office_slots + 0xb0) = 0x6;
	*(unsigned char*) (g_office_slots + 0xc8) = 0x7;
	*(unsigned char*) (g_office_slots + 0xe0) = 0x7;
	*(unsigned char*) (g_office_slots + 0xf8) = 0x8;
	*(unsigned char*) (g_office_slots + 0x110) = 0x9;
	*(unsigned char*) (g_office_slots + 0x128) = 0xa;
	*(unsigned char*) (g_office_slots + 0x140) = 0xb;
	*(unsigned char*) (g_office_slots + 0x158) = 0xc;
	*(unsigned char*) (g_office_slots + 0x170) = 0xd;
	*(unsigned char*) (g_office_slots + 0x188) = 0xe;
	*(unsigned char*) (g_office_slots + 0x1a0) = 0xf;
	*(unsigned char*) (g_office_slots + 0x1b8) = 0x10;
	*(unsigned char*) (g_office_slots + 0x1d0) = 0x11;
	*(unsigned char*) (g_office_slots + 0x1e8) = 0x12;
	*(unsigned char*) (g_office_slots + 0x200) = 0x13;
	*(unsigned char*) (g_office_slots + 0x218) = 0x14;
	*(unsigned char*) (g_office_slots + 0x230) = 0x15;
	*(unsigned char*) (g_office_slots + 0x248) = 0x16;
	*(unsigned char*) (g_office_slots + 0x260) = 0x17;
	*(unsigned char*) (g_office_slots + 0x278) = 0x18;
	*(unsigned char*) (g_office_slots + 0x290) = 0x19;
	*(unsigned char*) (g_office_slots + 0x2a8) = 0x1a;
	*(unsigned char*) (g_office_slots + 0x2c0) = 0x1b;
	*(unsigned char*) (g_office_slots + 0x2d8) = 0x1c;
	*(unsigned char*) (g_office_slots + 0x2f0) = 0x1d;
	*(unsigned char*) (g_office_slots + 0x308) = 0x1e;
	*(unsigned char*) (g_office_slots + 0x320) = 0x1f;
	*(unsigned char*) (g_office_slots + 0x338) = 0x20;
	*(unsigned char*) (g_office_slots + 0x350) = 0x21;
	*(unsigned char*) (g_office_slots + 0x368) = 0x22;
	*(unsigned char*) (g_office_slots + 0x380) = 0x23;
	*(unsigned char*) (g_office_slots + 0x398) = 0x24;
	*(unsigned char*) (g_office_slots + 0x3b0) = 0x25;
	*(unsigned char*) (g_office_slots + 0x3c8) = 0x26;
	*(unsigned char*) (g_office_slots + 0x3e0) = 0x27;
}
extern unsigned int g_player_slot_0;
extern int g_save_version[4];
extern int g_1002dde0[4];
char g_1002a0f8[1] = {
    0x61,
};
