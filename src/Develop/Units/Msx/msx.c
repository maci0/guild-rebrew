#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "msx.h"

extern int g_6b719c;
extern char g_6b6f90[];
int __cdecl msx_GetTimerHighestDelay(void);
int __cdecl msx_OpenStream(int* lib, char* path, int* out);
int __cdecl msx_GetStreamLengthMs(int h, int* len);
int __cdecl msx_SetStreamVolume(int h, int v);
int __cdecl msx_StartStream(int h);
int __cdecl msx_SetStreamMsPosition(int h, int pos);
int __cdecl msx_SetStreamLoopCount(int h, int f);

/* ADDRESS: GOLDDE 0x0041cc20 */
void __cdecl msx_SetTrackVolume(Chan_14cc460* p, int a2)
{
	if (msx_TrackDriver != 0 && p != 0) {
		EnterCriticalSection(&msx_TrackLock);
		p->f118 = a2;
		if (p->f114 == 0 && p->active != 0) {
			p->f11c = a2;
			if (p->handle != 0) {
				msx_SetStreamVolume(p->handle, a2);
			}
		}
		LeaveCriticalSection(&msx_TrackLock);
	}
}

/* ADDRESS: GOLDDE 0x0041cd80 */
Chan_14cc460* __cdecl msx_StartTrack(const char* name, int restart)
{
	Chan_14cc460* c;

	if (msx_TrackDriver == 0) {
		return &msx_NullTrack;
	}
	EnterCriticalSection(&msx_TrackLock);
	c = FindTrackByName(name);
	LeaveCriticalSection(&msx_TrackLock);
	if (c == 0) {
		EnterCriticalSection(&msx_TrackLock);
		c = FindFreeTrack();
		if (c != 0) {
			memset(c, 0, sizeof(Chan_14cc460));
			strcpy(c->name, name);
		}
		LeaveCriticalSection(&msx_TrackLock);
	}
	c->bAmbient = 0;
	if (msx_StartTrackInternal(c, restart) == -1) {
		c = 0;
	}
	return c;
}

/* ADDRESS: GOLDDE 0x0041ce20 */
int __cdecl msx_StartTrackInternal(Chan_14cc460* c, int restart)
{
	char path[0x100];
	int err;
	Chan_14cc460* cur;

	if (((int*)msx_TrackDriver) == 0 || ((int*)msx_AmbientDriver) == 0) {
		return 0;
	}
	EnterCriticalSection(&msx_TrackLock);
	if (g_6b719c != 0) {
		sprintf(g_6b6f90, "Reporting last delaypeak: %d", msx_GetTimerHighestDelay());
	}
	else {
		g_6b719c = msx_GetTimerHighestDelay();
	}
	if (c->active == 0) {
		strcpy(path, msx_TrackPath);
		strcat(path, c->name);
		if (c->handle == 0) {
			if (c->bAmbient != 0) {
				err = msx_OpenStream(((int*)msx_AmbientDriver), path, &c->handle);
			}
			else {
				err = msx_OpenStream(((int*)msx_TrackDriver), path, &c->handle) == -1;
			}
			if (err != 0) {
				LeaveCriticalSection(&msx_TrackLock);
				return -1;
			}
		}
		if (c->f108 == 0) {
			msx_GetStreamLengthMs(c->handle, &c->f108);
			c->f118 = 0x7f;
		}
		if ((c->bAmbient == 0 && c->f108 - c->f10c < 10000) || c->f10c == 0) {
			c->f10c = 0;
			c->f11c = c->f118;
			c->f114 = 0;
			msx_SetStreamVolume(c->handle, 0);
			msx_StartStream(c->handle);
			msx_PauseStream(c->handle, 1);
			msx_SetStreamMsPosition(c->handle, 0);
			msx_SetStreamVolume(c->handle, c->f118);
			c->f110 = 0;
		}
		else {
			msx_PauseStream(c->handle, 1);
			msx_SetStreamVolume(c->handle, 0);
			msx_SetStreamMsPosition(c->handle, c->f10c);
			if (c->bAmbient == 0) {
				c->f11c = 0;
				c->f120 = 0;
				c->f114 = 1;
				c->f110 = c->f10c;
			}
		}
		if (restart != 0) {
			msx_SetStreamLoopCount(c->handle, 0);
		}
		else {
			msx_SetStreamLoopCount(c->handle, 1);
		}
		cur = msx_FindActiveTrack();
		if (c->bAmbient == 0 && cur != 0) {
			sprintf(g_6b6f90, "Queuing Track %s after Track %s !", c->name, cur->name);
			cur->next = c;
			c->b105 = 1;
			msx_StartTrackFade(cur, 2);
		}
		else {
			sprintf(g_6b6f90, "Starting Track %s !", c->name);
			c->b105 = 0;
			msx_PauseStream(c->handle, 0);
			c->active = 1;
		}
	}
	else if (c->f114 == 2) {
		msx_StartTrackFade(c, 1);
	}
	LeaveCriticalSection(&msx_TrackLock);
	return 0;
}

