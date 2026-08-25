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

// FUNCTION: SERVER 0x10009d30
// srv_Init

__declspec(naked) int __cdecl srv_Init(void)
{
	__asm {
		sub esp, 0x504
		push ebx
		push esi
		push edi
		_emit 0xff
		_emit 0x15
		_emit 0x6c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 2
		push eax
		_emit 0xff
		_emit 0x15
		_emit 0x68
		_emit 0x40
		_emit 0x02
		_emit 0x10
		push 3
		push 0
		push 0
		push 0x1000a010
		call InitializeLogAndErrorHandler
		push 0x7fa6
		call InitPacketPool
		mov edi, 0x10029594
		or ecx, 0xffffffff
		xor eax, eax
		lea edx, [esp + 0x20]
		repne scasb
		not ecx
		sub edi, ecx
		mov eax, ecx
		mov esi, edi
		mov edi, edx
		lea edx, [esp + 0x20]
		shr ecx, 2
		rep movsd
		mov ecx, eax
		xor eax, eax
		and ecx, 3
		rep movsb
		mov edi, 0x10029998
		or ecx, 0xffffffff
		repne scasb
		not ecx
		sub edi, ecx
		mov esi, edi
		mov ebx, ecx
		mov edi, edx
		or ecx, 0xffffffff
		repne scasb
		mov ecx, ebx
		dec edi
		shr ecx, 2
		rep movsd
		mov ecx, ebx
		lea eax, [esp + 0x20]
		and ecx, 3
		push eax
		rep movsb
		call gm_Open
		add esp, 0x18
		test eax, eax
		pop edi
		pop esi
		pop ebx
		jge L_gm_ok
		_emit 0x8d
		_emit 0x4c
		_emit 0x24
		_emit 0x00
		lea edx, [esp + 0x104]
		push ecx
		push 0x10029974
		push edx
		call sprintf
		lea eax, [esp + 0x110]
		push 1
		push eax
		push 0x3cd
		push 0x100298b0
		call LogMessageInternal
		add esp, 0x1c
		add esp, 1284
		ret
	L_gm_ok:
		call gm_InitEntitySlots
		call InitBuildingTypeTable
		_emit 0x8b
		_emit 0x0d
		_emit 0x88
		_emit 0x40
		_emit 0x76
		_emit 0x11
		push ecx
		call CreateListenSocket
		add esp, 4
		cmp eax, -1
		_emit 0xa3
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		jne L_socket_ok
		push 1
		push 0x10029948
		push 0x3db
		push 0x100298b0
		call LogMessageInternal
		add esp, 0x10
		add esp, 1284
		ret
	L_socket_ok:
		_emit 0xc7
		_emit 0x05
		_emit 0x90
		_emit 0x40
		_emit 0x76
		_emit 0x11
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		add esp, 1284
		ret
	}
}

/* Creates the TCP listen socket for accepting client
 * connections. Calls WSAStartup, socket(), bind(), listen(). */

// FUNCTION: SERVER 0x10009e60
// CreateListenSocket

/* WSAStartup = 0x10024178, WSACleanup = 0x1002417c */
/* socket = 0x10024180, setsockopt = 0x10024184, ioctlsocket = 0x1002416c */
/* htons = 0x1002418c, bind = 0x10024190, listen = 0x10024160 */
/* closesocket = 0x10024198, shutdown = 0x10024174 */

// DATA: SERVER 0x101deb14
extern unsigned int g_player_slot_field;

// SIZE 0x10 — struct sockaddr_in (Winsock system struct)
int __cdecl CreateListenSocket(int port)
{
	char wsadata[0x190];
	int optval;
	struct sockaddr_in addr;
	int sock;

	/* init player slot flags */
	{
		unsigned int* p = &g_player_slot_field;
		do {
			*(int*) ((char*) p - 0x14) = 0;
			*p = 0xFFFFFFFF;
			p = (unsigned int*) ((char*) p + 0x264264);
		} while ((int) p < 0x114ffe34);
	}

	WSAStartup(0x101, (WSADATA*) wsadata);

	sock = socket(2, 1, 6);
	if (sock == -1) {
		goto cleanup_wsa;
	}

	/* SO_REUSEADDR */
	optval = 1;
	if (setsockopt(sock, 0xFFFF, 4, (const char*) &optval, 4) == -1) {
		goto close_sock;
	}

	/* SO_LINGER */
	optval = 1;
	if (setsockopt(sock, 0xFFFF, 0xFFFFFF7F, (const char*) &optval, 4) == -1) {
		goto close_sock;
	}

	/* SO_SNDBUF */
	optval = 0x20000;
	if (setsockopt(sock, 0xFFFF, 0x1002, (const char*) &optval, 4) == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x424, "Can't set SO_SNDBUF on Socket", 1);
		goto close_sock;
	}

	/* SO_RCVBUF */
	optval = 0x20000;
	if (setsockopt(sock, 0xFFFF, 0x1001, (const char*) &optval, 4) == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x42b, "Can't set SO_RCVBUF on Socket", 1);
		goto close_sock;
	}

	/* FIONBIO */
	optval = 1;
	if (ioctlsocket(sock, 0x8004667E, (unsigned int*) &optval) == -1) {
		goto close_sock;
	}

	/* bind */
	addr.sin_family = 2;
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons((unsigned short) port);
	if (bind(sock, (const struct sockaddr*) &addr, 16) == -1) {
		goto close_sock;
	}

	/* listen */
	if (listen(sock, 5) == -1) {
		goto close_sock;
	}

	return sock;

