#include "g_1552000.h"
extern int nt_BroadcastSocket;

extern struct sin_402220 g_1552010;
extern struct sin_402220 nt_BroadcastAddr;

__declspec(dllimport) int __stdcall WSAStartup(unsigned short, void*);
__declspec(dllimport) int __stdcall socket(int, int, int);
__declspec(dllimport) int __stdcall setsockopt(int, int, int, const char*, int);
__declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short);
__declspec(dllimport) int __stdcall bind(int, const void*, int);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);
__declspec(dllimport) unsigned long __stdcall FormatMessageA(unsigned long, const void*, unsigned long, unsigned long, char*, unsigned long, void*);
__declspec(dllimport) void* __stdcall LocalFree(void*);


/* Opens the UDP broadcast socket once: bound to any address, with the
 * broadcast destination on the given port. */
/* ADDRESS: GOLDTL 0x00402220 */
void __cdecl nt_InitBroadcastSocket(unsigned short port)
{
	int one;
	char* msg;
	char wsa[0x190];

	one = 1;
	if (nt_BroadcastSocket != -1) {
		return;
	}
	WSAStartup(2, wsa);
	nt_BroadcastSocket = socket(2, 2, 0);
	if (nt_BroadcastSocket == -1) {
		GetLastError();
		if (FormatMessageA(0x1300, 0, GetLastError(), 0x400, (char*) &msg, 0, 0) == 0) {
			LocalFree(msg);
		}
		return;
	}
	setsockopt(nt_BroadcastSocket, 0xffff, 0x20, (const char*) &one, 4);
	g_1552010.family = 2;
	g_1552010.addr = htonl(0);
	g_1552010.port = htons(0);
	bind(nt_BroadcastSocket, &g_1552010, 0x10);
	nt_BroadcastAddr.family = 2;
	nt_BroadcastAddr.addr = htonl(0xffffffff);
	nt_BroadcastAddr.port = htons(port);
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_14eaae0[423232];
#endif
