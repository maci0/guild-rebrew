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
extern int g_handler_started;
void __cdecl InitBuildingTypeTable(void);
int __cdecl srv_Init(void);
void __cdecl ShutdownMemoryAllocator();
int __cdecl gm_Open(char*);
int __cdecl CreateListenSocket(int port);
void __cdecl InitPacketPool(int);
extern int g_net_socket;
int __cdecl QueueCommandForProcessing(unsigned int* conn, unsigned char* pkt); /* 0x1000a8f0 */
int __cdecl SendPlayerData(unsigned int*);
void __cdecl FreeCommandBuffer(unsigned int*, int);
int GetCommandPayloadSize(unsigned char* cmd_payload);
extern handler_func g_dispatch_table[]; /* 0x1002c3f8 */
extern unsigned char g_connections[]; /* 0x101deb00 */
extern int g_connection_counter; /* 0x1003467c */
/* Console control handler for graceful shutdown.
 * Handles Ctrl+C and close events. Always returns 0. */

// FUNCTION: SERVER 0x10009d30
// srv_Init

int __cdecl srv_Init(void)
{
	char path[0x104];
	char msg[0x400];
	void* hThread;

	hThread = GetCurrentThread();
	SetThreadPriority(hThread, 2);
	((int (__cdecl*)(void*, int, int, int)) InitializeLogAndErrorHandler)((void*) CleanupSockets, 0, 0, 3);
	InitPacketPool(0x7fa6);
	strcpy(path, (char*) 0x10029594);
	strcat(path, (char*) 0x10029998);
	if (gm_Open(path) < 0) {
		sprintf(msg, "Could not open gamefiles path:%s", path);
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x3cd, msg, 1);
		goto srv_done;
	}
	gm_InitEntitySlots();
	InitBuildingTypeTable();
	g_net_socket = CreateListenSocket(*(int*) 0x11764088);
	if (g_net_socket == -1) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x3db, "***ERROR: Initialization of Socket failed!\n", 1);
		goto srv_done;
	}
	*(int*) 0x11764090 = 0;
srv_done:
	;
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

/* RELOC 600/600 (2026-09-07).

 * Two scheduling fixes close the prior 570/600 form:

 * 1. Head store-before-memset: MSVC6 sinks `*(int*)slot = 0x2103` past the
 * non-aliasing memset. Writing through
 * `dst + ((char*)slot - dst)` with `dst = slot + 0x26420c` keeps the
 * `[esi]` encoding and forces the store ahead of `rep stos`
 * (570 -> 588). Plain `*(int*)slot`, volatile, comma-in-memset, and
 * `dst - 0x26420c` either sink or emit `[edx-imm]` (size crash).

 * 2. Tail zero stores: with the head alias in place, non-volatile
 * `*(unsigned int*)(slot + 0x2641f0/f4) = 0` *before* sprintf sinks to
 * between the last argument push and the call (588 -> 600 RELOC).
 * Volatile after sprintf left them after the call (588); volatile or
 * comma-before/above sprintf reordered the pointer/byte cluster (519).

 * Folded fallback `0x101deb00 + 8 * 0x264264` kept; literal `0x114ffe20`
 * with the dst head reopened the sprintf cluster (546).
 */

// DATA: SERVER 0x101deaec

// DATA: SERVER 0x101deb00

// DATA: SERVER 0x114ffe20

// DATA: SERVER 0x1003467c

char s_No_more_Slots_for_new_Connection_100299c8[] = "No more Slots for new Connections!\n";
char s_D__Develop_DieGildeAddOnServer_s_100298b0[] = "D:\\Develop\\DieGildeAddOnServer\\server.c";
char s_New_Connection_from__li__li__li__100299a0[] = "New Connection from %li.%li.%li.%li\n";
extern int __cdecl sprintf(char*, const char*, ...);

int __cdecl AcceptConnections(void)
{
	int optval;
	int addrlen;
	struct sockaddr addr;
	char msg[0x100];
	int p;
	unsigned char* slot;
	int sock;
	int i;

	if (g_net_socket == -1)
		return -1;

	i = 0;
	p = 0x101deb00;
	while (1) {
		if (*(int*) p == 0)
			break;
		p += 0x264264;
		i++;
		if (p >= 0x114ffe20)
			goto no_slots;
	}
	slot = (unsigned char*) 0x101deb00 + i * 0x264264;
	if (slot != 0)
		goto do_accept;

no_slots:
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x495, s_No_more_Slots_for_new_Connection_100299c8, 1);
	if (*(int*) 0x114ffe20 != 0)
		goto ret_neg1;
	slot = (unsigned char*) 0x101deb00 + 8 * 0x264264;

