/* Winsock and socket-option error strings, 0x10028bdc..0x10029408: a data-only
 * Units TU. The original links its objects in file-name order, and this run sits
 * between m_alloc and trees, so the TU name sorts there; having no code, it is
 * still placed by --first-va (CMakeLists.txt). server.c reads these by name and
 * must not spell the same text as a literal, or the bytes are emitted twice. */

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

