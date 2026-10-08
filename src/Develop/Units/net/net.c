/* The network unit, D:\develop\units\net\net.c in both client builds: the client's TCP connection to the
 * server (Europa1400Gold_TL.exe 0x4208a0..0x421347). The server links the same source and calls none of
 * its functions, so /OPT:REF discards the code; what survives is the winsock error text below, which
 * server.c shares. The discarded code still loads the WS2_32 members only it calls (connect,
 * gethostbyname, gethostname, getsockopt, inet_addr, inet_ntoa, select) and its absolute operands count
 * into LINK's .reloc reservation (docs/msvc6-link-layout.md section 5d).
 *
 * The original links objects in file-name order and this run sits between m_alloc and trees, where net
 * sorts; no function here has a server address, so the TU is still placed by --first-va (CMakeLists.txt).
 * server.c reads the strings by name and must not spell the same text as a literal, or the bytes are
 * emitted twice. */

#include "../Error/error.h"
#include <winsock2.h>

char s_Unknown_winsock_error_u[] = "Unknown winsock error %u!!!";

char s_WSAECONNRESET[] =
	"WSAECONNRESET: The virtual circuit was reset by the remote side executing a "
	"hard or abortive close. The application should close the socket as it is no "
	"longer usable. On a UPD-datagram socket this error would indicate that a "
	"previous send operation resulted in an ICMP >Port Unreachable< message.";

char s_WSAETIMEDOUT[] =
	"WSAETIMEDOUT: The connection has been dropped because of a network failure or "
	"because the peer system failed to respond.";

char s_WSAECONNABORTED[] =
	"WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other "
	"failure. The application should close the socket as it is no longer usable.";

char s_WSAEINVAL[] =
	"WSAEINVAL: The socket has not been bound with bind, or an unknown flag was "
	"specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or "
	"(for byte stream sockets only) len was zero or negative.";

char s_WSAEMSGSIZE[] = "WSAEMSGSIZE: The message was too large to fit into the specified buffer and was truncated.";

char s_WSAEWOULDBLOCK[] = "WSAEWOULDBLOCK: The socket is marked as nonblocking and the receive operation would block.";

char s_WSAESHUTDOWN[] =
	"WSAESHUTDOWN: The socket has been shut down; it is not possible to receive on a "
	"socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.";

char s_WSAEOPNOTSUPP[] =
	"WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream-style such "
	"as type SOCK_STREAM, OOB data is not supported in the communication domain "
	"associated with this socket, or the socket is unidirectional and supports only "
	"send operations.";

char s_WSAENOTSOCK[] = "WSAENOTSOCK: The descriptor is not a socket.";

char s_WSAENETRESET[] =
	"WSAENETRESET: The connection has been broken due to the keep-alive activity "
	"detecting a failure while the operation was in progress.";

char s_WSAEINPROGRESS[] =
	"WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the "
	"service provider is still processing a callback function.";

char s_WSAEINTR[] = "WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.";

char s_WSAENOTCONN[] = "WSAENOTCONN: The socket is not connected.";

char s_WSAEFAULT[] = "WSAEFAULT: The buf parameter is not completely contained in a valid part of the user address space";

char s_WSAENETDOWN[] = "WSAENETDOWN: The network subsystem has failed!";

char s_WSANOTINITIALISED[] = "WSANOTINITIALISED";

char s_Cant_set_SO_SNDBUF[] = "Can't set SO_SNDBUF on Socket";

char s_Cant_set_SO_RCVBUF[] = "Can't set SO_RCVBUF on Socket";


/* Client state. The server image references none of it, so no server allocation is proven: each object
 * is selectany and leaves with the code. In the client, nt_WsaStarted..nt_SendBytes are the unit's
 * plain .bss (0x6b7d40..0x6b7d64, 36 bytes); the server's unreferenced 44 bytes at 0x10034644, between
 * m_alloc's .bss and the next unit's, are the likely remains. The connection block and the statistics
 * table are COMMON in the client (0x14cbc84..0x14cc360). cm_LastSyncCount is the client command.c's
 * (0xaecde0). */
