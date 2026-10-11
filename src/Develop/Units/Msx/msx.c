#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "msx.h"

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

void __cdecl fcn_00420120(Chan_14cc460* hTrack, int fade)
{
    if (g_6b71a4 != 0) {
        EnterCriticalSection(&g_14cc5a0);
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
        LeaveCriticalSection(&g_14cc5a0);
    }
}

void __cdecl fcn_00420840(Chan_14cc460* hTrack)
{
    if (g_6b71a8 != 0) {
        if (hTrack->bAmbient == 0) {
            _assert("hTrack->bAmbient", "D:\\develop\\units\\Msx\\msx.c", 0x2e5);
        }
        EnterCriticalSection(&g_14cc5a0);
        fcn_00420120(hTrack, 0);
        LeaveCriticalSection(&g_14cc5a0);
    }
}

Chan_14cc460* __cdecl FindTrackByName(const char* name)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (strcmp(g_6b71b0[i].name, name) == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}

Chan_14cc460* __cdecl FindFreeTrack(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0 && g_6b71b0[i].f10c == 0) {
			return &g_6b71b0[i];
		}
	}
	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].active == 0 && g_6b71b0[i].handle == 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}


Chan_14cc460* __cdecl fcn_0041fd70(const char* name, int a)
{
	Chan_14cc460* c;

	if (g_6b71a4 == 0) {
		return &g_14cc460;
	}
	EnterCriticalSection(&g_14cc5a0);
	c = FindTrackByName(name);
	LeaveCriticalSection(&g_14cc5a0);
	if (c == 0) {
		EnterCriticalSection(&g_14cc5a0);
		c = FindFreeTrack();
		if (c != 0) {
			memset(c, 0, sizeof(Chan_14cc460));
			strcpy(c->name, name);
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
	c->bAmbient = 0;
	if (fcn_0041fe10(c, a) == -1) {
		c = 0;
	}
	return c;
}

Chan_14cc460* __cdecl fcn_00420780(const char* name, int a)
{
	Chan_14cc460* c;

	if (g_6b71a8 == 0) {
		return &g_14cc460;
	}
	EnterCriticalSection(&g_14cc5a0);
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
			LeaveCriticalSection(&g_14cc5a0);
			return c;
		}
	}
	LeaveCriticalSection(&g_14cc5a0);
	return 0;
}

Chan_14cc460* __cdecl fcn_00420650(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (g_6b71b0[i].bAmbient == 0 && g_6b71b0[i].active != 0) {
			return &g_6b71b0[i];
		}
	}
	return 0;
}




extern int g_6b719c;
extern char g_6b6f90[];

int __cdecl fcn_0042b2e0(void);
int __cdecl fcn_0042abd0(int* lib, char* path, int* out);
int __cdecl fcn_0042b080(int h, int* len);
int __cdecl fcn_0042ae10(int h, int v);
int __cdecl fcn_0042ad60(int h);
int __cdecl fcn_0042aed0(int h, int pos);
int __cdecl fcn_0042ae90(int h, int f);

int __cdecl fcn_0041fe10(Chan_14cc460* c, int restart)
{
	char path[0x100];
	int err;
	Chan_14cc460* cur;

	if (((int*)g_6b71a4) == 0 || ((int*)g_6b71a8) == 0) {
		return 0;
	}
	EnterCriticalSection(&g_14cc5a0);
	if (g_6b719c != 0) {
		sprintf(g_6b6f90, "Reporting last delaypeak: %d", fcn_0042b2e0());
	}
	else {
		g_6b719c = fcn_0042b2e0();
	}
	if (c->active == 0) {
		strcpy(path, g_14cc360);
		strcat(path, c->name);
		if (c->handle == 0) {
			if (c->bAmbient != 0) {
				err = fcn_0042abd0(((int*)g_6b71a8), path, &c->handle);
			}
			else {
				err = fcn_0042abd0(((int*)g_6b71a4), path, &c->handle) == -1;
			}
			if (err != 0) {
				LeaveCriticalSection(&g_14cc5a0);
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
	LeaveCriticalSection(&g_14cc5a0);
	return 0;
}
void __cdecl fcn_0041fc10(Chan_14cc460* p, int a2)
{
	if (g_6b71a4 != 0 && p != 0) {
		EnterCriticalSection(&g_14cc5a0);
		p->f118 = a2;
		if (p->f114 == 0 && p->active != 0) {
			p->f11c = a2;
			if (p->handle != 0) {
				fcn_0042ae10(p->handle, a2);
			}
		}
		LeaveCriticalSection(&g_14cc5a0);
	}
}

void __cdecl SetTrackPath(const char* path)
{
	strcpy(g_14cc360, path);
}
