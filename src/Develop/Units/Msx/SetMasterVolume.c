


#include <stdio.h>
#include <windows.h>

extern int msx_TrackDriver;
extern float msx_MasterFadeScale;
extern int msx_MasterVolume;
extern char g_6b7090[];
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl msx_SetMasterVolume(int h, int vol);

void __cdecl SetMasterVolume(int vol)
{
	if (msx_TrackDriver == 0) {
		return;
	}
	if (msx_MasterFadeScale < 0.0f) {
		msx_MasterFadeScale = 0.0f;
	} else if (msx_MasterFadeScale > 1.0f) {
		msx_MasterFadeScale = 1.0f;
	}
	EnterCriticalSection(&msx_TrackLock);
	msx_SetMasterVolume(msx_TrackDriver, (int) (vol * msx_MasterFadeScale));
	LeaveCriticalSection(&msx_TrackLock);
	msx_MasterVolume = vol;
	sprintf(g_6b7090, "Fademodifier is %f, Mastervolume is %d", msx_MasterFadeScale, vol);
}