__declspec(selectany) int nt_WsaStarted = 0;
__declspec(selectany) char nt_LocalIp[16] = {0};
__declspec(selectany) unsigned int nt_RecvBytes = 0;
__declspec(selectany) unsigned int nt_RecvPackets = 0;
__declspec(selectany) unsigned int nt_SendBytes = 0;
__declspec(selectany) unsigned int nt_SendPackets = 0;
__declspec(selectany) int nt_LastRequCount = 0;
__declspec(selectany) SOCKET nt_Socket = 0;
__declspec(selectany) unsigned char* nt_RecvCmd = 0;
__declspec(selectany) unsigned char* nt_SendCmd = 0;
__declspec(selectany) unsigned short nt_RecvDone = 0;
__declspec(selectany) unsigned short nt_SendDone = 0;
__declspec(selectany) int nt_Closed = 0;
/* Per command type: received packets, received bytes, sent packets, sent bytes. */
__declspec(selectany) unsigned int nt_CmdStats[0x6a][4] = {0};
__declspec(selectany) int cm_LastSyncCount = 0;

/* A command starts with its type byte and its total length (unaligned word at offset 1). */
#define NT_CMD_LEN(cmd) (*(unsigned short*) ((cmd) + 1))
#define NT_CMD_HEADER 3

/* TL 0x4208a0 */
void __cdecl nt_LogWinsockError(int err_code)
{
	char buf[256];

	switch (err_code) {
	case WSANOTINITIALISED:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x31, s_WSANOTINITIALISED, 1);
		return;
	case WSAENETDOWN:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x33, s_WSAENETDOWN, 1);
		return;
	case WSAEFAULT:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x35, s_WSAEFAULT, 1);
		return;
	case WSAENOTCONN:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x37, s_WSAENOTCONN, 1);
		return;
	case WSAEINTR:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x39, s_WSAEINTR, 1);
		return;
	case WSAEINPROGRESS:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x3b, s_WSAEINPROGRESS, 1);
		return;
	case WSAENETRESET:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x3d, s_WSAENETRESET, 1);
		return;
	case WSAENOTSOCK:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x3f, s_WSAENOTSOCK, 1);
		return;
	case WSAEOPNOTSUPP:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x41, s_WSAEOPNOTSUPP, 1);
		return;
	case WSAESHUTDOWN:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x43, s_WSAESHUTDOWN, 1);
		return;
	case WSAEWOULDBLOCK:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x45, s_WSAEWOULDBLOCK, 1);
		return;
	case WSAEMSGSIZE:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x47, s_WSAEMSGSIZE, 1);
		return;
	case WSAEINVAL:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x49, s_WSAEINVAL, 1);
		return;
	case WSAECONNABORTED:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x4b, s_WSAECONNABORTED, 1);
		return;
	case WSAETIMEDOUT:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x4d, s_WSAETIMEDOUT, 1);
		return;
	case WSAECONNRESET:
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x4f, s_WSAECONNRESET, 1);
		return;
	default:
		sprintf(buf, s_Unknown_winsock_error_u, err_code);
		LogMessageInternal("D:\\develop\\units\\net\\net.c", 0x51, buf, 1);
		return;
	}
}

/* TL 0x420b70 */
void __cdecl nt_ResetStats(void)
{
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_ResetStats(): enter", 1);
	memset(nt_CmdStats, 0, sizeof(nt_CmdStats));
	nt_RecvPackets = 0;
	nt_RecvBytes = 0;
	nt_SendPackets = 0;
	nt_SendBytes = 0;
}

/* TL 0x420ba0 */
void __cdecl nt_CountCmd(unsigned char* cmd, unsigned int len, char received)
{
	int col;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_CountCmd(): enter", 1);
	if (cmd != 0 && len > *cmd && *cmd < 0x6a) {
		col = received ? 0 : 2;
		nt_CmdStats[*cmd][col]++;
		nt_CmdStats[*cmd][col + 1] += len;
	}
}

/* TL 0x420bf0: formats the totals and each command type's share; the text is not printed. */
void __cdecl nt_FormatStats(void)
{
	char line[256];
	char total[128];
	unsigned int type;

	sprintf(total, "Recv: %u Packets w/ %u bytes, Send: %u Packets w/ %u bytes",
		nt_RecvPackets, nt_RecvBytes, nt_SendPackets, nt_SendBytes);
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, total, 1);
	for (type = 0; type < 0x6a; type++) {
		sprintf(line,
			"%u. Recv: %u Packets (%02f%%) w/ %u bytes (%02f%%), Send: %u Packets (%02f%%) w/ %u bytes (%02f%%)",
			type,
			nt_CmdStats[type][0], (double) nt_CmdStats[type][0] * 100.0 / (double) nt_RecvPackets,
			nt_CmdStats[type][1], (double) nt_CmdStats[type][1] * 100.0 / (double) nt_RecvBytes,
			nt_CmdStats[type][2], (double) nt_CmdStats[type][2] * 100.0 / (double) nt_SendPackets,
			nt_CmdStats[type][3], (double) nt_CmdStats[type][3] * 100.0 / (double) nt_SendBytes);
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, line, 1);
	}
}