do_accept:
	addrlen = 16;
	sock = accept(g_net_socket, &addr, &addrlen);
	if (sock == -1)
		goto ret_neg1;

	{
		int (__stdcall* setopt)(unsigned int, int, int, const char*, int) = setsockopt;
		optval = 0x10000;
		setopt(sock, 0xffff, 0x1002, (const char*) &optval, 4);
		optval = 0x10000;
		setopt(sock, 0xffff, 0x1001, (const char*) &optval, 4);
	}

	g_connection_counter = g_connection_counter + 1;
	*(int*) (slot + 4) = g_connection_counter;
	{
		char* dst = (char*) (slot + 0x26420c);
		*(int*) (dst + ((char*) slot - dst)) = 0x2103;
		memset(dst, 0, 0x57);
	}
	*(int*) (slot + 0x26420c) = *(int*) (slot + 4);
	if (i == 0)
		*(int*) slot = *(int*) slot | 0x400;
	*(int*) (slot + 0x14) = sock;
	*(unsigned short*) (slot + 0x14a) = 0;
	*(unsigned short*) (slot + 0x14c) = 0;
	*(unsigned short*) (slot + 0x14e) = 0x19;
	*(unsigned int*) (slot + 0x150) = GetTickCount() + 0x493e0;

	for (i = 0; i < 0x2000; i++) {
		unsigned char* q = slot + i * 0x99;
		q[0x154] = 0;
		q[0x132154] = 0;
		if (i == 0) {
			*(unsigned int*) (slot + 0x1e5) = 0;
			*(unsigned int*) (slot + 0x1321e5) = 0;
		} else {
			*(unsigned int*) (q + 0x1e5) = (unsigned int) (q + 0xbb);
			*(unsigned int*) (q + 0x1321e5) = (unsigned int) (q + 0x1320bb);
		}
		if (i < 0x1fff) {
			*(unsigned int*) (q + 0x1e9) = (unsigned int) (q + 0x1ed);
			*(unsigned int*) (q + 0x1321e9) = (unsigned int) (q + 0x1321ed);
		} else {
			*(unsigned int*) (q + 0x1e9) = 0;
			*(unsigned int*) (q + 0x1321e9) = 0;
		}
	}

	*(unsigned int*) (slot + 0x2641f8) = (unsigned int) (slot + 0x154);
	*(unsigned int*) (slot + 0x2641fc) = (unsigned int) (slot + 0x132154);
	*(unsigned int*) (slot + 0x2641f0) = 0;
	*(unsigned int*) (slot + 0x2641f4) = 0;
	sprintf(msg, s_New_Connection_from__li__li__li__100299a0,
		((unsigned char*) &addr)[4], ((unsigned char*) &addr)[5],
		((unsigned char*) &addr)[6], ((unsigned char*) &addr)[7]);
	LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x4e1, msg, 1);
	return sock;

ret_neg1:
	return -1;
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

int __cdecl ReceivePacketHeader(unsigned int* conn)
{
	int (__stdcall* recv_fn)(unsigned int, char*, int, int);
	int n;
	int err;
	unsigned short state;

	if (*(unsigned char*) conn & 0x80)
		return 0;

	state = *(unsigned short*) ((char*) conn + 0x14a);
	recv_fn = (int (__stdcall*)(unsigned int, char*, int, int)) * (void**) 0x10024168;
	if (state < 3) {
		n = recv_fn(*(unsigned int*) ((char*) conn + 0x14),
			    (char*) conn + 0x18 + *(unsigned short*) ((char*) conn + 0x14a),
			    3 - *(unsigned short*) ((char*) conn + 0x14a), 0);
		if (n == 0) {
			if (*(unsigned int*) ((char*) conn + 0x150) >= GetTickCount())
				return 0;
			LogMessageInternal((char*) 0x100298b0, 0x52a, (char*) 0x10029a04, 1);
			cm_ClosePlayerConnection(conn);
			return -1;
		}
		if (n == -1) {
			err = WSAGetLastError();
			if (err == 0x2733)
				return 0;
			LogWinsockError(err);
			cm_ClosePlayerConnection(conn);
			return -1;
		}
	} else {
		n = *(volatile int*) &conn;
	}

	*(unsigned short*) ((char*) conn + 0x14a) = (unsigned short) (*(unsigned short*) ((char*) conn + 0x14a) + n);
	if (*(unsigned short*) ((char*) conn + 0x14a) < 3)
		return 0;

	n = recv_fn(*(unsigned int*) ((char*) conn + 0x14),
		    (char*) conn + 0x18 + *(unsigned short*) ((char*) conn + 0x14a),
		    (unsigned short) *(unsigned short*) ((char*) conn + 0x19) - *(unsigned short*) ((char*) conn + 0x14a), 0);
	if (n == 0) {
		if (*(unsigned int*) ((char*) conn + 0x150) >= GetTickCount())
			return 0;
		LogMessageInternal((char*) 0x100298b0, 0x552, (char*) 0x10029a04, 1);
		cm_ClosePlayerConnection(conn);
		return -1;
	}
	if (n == -1) {
		err = WSAGetLastError();
		if (err == 0x2733)
			return 0;
		LogWinsockError(err);
		cm_ClosePlayerConnection(conn);
		return -1;
	}

	*(unsigned short*) ((char*) conn + 0x14a) = (unsigned short) (*(unsigned short*) ((char*) conn + 0x14a) + n);
	*(unsigned int*) ((char*) conn + 0x150) = GetTickCount() + 0x493e0;
	if (*(unsigned short*) ((char*) conn + 0x14a) == *(unsigned short*) ((char*) conn + 0x19)) {
		unsigned int flags;
		/* Both accesses must be volatile: the volatile flag read keeps
		 * the OR in al instead of materializing 0x80 into edx, and the
		 * volatile clear pins it between the load and the OR. */
		flags = *(volatile unsigned int*) conn;
		*(volatile unsigned short*) ((char*) conn + 0x14a) = 0;
		*(unsigned int*) conn = flags | 0x80;
	}
	return 0;
}/* Sends queued data to a client socket. Transmits buffered
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

