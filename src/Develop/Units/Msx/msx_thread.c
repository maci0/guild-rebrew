#include <windows.h>

extern int g_6b71a0;
extern __int64 g_6b7194;
extern __int64 g_6b6f88;
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl msx_ShutdownDrivers(void);
void __cdecl msx_UpdateTracks(void);
#include <string.h>

#include "Develop/client_types.h"
extern Chan_14cc460 msx_NullTrack;
extern int msx_TrackDriver;
extern int msx_AmbientDriver;
int __cdecl msx_OpenDigOutput(int* out, int a, int b, int c);
void __cdecl msx_ReleaseWaveDriver(int h);
void __cdecl msx_RunTrackThread(void* arg);

/* ADDRESS: GOLD 0x00423770 */
/* ADDRESS: GOLDTL 0x0041fa10 */
/* ADDRESS: GOLDDE 0x0041ca60 */
void __cdecl msx_RunTrackThread(void* arg)
{
	LARGE_INTEGER now;

	while (g_6b71a0 == 0) {
		if (!QueryPerformanceCounter(&now)) {
			msx_ShutdownDrivers();
		} else if (now.QuadPart - g_6b7194 > g_6b6f88 / 20) {
			g_6b7194 = now.QuadPart;
			EnterCriticalSection(&msx_TrackLock);
			msx_UpdateTracks();
			LeaveCriticalSection(&msx_TrackLock);
		}
		Sleep(0x17);
	}
	DeleteCriticalSection(&msx_TrackLock);
}

/* ADDRESS: GOLD 0x00423830 */
/* ADDRESS: GOLDTL 0x0041fad0 */
/* ADDRESS: GOLDDE 0x0041cb20 */
int __cdecl msx_InitDrivers(int a, int b, int c)
{
	DWORD tid;

	memset(((char*)&msx_NullTrack), 0, sizeof(char[0x128]));
	InitializeCriticalSection(&msx_TrackLock);
	if (msx_OpenDigOutput(&msx_TrackDriver, a, b, c) != 0 || msx_OpenDigOutput(&msx_AmbientDriver, a, b, c) != 0) {
		return -1;
	}
	if (!QueryPerformanceFrequency(&(*(LARGE_INTEGER*)&g_6b6f88))) {
		msx_ReleaseWaveDriver(msx_TrackDriver);
		msx_TrackDriver = 0;
		return -1;
	}
	if (CreateThread(0, 0, (LPTHREAD_START_ROUTINE) msx_RunTrackThread, 0, 0, &tid) == 0) {
		msx_ReleaseWaveDriver(msx_TrackDriver);
		msx_TrackDriver = 0;
		return -1;
	}
	return 0;
}