/* TL 0x420d20: the local host's address as dotted text, resolved once. */
char* __cdecl nt_GetLocalIp(void)
{
	char host[512];
	WSADATA wsa;
	struct hostent* h;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_GetLocalIp(): enter", 1);
	if (nt_LocalIp[0] == 0) {
		if (nt_WsaStarted == 0) {
			WSAStartup(2, &wsa);
		}
		if (gethostname(host, sizeof(host)) == 0) {
			h = gethostbyname(host);
			if (h != 0) {
				strcpy(nt_LocalIp, inet_ntoa(*(struct in_addr*) h->h_addr_list[0]));
			}
		}
		if (nt_WsaStarted == 0) {
			WSACleanup();
		}
	}
	return nt_LocalIp;
}

/* TL 0x420db0: opens a non-blocking TCP connection to host:port, waiting up to 16 half-second select
 * rounds; returns the socket or -1. */
int __cdecl nt_Connect(char* host, int port)
{
	WSADATA wsa;
	fd_set fds;
	char buf[128];
	struct sockaddr_in addr;
	struct timeval tv;
	struct hostent* h;
	int len;
	int opt;
	SOCKET s;
	int i;
	int r;
	int res;

	nt_ResetStats();
	res = -1;
	nt_Socket = res;
	nt_RecvCmd = 0;
	nt_SendCmd = 0;
	nt_RecvDone = 0;
	nt_SendDone = 0;
	nt_Closed = 0;
	if (host == 0) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): host == NULL", 1);
		goto done;
	}
	WSAStartup(2, &wsa);
	nt_WsaStarted = 1;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET) {
		opt = 1;
		if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*) &opt, 4) == SOCKET_ERROR) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): setsockopt SO_REUSEADDR failed", 1);
			goto fail;
		}
		opt = 1;
		if (setsockopt(s, SOL_SOCKET, SO_DONTLINGER, (char*) &opt, 4) == SOCKET_ERROR) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): setsockopt SO_DONTLINGER failed", 1);
			goto fail;
		}
		opt = 0x40000;
		if (setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*) &opt, 4) == SOCKET_ERROR) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): setsockopt SO_RCVBUF failed", 1);
			goto fail;
		}
		opt = 0x20000;
		if (setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*) &opt, 4) == SOCKET_ERROR) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): setsockopt SO_SNDBUF failed", 1);
			goto fail;
		}
		opt = 1;
		if (ioctlsocket(s, FIONBIO, (unsigned long*) &opt) == SOCKET_ERROR) {
			/* placeholder: inferred server log call, see msvc6-link-layout 5f */
			LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): ioctlsocket FIONBIO failed", 1);
			goto fail;
		}
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(host);
		if (addr.sin_addr.s_addr == INADDR_NONE) {
			h = gethostbyname(host);
			if (h == 0) {
				/* placeholder: inferred server log call, see msvc6-link-layout 5f */
				LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Connect(): Unknown host", 1);
				goto fail;
			}
			addr.sin_addr.s_addr = *(unsigned long*) h->h_addr_list[0];
		}
		addr.sin_port = htons((unsigned short) port);
		if (connect(s, (struct sockaddr*) &addr, 16) != 0 && WSAGetLastError() != WSAEWOULDBLOCK) {
			nt_LogWinsockError(WSAGetLastError());
			goto fail;
		}
		tv.tv_sec = 0;
		tv.tv_usec = 500000;
		for (i = 0; i < 16; i++) {
			fds.fd_array[0] = s;
			fds.fd_count = 1;
			r = select(1, 0, &fds, 0, &tv);
			if (r == SOCKET_ERROR) {
				break;
			}
			if (r != 0) {
				goto connected;
			}
		}
		nt_LogWinsockError(WSAGetLastError());
	fail:
		shutdown(s, 2);
		closesocket(s);
	}
	nt_WsaStarted = 0;
	WSACleanup();
	goto done;
connected:
	len = 4;
	if (getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*) &opt, &len) != SOCKET_ERROR) {
		sprintf(buf, "getsockopt SO_SNDBUF: %d", opt);
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, buf, 1);
	}
	len = 4;
	if (getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*) &opt, &len) != SOCKET_ERROR) {
		sprintf(buf, "getsockopt SO_RCVBUF: %d", opt);
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, buf, 1);
	}
	nt_Socket = s;
	res = s;
done:
	return res;
}

