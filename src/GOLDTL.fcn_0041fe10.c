// FUNCTION: GOLDTL 0x0041fe10
// SIZE: 699

#include <stdio.h>
#include <string.h>
#include <windows.h>

// SIZE 0x128
typedef struct Chan {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char queued;
	unsigned char music;
	unsigned char b107;
	int length;
	int pos;
	int start;
	int state;
	int volume;
	int vol_now;
	int vol_target;
	struct Chan* next;
} Chan;

extern int g_6b71a4;
extern int g_6b71a8;
extern int g_6b719c;
extern char g_6b6f90[];
extern char g_14cc360[];
extern CRITICAL_SECTION g_14cc5a0;

int __cdecl fcn_0042b2e0(void);
int __cdecl fcn_0042abd0(int* lib, char* path, int* out);
int __cdecl fcn_0042b080(int h, int* len);
int __cdecl fcn_0042ae10(int h, int v);
int __cdecl fcn_0042ad60(int h);
int __cdecl fcn_0042ad90(int h, int f);
int __cdecl fcn_0042aed0(int h, int pos);
int __cdecl fcn_0042ae90(int h, int f);
Chan* __cdecl fcn_00420650(void);
void __cdecl fcn_00420700(Chan* c, int mode);

int __cdecl fcn_0041fe10(Chan* c, int restart)
{
	char path[0x100];
	int err;
	Chan* cur;

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
			if (c->music != 0) {
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
		if (c->length == 0) {
			fcn_0042b080(c->handle, &c->length);
			c->volume = 0x7f;
		}
		if ((c->music == 0 && c->length - c->pos < 10000) || c->pos == 0) {
			c->pos = 0;
			c->vol_now = c->volume;
			c->state = 0;
			fcn_0042ae10(c->handle, 0);
			fcn_0042ad60(c->handle);
			fcn_0042ad90(c->handle, 1);
			fcn_0042aed0(c->handle, 0);
			fcn_0042ae10(c->handle, c->volume);
			c->start = 0;
		}
		else {
			fcn_0042ad90(c->handle, 1);
			fcn_0042ae10(c->handle, 0);
			fcn_0042aed0(c->handle, c->pos);
			if (c->music == 0) {
				c->vol_now = 0;
				c->vol_target = 0;
				c->state = 1;
				c->start = c->pos;
			}
		}
		if (restart != 0) {
			fcn_0042ae90(c->handle, 0);
		}
		else {
			fcn_0042ae90(c->handle, 1);
		}
		cur = fcn_00420650();
		if (c->music == 0 && cur != 0) {
			sprintf(g_6b6f90, "Queuing Track %s after Track %s !", c->name, cur->name);
			cur->next = c;
			c->queued = 1;
			fcn_00420700(cur, 2);
		}
		else {
			sprintf(g_6b6f90, "Starting Track %s !", c->name);
			c->queued = 0;
			fcn_0042ad90(c->handle, 0);
			c->active = 1;
		}
	}
	else if (c->state == 2) {
		fcn_00420700(c, 1);
	}
	LeaveCriticalSection(&g_14cc5a0);
	return 0;
}