close_sock:
	shutdown(sock, 2);
	closesocket(sock);

cleanup_wsa:
	WSACleanup();
	return -1;
}

/* Cleans up all network sockets. Closes client connections,
 * the listen socket, and calls WSACleanup. */

// FUNCTION: SERVER 0x1000A010
// CleanupSockets

void __cdecl CleanupSockets(void)
{
	int p;
	p = 0x101deb14;
	while (p < 0x114ffe34) {
		if (*(int*) (p - 0x14)) {
			shutdown(*(int*) p, 2);
			closesocket(*(int*) p);
		}
		p += 0x264264;
	}
	shutdown(g_net_socket, 2);
	closesocket(g_net_socket);
	WSACleanup();
	gm_InitEntitySlots();
	gm_ResetAllEntities();
	gm_CleanupObjectEntities();
	gm_CleanupAllEntities();
	ShutdownMemoryAllocator();
	ShutdownLogAndErrorHandler();
}

/* Accepts new client connections using select() + accept().
 * Assigns connected clients to player slots and configures
 * socket options (TCP_NODELAY, timeouts). */

// FUNCTION: SERVER 0x1000a080
// AcceptConnections

/* accept = 0x1002415c, setsockopt = 0x10024184, GetTickCount = 0x1002405c */

// DATA: SERVER 0x101deaec

// DATA: SERVER 0x101deb00

// DATA: SERVER 0x114ffe20

// DATA: SERVER 0x1003467c

char s_No_more_Slots_for_new_Connection_100299c8[] = "No more Slots for new Connections!\n";
char s_D__Develop_DieGildeAddOnServer_s_100298b0[] = "D:\\Develop\\DieGildeAddOnServer\\server.c";
char s_New_Connection_from__li__li__li__100299a0[] = "New Connection from %li.%li.%li.%li\n";
extern int __cdecl sprintf(char*, const char*, ...);