/* TL 0x421050 */
void __cdecl nt_Disconnect(void)
{
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Disconnect(): enter", 1);
	if (nt_Socket != INVALID_SOCKET) {
		shutdown(nt_Socket, 2);
		closesocket(nt_Socket);
		nt_Socket = INVALID_SOCKET;
		nt_Closed = 1;
	}
	WSACleanup();
	nt_WsaStarted = 0;
}

/* TL 0x4210a0: reads the pending command into nt_RecvCmd, header first. Returns 1 when the connection
 * is gone, else 0. */
int __cdecl nt_Recv(void)
{
	char buf[256];
	unsigned char* cmd;
	int n;
	int err;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Recv(): enter", 1);
	if (nt_Socket == INVALID_SOCKET) {
		return 1;
	}
	if (nt_RecvCmd == 0) {
		return 0;
	}
	if (nt_RecvDone < NT_CMD_HEADER) {
		n = recv(nt_Socket, (char*) nt_RecvCmd + nt_RecvDone, NT_CMD_HEADER - nt_RecvDone, 0);
		if (n == 0) {
			nt_Disconnect();
			return 1;
		}
		if (n == SOCKET_ERROR) {
			goto error;
		}
		nt_RecvDone += n;
		nt_RecvBytes += n;
		if (nt_RecvDone < NT_CMD_HEADER) {
			return 0;
		}
	}
	n = recv(nt_Socket, (char*) nt_RecvCmd + nt_RecvDone, NT_CMD_LEN(nt_RecvCmd) - nt_RecvDone, 0);
	if (n == 0) {
		nt_Disconnect();
		return 1;
	}
	if (n == SOCKET_ERROR) {
	error:
		err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK) {
			return 0;
		}
		nt_LogWinsockError(err);
		nt_Disconnect();
		return 1;
	}
	nt_RecvBytes += n;
	nt_RecvDone += n;
	if (nt_RecvDone == NT_CMD_LEN(nt_RecvCmd)) {
		cmd = nt_RecvCmd;
		if (*(int*) (cmd + 4) != -1) {
			if (*(int*) (cmd + 8) == nt_LastRequCount + 1) {
				nt_LastRequCount = *(int*) (cmd + 8);
			} else if (*(int*) (cmd + 8) == cm_LastSyncCount) {
				sprintf(buf,
					"nt_Recv(): Received a Command with Count == cm_LastSyncCount, cmd->Count is %li, LastRequCnt is %li",
					*(int*) (cmd + 8), cm_LastSyncCount);
				/* placeholder: inferred server log call, see msvc6-link-layout 5f */
				LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, buf, 1);
			} else if (cmd[0] == 0x20 && cmd[0x10] == 0xe) {
				sprintf(buf, "nt_Recv(): Received Sync, cmd->Count is %li, LastRequCnt is %li",
					*(int*) (cmd + 8), nt_LastRequCount);
				/* placeholder: inferred server log call, see msvc6-link-layout 5f */
				LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, buf, 1);
			} else {
				sprintf(buf, "nt_Recv(): Lost a Command, cmd->Count is %li, nt_LastRequCount is %li",
					*(int*) (cmd + 8), nt_LastRequCount);
				/* placeholder: inferred server log call, see msvc6-link-layout 5f */
				LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, buf, 1);
				nt_LastRequCount = *(int*) (cmd + 8);
			}
		}
		nt_CountCmd(nt_RecvCmd, nt_RecvDone, 1);
		nt_RecvCmd = 0;
		nt_RecvDone = 0;
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Recv(): exit", 1);
	return 0;
}

/* TL 0x421290: sends the rest of nt_SendCmd. Returns 1 when the connection is gone, else 0. */
int __cdecl nt_Send(void)
{
	int n;
	int err;

	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\develop\\units\\net\\net.c", __LINE__, "nt_Send(): enter", 1);
	if (nt_Socket == INVALID_SOCKET) {
		return 1;
	}
	if (nt_SendCmd == 0) {
		return 0;
	}
	n = send(nt_Socket, (char*) nt_SendCmd + nt_SendDone, NT_CMD_LEN(nt_SendCmd) - nt_SendDone, 0);
	if (n == SOCKET_ERROR) {
		err = WSAGetLastError();
		if (err == WSAEWOULDBLOCK) {
			return 0;
		}
		nt_LogWinsockError(err);
		nt_Disconnect();
		return 1;
	}
	nt_SendDone += n;
	nt_SendBytes += n;
	if (nt_SendDone == NT_CMD_LEN(nt_SendCmd)) {
		nt_CountCmd(nt_SendCmd, nt_SendDone, 0);
		nt_SendCmd = 0;
		nt_SendDone = 0;
	}
	return 0;
}