/* ADDRESS: GOLDDE 0x0041d0e0 */
void __cdecl msx_StopTrack(Chan_14cc460* hTrack, int fade)
{
    if (msx_TrackDriver != 0) {
        EnterCriticalSection(&msx_TrackLock);
        if (hTrack->active != 0) {
            if (fade != 0) {
                msx_StartTrackFade(hTrack, 2);
            } else {
                msx_PauseStream(hTrack->handle, 1);
                msx_CloseStream(hTrack->handle);
                hTrack->handle = 0;
                hTrack->active = 0;
            }
        }
        LeaveCriticalSection(&msx_TrackLock);
    }
}

/* ADDRESS: GOLDDE 0x0041d540 */
Chan_14cc460* __cdecl FindTrackByName(const char* name)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (strcmp(msx_Tracks[i].name, name) == 0) {
			return &msx_Tracks[i];
		}
	}
	return 0;
}

/* ADDRESS: GOLDDE 0x0041d5b0 */
Chan_14cc460* __cdecl msx_FindActiveTrack(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (msx_Tracks[i].bAmbient == 0 && msx_Tracks[i].active != 0) {
			return &msx_Tracks[i];
		}
	}
	return 0;
}

/* ADDRESS: GOLDDE 0x0041d5f0 */
Chan_14cc460* __cdecl FindFreeTrack(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (msx_Tracks[i].active == 0 && msx_Tracks[i].handle == 0 && msx_Tracks[i].f10c == 0) {
			return &msx_Tracks[i];
		}
	}
	for (i = 0; i < 10; i++) {
		if (msx_Tracks[i].active == 0 && msx_Tracks[i].handle == 0) {
			return &msx_Tracks[i];
		}
	}
	return 0;
}

/* ADDRESS: GOLDDE 0x0041d660 */
void __cdecl msx_StartTrackFade(Chan_14cc460* hTrack, int mode)
{
    if (hTrack == 0) {
        return;
    }
    if (hTrack->active == 0) {
        return;
    }
    if (mode == 0) {
        return;
    }
    msx_GetStreamMsPosition(hTrack->handle, &hTrack->f10c);
    hTrack->f110 = hTrack->f10c;
    hTrack->f120 = hTrack->f11c;
    hTrack->f114 = mode;
}

/* ADDRESS: GOLDDE 0x0041d6c0 */
void __cdecl SetTrackPath(const char* path)
{
	strcpy(msx_TrackPath, path);
}

/* ADDRESS: GOLDDE 0x0041d6e0 */
Chan_14cc460* __cdecl msx_StartAmbientTrack(const char* name, int a)
{
	Chan_14cc460* c;

	if (msx_AmbientDriver == 0) {
		return &msx_NullTrack;
	}
	EnterCriticalSection(&msx_TrackLock);
	c = FindTrackByName(name);
	if (c == 0) {
		c = FindFreeTrack();
		if (c != 0) {
			memset(c, 0, sizeof(Chan_14cc460));
			strcpy(c->name, name);
		}
	}
	if (c != 0) {
		c->bAmbient = 1;
		if (c->handle != 0) {
			msx_CloseStream(c->handle);
			c->handle = 0;
		}
		if (msx_StartTrackInternal(c, 1) == 0) {
			msx_SetTrackVolume(c, a);
			LeaveCriticalSection(&msx_TrackLock);
			return c;
		}
	}
	LeaveCriticalSection(&msx_TrackLock);
	return 0;
}

/* ADDRESS: GOLDDE 0x0041d7a0 */
void __cdecl msx_StopAmbientTrack(Chan_14cc460* hTrack)
{
    if (msx_AmbientDriver != 0) {
        if (hTrack->bAmbient == 0) {
            _assert("hTrack->bAmbient", "D:\\develop\\units\\Msx\\msx.c", 0x2e5);
        }
        EnterCriticalSection(&msx_TrackLock);
        msx_StopTrack(hTrack, 0);
        LeaveCriticalSection(&msx_TrackLock);
    }
}
unsigned char _dpad_14611a0[256] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
unsigned char _dpad_14cb8f0[3248];
unsigned char _dpad_14cc5a0[8584];
