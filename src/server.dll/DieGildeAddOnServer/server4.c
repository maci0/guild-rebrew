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

/* Initializes the building type lookup table. Loads building
 * definitions (costs, capacities, upgrade paths) from game
 * data into the runtime type table. */

extern char g_office_slots[];

// FUNCTION: SERVER 0x1000b040
// InitBuildingTypeTable

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000b040.
// Alignment-memset table init (Finding 19) — no C conversion attempted; fenced-naked.
__declspec(naked) void InitBuildingTypeTable(void)
{
	__asm {
		push ebp
		mov ebp, esp
		push ecx
		push ebx
		push edi
		mov dword ptr [ebp - 4], 0x3f0
		mov edi, offset g_office_slots
		mov ebx, dword ptr [ebp - 4]
		xor eax, eax
		lea ecx, [edi + edi*2]
		and ecx, 3
		sub ebx, ecx
		jle L_after_stos
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L_after_stos:
		add ecx, ebx
		rep stosb
		xor ecx, ecx
		pop edi
		mov eax, offset g_office_slots + 4
		or edx, 0xffffffff
		pop ebx
	L_loop_init:
		mov byte ptr [eax - 4], cl
		mov dword ptr [eax], edx
		mov dword ptr [eax + 0x10], edx
		add eax, 0x18
		inc ecx
		cmp eax, offset g_office_slots + 0x3f4
		jl L_loop_init
		mov al, 1
		mov byte ptr [g_office_slots + 0x38], 2
		mov byte ptr [g_office_slots + 0x8], al
		mov byte ptr [g_office_slots + 0x20], al
		mov al, 4
		mov byte ptr [g_office_slots + 0x50], 3
		mov byte ptr [g_office_slots + 0x68], al
		mov byte ptr [g_office_slots + 0x80], al
		mov al, 7
		mov byte ptr [g_office_slots + 0x98], 5
		mov byte ptr [g_office_slots + 0xb0], 6
		mov byte ptr [g_office_slots + 0xc8], al
		mov byte ptr [g_office_slots + 0xe0], al
		mov byte ptr [g_office_slots + 0xf8], 8
		mov byte ptr [g_office_slots + 0x110], 9
		mov byte ptr [g_office_slots + 0x128], 0xa
		mov byte ptr [g_office_slots + 0x140], 0xb
		mov byte ptr [g_office_slots + 0x158], 0xc
		mov byte ptr [g_office_slots + 0x170], 0xd
		mov byte ptr [g_office_slots + 0x188], 0xe
		mov byte ptr [g_office_slots + 0x1a0], 0xf
		mov byte ptr [g_office_slots + 0x1b8], 0x10
		mov byte ptr [g_office_slots + 0x1d0], 0x11
		mov byte ptr [g_office_slots + 0x1e8], 0x12
		mov byte ptr [g_office_slots + 0x200], 0x13
		mov byte ptr [g_office_slots + 0x218], 0x14
		mov byte ptr [g_office_slots + 0x230], 0x15
		mov byte ptr [g_office_slots + 0x248], 0x16
		mov byte ptr [g_office_slots + 0x260], 0x17
		mov byte ptr [g_office_slots + 0x278], 0x18
		mov byte ptr [g_office_slots + 0x290], 0x19
		mov byte ptr [g_office_slots + 0x2a8], 0x1a
		mov byte ptr [g_office_slots + 0x2c0], 0x1b
		mov byte ptr [g_office_slots + 0x2d8], 0x1c
		mov byte ptr [g_office_slots + 0x2f0], 0x1d
		mov byte ptr [g_office_slots + 0x308], 0x1e
		mov byte ptr [g_office_slots + 0x320], 0x1f
		mov byte ptr [g_office_slots + 0x338], 0x20
		mov byte ptr [g_office_slots + 0x350], 0x21
		mov byte ptr [g_office_slots + 0x368], 0x22
		mov byte ptr [g_office_slots + 0x380], 0x23
		mov byte ptr [g_office_slots + 0x398], 0x24
		mov byte ptr [g_office_slots + 0x3b0], 0x25
		mov byte ptr [g_office_slots + 0x3c8], 0x26
		mov byte ptr [g_office_slots + 0x3e0], 0x27
		mov esp, ebp
		pop ebp
		ret
	}
}
#else
void InitBuildingTypeTable(void)
{
	/* C fallback (no byte-matching conversion; alignment-memset init,
	 * Finding 19). */
}
#endif
extern unsigned int g_player_slot_0;
extern int g_save_version[4];
extern int g_1002dde0[4];
char g_1002a0f8[1] = {
    0x61,
};
