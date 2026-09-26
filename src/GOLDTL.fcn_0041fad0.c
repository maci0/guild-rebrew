// FUNCTION: GOLD 0x423830
// SIZE: 176
// FUNCTION: GOLDTL 0x0041fad0
// SIZE: 176

#include <string.h>
#include <windows.h>

#include "client_types.h"
extern Chan_14cc460 g_14cc460;
extern CRITICAL_SECTION g_14cc5a0;
extern int g_6b71a4;
extern int g_6b71a8;
extern __int64 g_6b6f88;
int __cdecl fcn_0042a120(int* out, int a, int b, int c);
void __cdecl fcn_0042a2d0(int h);
void __cdecl fcn_0041fa10(void* arg);

int __cdecl fcn_0041fad0(int a, int b, int c)
{
	DWORD tid;

	memset(((char*)&g_14cc460), 0, sizeof(char[0x128]));
	InitializeCriticalSection(&g_14cc5a0);
	if (fcn_0042a120(&g_6b71a4, a, b, c) != 0 || fcn_0042a120(&g_6b71a8, a, b, c) != 0) {
		return -1;
	}
	if (!QueryPerformanceFrequency(&(*(LARGE_INTEGER*)&g_6b6f88))) {
		fcn_0042a2d0(g_6b71a4);
		g_6b71a4 = 0;
		return -1;
	}
	if (CreateThread(0, 0, (LPTHREAD_START_ROUTINE) fcn_0041fa10, 0, 0, &tid) == 0) {
		fcn_0042a2d0(g_6b71a4);
		g_6b71a4 = 0;
		return -1;
	}
	return 0;
}
