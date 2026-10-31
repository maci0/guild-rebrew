#include <stdio.h>

/* SIZE 0x104 */
typedef struct {
	unsigned int fd_count;
	unsigned int fd_array[64];
} FdSet_420db0;

/* SIZE 0x8 */
typedef struct {
	long tv_sec;
	long tv_usec;
} TimeVal_420db0;

/* SIZE 0x10 */
typedef struct {
	short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	char sin_zero[8];
} SockAddrIn_420db0;

/* SIZE 0x10 */
typedef struct {
	char* h_name;
	char** h_aliases;
	short h_addrtype;
	short h_length;
	char** h_addr_list;
} HostEnt_420db0;

__declspec(dllimport) int __stdcall WSAStartup(unsigned short ver, void* data);
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) int __stdcall WSAGetLastError(void);
__declspec(dllimport) unsigned int __stdcall socket(int af, int type, int proto);
__declspec(dllimport) int __stdcall setsockopt(unsigned int s, int level, int name, const char* val, int len);
__declspec(dllimport) int __stdcall getsockopt(unsigned int s, int level, int name, char* val, int* len);
__declspec(dllimport) int __stdcall ioctlsocket(unsigned int s, long cmd, unsigned long* arg);
__declspec(dllimport) unsigned long __stdcall inet_addr(const char* cp);
__declspec(dllimport) HostEnt_420db0* __stdcall gethostbyname(const char* name);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short v);
__declspec(dllimport) int __stdcall connect(unsigned int s, const void* addr, int len);
__declspec(dllimport) int __stdcall select(int n, FdSet_420db0* r, FdSet_420db0* w, FdSet_420db0* e, const TimeVal_420db0* tv);
__declspec(dllimport) int __stdcall shutdown(unsigned int s, int how);
__declspec(dllimport) int __stdcall closesocket(unsigned int s);

extern int g_14cbca0;
extern char* g_14cbca4;
extern unsigned char* g_14cbca8;
extern unsigned short g_14cbcac;
extern unsigned short g_14cbcae;
extern int g_14cbcb0;
extern int g_6b7d40;

void __cdecl fcn_00420b70(void);
void __cdecl fcn_004208a0(int err);


/* Opens a non-blocking TCP connection to host:port, waiting up to 16
 * half-second select rounds; returns the socket or -1. */
/* ADDRESS: GOLDTL 0x00420db0 */
int __cdecl fcn_00420db0(char* host, int port)
{
	char wsa[0x190];
	FdSet_420db0 fds;
	char buf[0x80];
	SockAddrIn_420db0 addr;
	TimeVal_420db0 tv;
	HostEnt_420db0* h;
	int len;
	int opt;
	unsigned int s;
	int i;
	int r;

	fcn_00420b70();
	g_14cbca0 = -1;
	g_14cbca4 = 0;
	g_14cbca8 = 0;
	g_14cbcac = 0;
	g_14cbcae = 0;
	g_14cbcb0 = 0;
	if (host == 0) {
		return -1;
	}
	WSAStartup(2, wsa);
	g_6b7d40 = 1;
	s = socket(2, 1, 6);
	if (s != (unsigned int) -1) {
		opt = 1;
		if (setsockopt(s, 0xffff, 4, (char*) &opt, 4) == -1) {
			goto fail;
		}
		opt = 1;
		if (setsockopt(s, 0xffff, ~0x80, (char*) &opt, 4) == -1) {
			goto fail;
		}
		opt = 0x40000;
		if (setsockopt(s, 0xffff, 0x1002, (char*) &opt, 4) == -1) {
			goto fail;
		}
		opt = 0x20000;
		if (setsockopt(s, 0xffff, 0x1001, (char*) &opt, 4) == -1) {
			goto fail;
		}
		opt = 1;
		if (ioctlsocket(s, 0x8004667e, (unsigned long*) &opt) == -1) {
			goto fail;
		}
		addr.sin_family = 2;
		addr.sin_addr = inet_addr(host);
		if (addr.sin_addr == 0xffffffff) {
			h = gethostbyname(host);
			if (h == 0) {
				goto fail;
			}
			addr.sin_addr = **(unsigned long**) h->h_addr_list;
		}
		addr.sin_port = htons((unsigned short) port);
		if (connect(s, &addr, 16) != 0 && WSAGetLastError() != 0x2733) {
			fcn_004208a0(WSAGetLastError());
			goto fail;
		}
		tv.tv_sec = 0;
		tv.tv_usec = 500000;
		for (i = 0; i < 16; i++) {
			fds.fd_array[0] = s;
			fds.fd_count = 1;
			r = select(1, 0, &fds, 0, &tv);
			if (r == -1) {
				break;
			}
			if (r != 0) {
				goto connected;
			}
		}
		fcn_004208a0(WSAGetLastError());
fail:
		shutdown(s, 2);
		closesocket(s);
	}
	g_6b7d40 = 0;
	WSACleanup();
	s = -1;
	return s;
connected:
	len = 4;
	if (getsockopt(s, 0xffff, 0x1001, (char*) &opt, &len) != -1) {
		sprintf(buf, "getsockopt SO_SNDBUF: %d", opt);
	}
	len = 4;
	if (getsockopt(s, 0xffff, 0x1002, (char*) &opt, &len) != -1) {
		sprintf(buf, "getsockopt SO_RCVBUF: %d", opt);
	}
	g_14cbca0 = s;
	return s;
}
