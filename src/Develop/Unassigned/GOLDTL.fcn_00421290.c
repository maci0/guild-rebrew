


__declspec(dllimport) int __stdcall send(int s, const char* buf, int len, int flags);
__declspec(dllimport) int __stdcall WSAGetLastError(void);

extern int g_14cbca0;
extern unsigned char* g_14cbca8;
extern unsigned short g_14cbcae;
#include "GOLDTL.fcn_00421290_gconf.h"
void __cdecl fcn_004208a0(int err);
void __cdecl fcn_00421050(void);
void __cdecl fcn_00420ba0(unsigned char* p, unsigned int n, char flag);

int __cdecl fcn_00421290(void)
{
	int n;
	int err;

	if (g_14cbca0 == -1) {
		return 1;
	}
	if (g_14cbca8 == 0) {
		return 0;
	}
	n = send(g_14cbca0, (char*) g_14cbca8 + g_14cbcae, *(unsigned short*) (g_14cbca8 + 1) - g_14cbcae, 0);
	if (n == -1) {
		err = WSAGetLastError();
		if (err == 10035) {
			return 0;
		}
		fcn_004208a0(err);
		fcn_00421050();
		return 1;
	}
	g_14cbcae += n;
	g_6b7d5c += n;
	if (g_14cbcae == *(unsigned short*) (g_14cbca8 + 1)) {
		fcn_00420ba0(g_14cbca8, g_14cbcae, 0);
		g_14cbca8 = 0;
		g_14cbcae = 0;
	}
	return 0;
}
