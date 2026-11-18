


#include <stdio.h>
#include <windows.h>

extern int msx_TrackDriver;
extern float g_678150;
extern int g_678160;
extern char g_6b7090[];
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl fcn_0042a0e0(int h, int vol);

void __cdecl SetMasterVolume(int vol)
{
	if (msx_TrackDriver == 0) {
		return;
	}
	if (g_678150 < 0.0f) {
		g_678150 = 0.0f;
	} else if (g_678150 > 1.0f) {
		g_678150 = 1.0f;
	}
	EnterCriticalSection(&msx_TrackLock);
	fcn_0042a0e0(msx_TrackDriver, (int) (vol * g_678150));
	LeaveCriticalSection(&msx_TrackLock);
	g_678160 = vol;
	sprintf(g_6b7090, "Fademodifier is %f, Mastervolume is %d", g_678150, vol);
}
