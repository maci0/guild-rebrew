

#include "msx.h"

extern int g_678168;
extern float msx_MasterFadeScale;
extern float msx_MasterFadeStart;
extern float msx_MasterFadeTarget;
extern unsigned int msx_MasterFadeDuration;
extern int msx_MasterVolume;
extern int msx_MasterFadeStartTime;
extern volatile int gm_GameTicks;

int __cdecl msx_GetStreamStatus(int h);
int __cdecl msx_SetStreamVolume(int h, int v);
void __cdecl SetMasterVolume(int vol);

void __cdecl msx_UpdateTracks(void)
{
	int i;
	Chan_14cc460* c;
	int n;
	unsigned int v;
	unsigned int t;

	if (msx_TrackDriver != 0) {
		for (i = 0; i < 10; i++) {
			c = &msx_Tracks[i];
			if (c->active == 0) {
				continue;
			}
			if (c->handle == 0) {
				c->active = 0;
				if (c->next != 0) {
					if (c->next->handle != 0) {
						msx_PauseStream(c->next->handle, 0);
						c->next->active = 1;
					}
					c->next->b105 = 0;
					c->next = 0;
				}
				continue;
			}
			msx_GetStreamMsPosition(c->handle, &c->f10c);
			if (c->bAmbient != 0) {
				continue;
			}
			if (msx_GetStreamStatus(c->handle) != 4 && msx_GetStreamStatus(c->handle) != 0x10) {
				c->active = 0;
				c->f114 = 0;
				msx_CloseStream(c->handle);
				c->handle = 0;
				if (c->next != 0 && c->next->handle != 0) {
					msx_PauseStream(c->next->handle, 0);
					c->next->active = 1;
					c->next->b105 = 0;
					c->next = 0;
				}
			}
			if (c->f114 == 1) {
				if (c->f10c < c->f110) {
					c->f10c = c->f110;
				}
				if (c->f120 != 0) {
					n = c->f120 * g_678168 / c->f118;
				} else {
					n = g_678168;
				}
				if (n != 0 && n > c->f10c - c->f110) {
					c->f11c = (c->f10c - c->f110) * c->f118 / n;
					if (abs(c->f118 - c->f11c) < 2) {
						c->f114 = 0;
						c->f11c = c->f118;
					}
				} else {
					c->f114 = 0;
					c->f11c = c->f118;
				}
				msx_SetStreamVolume(c->handle, c->f11c);
			} else if (c->f114 == 2) {
				if (c->f10c < c->f110) {
					c->f10c = c->f110;
				}
				n = c->f120 * g_678168 / c->f118;
				v = 0;
				if (n != 0 && n > c->f10c - c->f110) {
					v = (c->f110 - c->f10c + n) * c->f118 / n;
					c->f11c = v;
					if (v > 2) {
						msx_SetStreamVolume(c->handle, v);
					} else {
						c->f114 = 0;
						c->f11c = 0;
						msx_SetStreamVolume(c->handle, 0);
						msx_CloseStream(c->handle);
						c->handle = 0;
						c->active = 0;
						if (c->next != 0) {
							msx_PauseStream(c->next->handle, 0);
							c->next->active = 1;
							c->next->b105 = 0;
							c->next = 0;
						}
					}
				} else {
					c->f114 = v;
					c->f11c = v;
					msx_SetStreamVolume(c->handle, v);
					msx_CloseStream(c->handle);
					c->handle = 0;
					c->active = 0;
					if (c->next != 0) {
						msx_PauseStream(c->next->handle, 0);
						c->next->active = 1;
						c->next->b105 = 0;
						c->next = 0;
					}
				}
			}
		}
		if (msx_MasterFadeTarget >= 0.0f) {
			t = gm_GameTicks * 8 + gm_GameTicks * 4 + gm_GameTicks;
			t -= msx_MasterFadeStartTime;
			if (t < msx_MasterFadeDuration) {
				msx_MasterFadeScale = (msx_MasterFadeTarget - msx_MasterFadeStart) / (float) msx_MasterFadeDuration * (float) t + msx_MasterFadeStart;
			} else {
				msx_MasterFadeScale = msx_MasterFadeTarget;
				msx_MasterFadeTarget = -1.0f;
			}
			SetMasterVolume(msx_MasterVolume);
		}
	}
}
