

#include <windows.h>

extern int msx_TrackDriver;
extern float msx_MasterFadeScale;
extern float msx_MasterFadeStart;
extern float msx_MasterFadeTarget;
extern unsigned int msx_MasterFadeDuration;
extern int msx_MasterVolume;
extern int msx_MasterFadeStartTime;
extern volatile int gm_GameTicks;
extern CRITICAL_SECTION msx_TrackLock;
void __cdecl SetMasterVolume(int vol);

void __cdecl FadeMasterVolume(float fade, int time)
{
	if (msx_TrackDriver == 0 || fade < 0.0f || fade > 1.0f) {
		return;
	}
	EnterCriticalSection(&msx_TrackLock);
	if (time == 0) {
		msx_MasterFadeScale = fade;
		SetMasterVolume(msx_MasterVolume);
		LeaveCriticalSection(&msx_TrackLock);
		return;
	}
	msx_MasterFadeDuration = time;
	msx_MasterFadeTarget = fade;
	msx_MasterFadeStart = msx_MasterFadeScale;
	msx_MasterFadeStartTime = gm_GameTicks * 8 + gm_GameTicks * 4 + gm_GameTicks;
	LeaveCriticalSection(&msx_TrackLock);
}
