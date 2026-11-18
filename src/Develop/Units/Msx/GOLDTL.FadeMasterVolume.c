

#include <windows.h>

extern int msx_TrackDriver;
extern float g_678150;
extern float g_678154;
extern float g_678158;
extern unsigned int g_67815c;
extern int g_678160;
extern int g_6b7190;
extern volatile int g_6b7fac;
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl SetMasterVolume(int vol);

void __cdecl FadeMasterVolume(float fade, int time)
{
	if (msx_TrackDriver == 0 || fade < 0.0f || fade > 1.0f) {
		return;
	}
	EnterCriticalSection(&msx_TrackLock);
	if (time == 0) {
		g_678150 = fade;
		SetMasterVolume(g_678160);
		LeaveCriticalSection(&msx_TrackLock);
		return;
	}
	g_67815c = time;
	g_678158 = fade;
	g_678154 = g_678150;
	g_6b7190 = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
	LeaveCriticalSection(&msx_TrackLock);
}