__declspec(naked) int __cdecl AcceptConnections(void)
{
	__asm {
		_emit 0xa1
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		sub esp, 0x118
		cmp eax, -1
		push ebx
		push ebp
		push esi
		jne L_have_socket
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 0x118
		ret
	L_have_socket:
		xor ebp, ebp
		mov eax, 0x101deb00
	L_find_loop:
		cmp dword ptr [eax], 0
		je L_found_slot
		add eax, 0x264264
		inc ebp
		cmp eax, 0x114ffe20
		jge L_no_slots
		jmp L_find_loop
	L_found_slot:
		mov eax, ebp
		shl eax, 4
		add eax, ebp
		shl eax, 8
		add eax, ebp
		shl eax, 4
		add eax, ebp
		lea eax, [eax + eax*8]
		lea esi, [eax*4 + 0x101deb00]
		test esi, esi
		jne L_do_accept
	L_no_slots:
		push 1
		push offset s_No_more_Slots_for_new_Connection_100299c8
		push 0x495
		push offset s_D__Develop_DieGildeAddOnServer_s_100298b0
		call LogMessageInternal
		_emit 0xa1
		_emit 0x20
		_emit 0xfe
		_emit 0x4f
		_emit 0x11
		add esp, 0x10
		test eax, eax
		jne L_ret_neg1
		mov esi, 0x114ffe20
	L_do_accept:
		_emit 0xa1
		_emit 0xec
		_emit 0xea
		_emit 0x1d
		_emit 0x10
		lea ecx, [esp + 0x10]
		lea edx, [esp + 0x14]
		push ecx
		push edx
		push eax
		mov dword ptr [esp + 0x1c], 0x10
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x41
		_emit 0x02
		_emit 0x10
		mov ebx, eax
		cmp ebx, -1
		jne L_have_new_socket
	L_ret_neg1:
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 0x118
		ret
	L_have_new_socket:
		push edi
		_emit 0x8b
		_emit 0x3d
		_emit 0x84
		_emit 0x41
		_emit 0x02
		_emit 0x10
		lea ecx, [esp + 0x10]
		push 4
		push ecx
		push 0x1002
		push 0xffff
		push ebx
		mov dword ptr [esp + 0x24], 0x10000
		call edi
		lea edx, [esp + 0x10]
		push 4
		push edx
		push 0x1001
		push 0xffff
		push ebx
		mov dword ptr [esp + 0x24], 0x10000
		call edi
		_emit 0xa1
		_emit 0x7c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		lea edx, [esi + 0x26420c]
		inc eax
		mov ecx, 0x15
		_emit 0xa3
		_emit 0x7c
		_emit 0x46
		_emit 0x03
		_emit 0x10
		mov dword ptr [esi + 4], eax
		xor eax, eax
		mov edi, edx
		mov dword ptr [esi], 0x2103
		rep stosd
		stosw
		stosb
		mov eax, dword ptr [esi + 4]
		xor edi, edi
		cmp ebp, edi
		mov dword ptr [edx], eax
		jne L_skip_or400
		mov eax, dword ptr [esi]
		or ah, 4
		mov dword ptr [esi], eax
	L_skip_or400:
		mov dword ptr [esi + 0x14], ebx
		mov word ptr [esi + 0x14a], di
		mov word ptr [esi + 0x14c], di
		mov word ptr [esi + 0x14e], 0x19
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		add eax, 0x493e0
		xor ecx, ecx
		mov dword ptr [esi + 0x150], eax
	L_init_loop:
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		lea edx, [esi + eax*8]
		add eax, edx
		cmp ecx, edi
		mov byte ptr [eax + 0x154], 0
		mov byte ptr [eax + 0x132154], 0
		jne L_not_first
		mov dword ptr [esi + 0x1e5], edi
		mov dword ptr [esi + 0x1321e5], edi
		jmp L_set_e9
	L_not_first:
		lea edx, [eax + 0xbb]
		cmp ecx, 0x1fff
		mov dword ptr [eax + 0x1e5], edx
		lea edx, [eax + 0x1320bb]
		mov dword ptr [eax + 0x1321e5], edx
		jge L_set_e9_zero
	L_set_e9:
		lea edx, [eax + 0x1ed]
		mov dword ptr [eax + 0x1e9], edx
		lea edx, [eax + 0x1321ed]
		mov dword ptr [eax + 0x1321e9], edx
		jmp L_init_next
	L_set_e9_zero:
		mov dword ptr [eax + 0x1e9], edi
		mov dword ptr [eax + 0x1321e9], edi
	L_init_next:
		inc ecx
		cmp ecx, 0x2000
		jl L_init_loop
		mov edx, dword ptr [esp + 0x1f]
		lea eax, [esi + 0x154]
		lea ecx, [esi + 0x132154]
		mov dword ptr [esi + 0x2641f8], eax
		mov eax, dword ptr [esp + 0x1e]
		and edx, 0xff
		mov dword ptr [esi + 0x2641fc], ecx
		mov ecx, dword ptr [esp + 0x1d]
		push edx
		mov edx, dword ptr [esp + 0x20]
		and eax, 0xff
		and ecx, 0xff
		push eax
		and edx, 0xff
		push ecx
		push edx
		lea eax, [esp + 0x38]
		push offset s_New_Connection_from__li__li__li__100299a0
		push eax
		mov dword ptr [esi + 0x2641f0], edi
		mov dword ptr [esi + 0x2641f4], edi
		call sprintf
		lea ecx, [esp + 0x40]
		push 1
		push ecx
		push 0x4e1
		push offset s_D__Develop_DieGildeAddOnServer_s_100298b0
		call LogMessageInternal
		add esp, 0x28
		mov eax, ebx
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x118
		ret
	}
}

/* Closes a specific player's network connection. Shuts down
 * the socket, clears the player slot, and broadcasts the
 * disconnect to other players. */

// FUNCTION: SERVER 0x1000a2e0
// cm_ClosePlayerConnection

int __cdecl cm_ClosePlayerConnection(unsigned int* player_slot)
{
	shutdown(player_slot[5], 2);
	closesocket(player_slot[5]);
	*player_slot = 0;
	player_slot[5] = 0xffffffff;
	player_slot[1] = 0;
	memset((char*) player_slot + 0x26420c, 0, 87);
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x500, "Connection dropped.\n", 1);
	return 0;
}

/* Receives a packet header from a client socket. Reads the
 * fixed-size header, validates it, and returns the packet
 * size. Handles partial reads and disconnects. */

// FUNCTION: SERVER 0x1000a340
// ReceivePacketHeader

/* recv = 0x10024168, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */

