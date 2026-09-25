extern int g_675170;

// SIZE 0x10
struct sin_402220 {
	short family;
	unsigned short port;
	unsigned long addr;
	char zero[8];
};

extern struct sin_402220 g_1552010;
extern struct sin_402220 g_1552000;

__declspec(dllimport) int __stdcall WSAStartup(unsigned short, void*);
__declspec(dllimport) int __stdcall socket(int, int, int);
__declspec(dllimport) int __stdcall setsockopt(int, int, int, const char*, int);
__declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short);
__declspec(dllimport) int __stdcall bind(int, const void*, int);
__declspec(dllimport) unsigned long __stdcall GetLastError(void);
__declspec(dllimport) unsigned long __stdcall FormatMessageA(unsigned long, const void*, unsigned long, unsigned long, char*, unsigned long, void*);
__declspec(dllimport) void* __stdcall LocalFree(void*);

// FUNCTION: GOLDTL 0x402220
// SIZE: 254

/* Opens the UDP broadcast socket once: bound to any address, with the
 * broadcast destination on the given port. */
void __cdecl fcn_00402220(unsigned short port)
{
	int one;
	char* msg;
	char wsa[0x190];

	one = 1;
	if (g_675170 != -1) {
		return;
	}
	WSAStartup(2, wsa);
	g_675170 = socket(2, 2, 0);
	if (g_675170 == -1) {
		GetLastError();
		if (FormatMessageA(0x1300, 0, GetLastError(), 0x400, (char*) &msg, 0, 0) == 0) {
			LocalFree(msg);
		}
		return;
	}
	setsockopt(g_675170, 0xffff, 0x20, (const char*) &one, 4);
	g_1552010.family = 2;
	g_1552010.addr = htonl(0);
	g_1552010.port = htons(0);
	bind(g_675170, &g_1552010, 0x10);
	g_1552000.family = 2;
	g_1552000.addr = htonl(0xffffffff);
	g_1552000.port = htons(port);
}
