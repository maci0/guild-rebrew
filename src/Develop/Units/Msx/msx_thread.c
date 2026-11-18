#include <windows.h>

extern int g_6b71a0;
extern __int64 g_6b7194;
extern __int64 g_6b6f88;
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl fcn_0041fb80(void);
void __cdecl fcn_00420210(void);
#include <string.h>

#include "../../../client_types.h"
extern Chan_14cc460 msx_NullTrack;
extern int msx_TrackDriver;
extern int msx_AmbientDriver;
int __cdecl fcn_0042a120(int* out, int a, int b, int c);
void __cdecl fcn_0042a2d0(int h);
void __cdecl fcn_0041fa10(void* arg);

/* ADDRESS: GOLD 0x00423770 */
/* ADDRESS: GOLDTL 0x0041fa10 */
void __cdecl fcn_0041fa10(void* arg)
{
	LARGE_INTEGER now;

	while (g_6b71a0 == 0) {
		if (!QueryPerformanceCounter(&now)) {
			fcn_0041fb80();
		} else if (now.QuadPart - g_6b7194 > g_6b6f88 / 20) {
			g_6b7194 = now.QuadPart;
			EnterCriticalSection(&msx_TrackLock);
			fcn_00420210();
			LeaveCriticalSection(&msx_TrackLock);
		}
		Sleep(0x17);
	}
	DeleteCriticalSection(&msx_TrackLock);
}

/* ADDRESS: GOLD 0x00423830 */
/* ADDRESS: GOLDTL 0x0041fad0 */
int __cdecl fcn_0041fad0(int a, int b, int c)
{
	DWORD tid;

	memset(((char*)&msx_NullTrack), 0, sizeof(char[0x128]));
	InitializeCriticalSection(&msx_TrackLock);
	if (fcn_0042a120(&msx_TrackDriver, a, b, c) != 0 || fcn_0042a120(&msx_AmbientDriver, a, b, c) != 0) {
		return -1;
	}
	if (!QueryPerformanceFrequency(&(*(LARGE_INTEGER*)&g_6b6f88))) {
		fcn_0042a2d0(msx_TrackDriver);
		msx_TrackDriver = 0;
		return -1;
	}
	if (CreateThread(0, 0, (LPTHREAD_START_ROUTINE) fcn_0041fa10, 0, 0, &tid) == 0) {
		fcn_0042a2d0(msx_TrackDriver);
		msx_TrackDriver = 0;
		return -1;
	}
	return 0;
}