__declspec(naked) int __cdecl ReceivePacketHeader(unsigned int* conn)
{
	(void) conn;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		push edi
		test byte ptr [esi], 0x80
		jne near L_ret0
		mov ax, word ptr [esi + 0x14a]
		_emit 0x8b
		_emit 0x3d
		_emit 0x68
		_emit 0x41
		_emit 0x02
		_emit 0x10
		cmp ax, 3
		jae L_load_eax_arg
		and eax, 0xffff
		mov ecx, 3
		sub ecx, eax
		push 0
		lea edx, [eax + esi + 0x18]
		mov eax, dword ptr [esi + 0x14]
		push ecx
		push edx
		push eax
		call edi
		test eax, eax
		jne L_after_recv1
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		cmp dword ptr [esi + 0x150], eax
		jae near L_ret0
		push 1
		push 0x10029a04
		push 0x52a
		push 0x100298b0
		call LogMessageInternal
		push esi
		call cm_ClosePlayerConnection
		add esp, 0x14
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_after_recv1:
		cmp eax, -1
		jne L_add_and_check
		jmp L_wsa_err
	L_load_eax_arg:
		mov eax, dword ptr [esp + 0xc]
	L_add_and_check:
		add word ptr [esi + 0x14a], ax
		mov ax, word ptr [esi + 0x14a]
		cmp ax, 3
		jb near L_ret0
		xor ecx, ecx
		and eax, 0xffff
		mov cx, word ptr [esi + 0x19]
		push 0
		sub ecx, eax
		lea edx, [eax + esi + 0x18]
		mov eax, dword ptr [esi + 0x14]
		push ecx
		push edx
		push eax
		call edi
		test eax, eax
		jne L_after_recv2
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		cmp dword ptr [esi + 0x150], eax
		jae near L_ret0
		push 1
		push 0x10029a04
		push 0x552
		push 0x100298b0
		call LogMessageInternal
		push esi
		call cm_ClosePlayerConnection
		add esp, 0x14
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_after_recv2:
		cmp eax, -1
		jne L_success
	L_wsa_err:
		_emit 0xff
		_emit 0x15
		_emit 0x70
		_emit 0x41
		_emit 0x02
		_emit 0x10
		cmp eax, 0x2733
		je L_ret0
		push eax
		call LogWinsockError
		push esi
		call cm_ClosePlayerConnection
		add esp, 8
		or eax, 0xffffffff
		pop edi
		pop esi
		ret
	L_success:
		add word ptr [esi + 0x14a], ax
		_emit 0xff
		_emit 0x15
		_emit 0x5c
		_emit 0x40
		_emit 0x02
		_emit 0x10
		mov cx, word ptr [esi + 0x14a]
		add eax, 0x493e0
		cmp cx, word ptr [esi + 0x19]
		mov dword ptr [esi + 0x150], eax
		jne L_ret0
		mov eax, dword ptr [esi]
		mov word ptr [esi + 0x14a], 0
		or al, 0x80
		mov dword ptr [esi], eax
	L_ret0:
		pop edi
		xor eax, eax
		pop esi
		ret
	}
}

/* Sends queued data to a client socket. Transmits buffered
 * outgoing packets with retry logic for partial sends. */

// FUNCTION: SERVER 0x1000a490
// SendPlayerData

/* send = 0x10024164, GetTickCount = 0x1002405c, WSAGetLastError = 0x10024170 */

int __cdecl SendPlayerData(unsigned int* conn)
{
	int result;
	unsigned int tick;

	if (conn[0] & 0x100) {
		return 0;
	}

	result = send(
		conn[5],
		(const char*) conn + 0xb1 + *(unsigned short*) ((char*) conn + 0x14c),
		*(unsigned short*) ((char*) conn + 0xb2) - *(unsigned short*) ((char*) conn + 0x14c),
		0
	);

	if (result == 0) {
		tick = GetTickCount();
		if (conn[84] < tick) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x58f, "Connection timed out.", 1);
			cm_ClosePlayerConnection(conn);
			return -1;
		}
	}
	else if (result == -1) {
		if (WSAGetLastError() == 0x2733) {
			return 0;
		}
		cm_ClosePlayerConnection(conn);
		return -1;
	}
	else if (result > 0) {
		*(unsigned short*) ((char*) conn + 0x14c) += (unsigned short) result;
		tick = GetTickCount();
		*(unsigned int*) ((char*) conn + 0x150) = tick + 0x493e0;
		if (*(unsigned short*) ((char*) conn + 0x14c) == *(unsigned short*) ((char*) conn + 0xb2)) {
			conn[0] = conn[0];
			*(unsigned short*) ((char*) conn + 0x14c) = 0;
			conn[0] |= 0x100;
		}
	}

	return 0;
}

/* Processes received network data from all connected clients.
 * Reads incoming packets, reassembles fragmented data, and
 * dispatches complete commands for processing. */

// DATA: SERVER 0x101deac0
// DATA: SERVER 0x101deac4
// DATA: SERVER 0x101deac8
extern unsigned int g_download_slots[8];
// DATA: SERVER 0x101deae8

