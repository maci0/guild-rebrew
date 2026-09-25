// FUNCTION: GOLD 0x423770
// SIZE: 182
// FUNCTION: GOLDTL 0x0041fa10
// SIZE: 182

#include <windows.h>

extern int g_6b71a0;
extern __int64 g_6b7194;
extern __int64 g_6b6f88;
extern CRITICAL_SECTION g_14cc5a0;
void __cdecl fcn_0041fb80(void);
void __cdecl fcn_00420210(void);

void __cdecl fcn_0041fa10(void* arg)
{
	LARGE_INTEGER now;

	while (g_6b71a0 == 0) {
		if (!QueryPerformanceCounter(&now)) {
			fcn_0041fb80();
		} else if (now.QuadPart - g_6b7194 > g_6b6f88 / 20) {
			g_6b7194 = now.QuadPart;
			EnterCriticalSection(&g_14cc5a0);
			fcn_00420210();
			LeaveCriticalSection(&g_14cc5a0);
		}
		Sleep(0x17);
	}
	DeleteCriticalSection(&g_14cc5a0);
}
