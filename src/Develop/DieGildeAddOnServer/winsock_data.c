/* Winsock / socket option error strings that the reference places at
 * 0x10028bdc..0x10029408 -- immediately after m_alloc2's literals and
 * immediately before zlib trees.c's static tables.
 *
 * They used to live as (a) a named global + (b) anonymous literals in
 * server4.c / server2.c.  Those TUs' first functions sit at 0x1000ad40 /
 * 0x10009d30, so rebrew order-sources (CMakeLists.txt) links them AFTER
 * vfs/zlib (trees at 0x10006ec0), and the 0x82c-byte run landed ~900 bytes
 * late with trees/vfs occupying the winsock slot.  This TU is data-only
 * and is ordered between m_alloc2 and trees via --first-va (see
 * CMakeLists.txt).  Callers reference these by name; they must NOT also
 * spell the same text as a string literal or the bytes emit twice.
 */

/* DATA: SERVER 0x10028bdc */
char s_Unknown_winsock_error_u[] = "Unknown winsock error %u!!!";

/* DATA: SERVER 0x10028bf8 */
char s_WSAECONNRESET[] =
	"WSAECONNRESET: The virtual circuit was reset by the remote side executing a "
	"hard or abortive close. The application should close the socket as it is no "
	"longer usable. On a UPD-datagram socket this error would indicate that a "
	"previous send operation resulted in an ICMP >Port Unreachable< message.";

/* DATA: SERVER 0x10028d24 */
char s_WSAETIMEDOUT[] =
	"WSAETIMEDOUT: The connection has been dropped because of a network failure or "
	"because the peer system failed to respond.";

/* DATA: SERVER 0x10028da0 */
char s_WSAECONNABORTED[] =
	"WSAECONNABORTED: The virtual circuit was terminated due to a time-out or other "
	"failure. The application should close the socket as it is no longer usable.";

/* DATA: SERVER 0x10028e3c */
char s_WSAEINVAL[] =
	"WSAEINVAL: The socket has not been bound with bind, or an unknown flag was "
	"specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or "
	"(for byte stream sockets only) len was zero or negative.";

/* DATA: SERVER 0x10028f10 */
char s_WSAEMSGSIZE[] = "WSAEMSGSIZE: The message was too large to fit into the specified buffer and was truncated.";

/* DATA: SERVER 0x10028f6c */
char s_WSAEWOULDBLOCK[] = "WSAEWOULDBLOCK: The socket is marked as nonblocking and the receive operation would block.";

/* DATA: SERVER 0x10028fc8 */
char s_WSAESHUTDOWN[] =
	"WSAESHUTDOWN: The socket has been shut down; it is not possible to receive on a "
	"socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH.";

/* DATA: SERVER 0x10029068 */
char s_WSAEOPNOTSUPP[] =
	"WSAEOPNOTSUPP: MSG_OOB was specified, but the socket is not stream-style such "
	"as type SOCK_STREAM, OOB data is not supported in the communication domain "
	"associated with this socket, or the socket is unidirectional and supports only "
	"send operations.";

/* DATA: SERVER 0x10029164 */
char s_WSAENOTSOCK[] = "WSAENOTSOCK: The descriptor is not a socket.";

/* DATA: SERVER 0x10029194 */
char s_WSAENETRESET[] =
	"WSAENETRESET: The connection has been broken due to the keep-alive activity "
	"detecting a failure while the operation was in progress.";

/* DATA: SERVER 0x1002921c */
char s_WSAEINPROGRESS[] =
	"WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the "
	"service provider is still processing a callback function.";

/* DATA: SERVER 0x100292a4 */
char s_WSAEINTR[] = "WSAEINTR: The (blocking) call was canceled through WSACancelBlockingCall.";

/* DATA: SERVER 0x100292f0 */
char s_WSAENOTCONN[] = "WSAENOTCONN: The socket is not connected.";

/* DATA: SERVER 0x1002931c */
char s_WSAEFAULT[] = "WSAEFAULT: The buf parameter is not completely contained in a valid part of the user address space";

/* DATA: SERVER 0x10029380 */
char s_WSAENETDOWN[] = "WSAENETDOWN: The network subsystem has failed!";

/* DATA: SERVER 0x100293b0 */
char s_WSANOTINITIALISED[] = "WSANOTINITIALISED";

/* DATA: SERVER 0x100293c4 */
char s_Cant_set_SO_SNDBUF[] = "Can't set SO_SNDBUF on Socket";

/* DATA: SERVER 0x100293e4 */
char s_Cant_set_SO_RCVBUF[] = "Can't set SO_RCVBUF on Socket";

