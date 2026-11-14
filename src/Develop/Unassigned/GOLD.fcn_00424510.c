#include <windows.h>
#include <winsock.h>
#include <stdio.h>

void __cdecl fcn_0041da60(char* module, unsigned int line, char* msg, int severity);

/* Gold twin of nt_LogWinsockError (GOLDTL 0x4208a0, net.c). */
/* ADDRESS: GOLD 0x00424510 */
void __cdecl fcn_00424510(int err_code)
{
	char buf[256];

	switch (err_code) {
	case WSANOTINITIALISED:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x31, "WSANOTINITIALISED", 1);
		return;
	case WSAENETDOWN:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x33, "WSAENETDOWN: The network subsystem has failed!", 1);
		return;
	case WSAEFAULT:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x35, "WSAEFAULT: The buf parameter is not completely contained in a valid part of the user address space", 1);
		return;
	case WSAENOTCONN:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x37, "WSAENOTCONN: The socket is not connected.", 1);
		return;
	case WSAEINTR:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x39, "WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.", 1);
		return;
	case WSAEINPROGRESS:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x3b, "WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the "
			"service provider is still processing a callback function.", 1);
		return;
	case WSAENETRESET:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x3d, "WSAENETRESET: The connection has been broken due to the keep-alive activity "
			"detecting a failure while the operation was in progress.", 1);
		return;
	case WSAENOTSOCK:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x3f, "WSAENOTSOCK: The descriptor is not a socket.", 1);
		return;
	case WSAEOPNOTSUPP:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x41, "WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream-style such "
			"as type SOCK_STREAM, OOB data is not supported in the communication domain "
			"associated with this socket, or the socket is unidirectional and supports only "
			"send operations.", 1);
		return;
	case WSAESHUTDOWN:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x43, "WSAESHUTDOWN: The socket has been shut down; it is not possible to receive on a "
			"socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.", 1);
		return;
	case WSAEWOULDBLOCK:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x45, "WSAEWOULDBLOCK: The socket is marked as nonblocking and the receive operation would block.", 1);
		return;
	case WSAEMSGSIZE:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x47, "WSAEMSGSIZE: The message was too large to fit into the specified buffer and was truncated.", 1);
		return;
	case WSAEINVAL:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x49, "WSAEINVAL: The socket has not been bound with bind, or an unknown flag was "
			"specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or "
			"(for byte stream sockets only) len was zero or negative.", 1);
		return;
	case WSAECONNABORTED:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x4b, "WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other "
			"failure. The application should close the socket as it is no longer usable.", 1);
		return;
	case WSAETIMEDOUT:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x4d, "WSAETIMEDOUT: The connection has been dropped because of a network failure or "
			"because the peer system failed to respond.", 1);
		return;
	case WSAECONNRESET:
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x4f, "WSAECONNRESET: The virtual circuit was reset by the remote side executing a "
			"hard or abortive close. The application should close the socket as it is no "
			"longer usable. On a UPD-datagram socket this error would indicate that a "
			"previous send operation resulted in an ICMP >Port Unreachable< message.", 1);
		return;
	default:
		sprintf(buf, "Unknown winsock error %u!!!", err_code);
		fcn_0041da60("D:\\develop\\units\\net\\net.c", 0x51, buf, 1);
		return;
	}
}
