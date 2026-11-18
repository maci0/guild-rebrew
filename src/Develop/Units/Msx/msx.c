#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "msx.h"

extern int g_6b719c;
extern char g_6b6f90[];
int __cdecl fcn_0042b2e0(void);
int __cdecl fcn_0042abd0(int* lib, char* path, int* out);
int __cdecl fcn_0042b080(int h, int* len);
int __cdecl fcn_0042ae10(int h, int v);
int __cdecl fcn_0042ad60(int h);
int __cdecl fcn_0042aed0(int h, int pos);
int __cdecl fcn_0042ae90(int h, int f);

void __cdecl fcn_0041fc10(Chan_14cc460* p, int a2)
{
	if (msx_TrackDriver != 0 && p != 0) {
		EnterCriticalSection(&msx_TrackLock);
		p->f118 = a2;
		if (p->f114 == 0 && p->active != 0) {
			p->f11c = a2;
			if (p->handle != 0) {
				fcn_0042ae10(p->handle, a2);
			}
		}
		LeaveCriticalSection(&msx_TrackLock);
	}
}

Chan_14cc460* __cdecl fcn_0041fd70(const char* name, int restart)
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
	if (fcn_0041fe10(c, restart) == -1) {
		c = 0;
	}
	return c;
}

int __cdecl fcn_0041fe10(Chan_14cc460* c, int restart)
{
	char path[0x100];
	int err;
	Chan_14cc460* cur;

	if (((int*)msx_TrackDriver) == 0 || ((int*)msx_AmbientDriver) == 0) {
		return 0;
	}
	EnterCriticalSection(&msx_TrackLock);
	if (g_6b719c != 0) {
		sprintf(g_6b6f90, "Reporting last delaypeak: %d", fcn_0042b2e0());
	}
	else {
		g_6b719c = fcn_0042b2e0();
	}
	if (c->active == 0) {
		strcpy(path, msx_TrackPath);
		strcat(path, c->name);
		if (c->handle == 0) {
			if (c->bAmbient != 0) {
				err = fcn_0042abd0(((int*)msx_AmbientDriver), path, &c->handle);
			}
			else {
				err = fcn_0042abd0(((int*)msx_TrackDriver), path, &c->handle) == -1;
			}
			if (err != 0) {
				LeaveCriticalSection(&msx_TrackLock);
				return -1;
			}
		}
		if (c->f108 == 0) {
			fcn_0042b080(c->handle, &c->f108);
			c->f118 = 0x7f;
		}
		if ((c->bAmbient == 0 && c->f108 - c->f10c < 10000) || c->f10c == 0) {
			c->f10c = 0;
			c->f11c = c->f118;
			c->f114 = 0;
			fcn_0042ae10(c->handle, 0);
			fcn_0042ad60(c->handle);
			fcn_0042ad90(c->handle, 1);
			fcn_0042aed0(c->handle, 0);
			fcn_0042ae10(c->handle, c->f118);
			c->f110 = 0;
		}
		else {
			fcn_0042ad90(c->handle, 1);
			fcn_0042ae10(c->handle, 0);
			fcn_0042aed0(c->handle, c->f10c);
			if (c->bAmbient == 0) {
				c->f11c = 0;
				c->f120 = 0;
				c->f114 = 1;
				c->f110 = c->f10c;
			}
		}
		if (restart != 0) {
			fcn_0042ae90(c->handle, 0);
		}
		else {
			fcn_0042ae90(c->handle, 1);
		}
		cur = fcn_00420650();
		if (c->bAmbient == 0 && cur != 0) {
			sprintf(g_6b6f90, "Queuing Track %s after Track %s !", c->name, cur->name);
			cur->next = c;
			c->b105 = 1;
			fcn_00420700(cur, 2);
		}
		else {
			sprintf(g_6b6f90, "Starting Track %s !", c->name);
			c->b105 = 0;
			fcn_0042ad90(c->handle, 0);
			c->active = 1;
		}
	}
	else if (c->f114 == 2) {
		fcn_00420700(c, 1);
	}
	LeaveCriticalSection(&msx_TrackLock);
	return 0;
}

void __cdecl fcn_00420120(Chan_14cc460* hTrack, int fade)
{
    if (msx_TrackDriver != 0) {
        EnterCriticalSection(&msx_TrackLock);
        if (hTrack->active != 0) {
            if (fade != 0) {
                fcn_00420700(hTrack, 2);
            } else {
                fcn_0042ad90(hTrack->handle, 1);
                fcn_0042ac40(hTrack->handle);
                hTrack->handle = 0;
                hTrack->active = 0;
            }
        }
        LeaveCriticalSection(&msx_TrackLock);
    }
}

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

Chan_14cc460* __cdecl fcn_00420650(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (msx_Tracks[i].bAmbient == 0 && msx_Tracks[i].active != 0) {
			return &msx_Tracks[i];
		}
	}
	return 0;
}

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

void __cdecl fcn_00420700(Chan_14cc460* hTrack, int mode)
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
    fcn_0042b040(hTrack->handle, &hTrack->f10c);
    hTrack->f110 = hTrack->f10c;
    hTrack->f120 = hTrack->f11c;
    hTrack->f114 = mode;
}

void __cdecl SetTrackPath(const char* path)
{
	strcpy(msx_TrackPath, path);
}

Chan_14cc460* __cdecl fcn_00420780(const char* name, int a)
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
			fcn_0042ac40(c->handle);
			c->handle = 0;
		}
		if (fcn_0041fe10(c, 1) == 0) {
			fcn_0041fc10(c, a);
			LeaveCriticalSection(&msx_TrackLock);
			return c;
		}
	}
	LeaveCriticalSection(&msx_TrackLock);
	return 0;
}

void __cdecl fcn_00420840(Chan_14cc460* hTrack)
{
    if (msx_AmbientDriver != 0) {
        if (hTrack->bAmbient == 0) {
            _assert("hTrack->bAmbient", "D:\\develop\\units\\Msx\\msx.c", 0x2e5);
        }
        EnterCriticalSection(&msx_TrackLock);
        fcn_00420120(hTrack, 0);
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
