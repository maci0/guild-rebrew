

#include <string.h>

// SIZE 0x6a
struct netinfo {
	short a;
	short b;
	short size;
	char name[0x20];
	char mode;
	char pad;
	short port;
	char rest[0x40];
};

extern struct netinfo g_7e2520;
// SIZE 0x70
struct netslot {
	struct netinfo info;
	int x;
};

extern struct netslot g_9baa70;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a3a28[];
extern char g_6a3778[];
extern unsigned char g_7747b0;
extern unsigned char g_6a375c;
extern short g_7e2510;
extern float g_10529c8;
extern float g_10421a0;
extern float g_10432a4;
// SIZE 4
struct shortpair {
	short lo;
	short hi;
};

extern short g_fb9070;

int __cdecl d2_ChoosePlayerCount(void);
void __cdecl d2_ClearBackdropResource(void);
int __cdecl d2_RunChooseCityDialog(int, int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl d3_SetViewport(float, float, float, float, int, int, int, int, int);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_SetBackdropResource(int);

int __cdecl d2_HostNetworkGame(void)
{
	if (d2_ChoosePlayerCount() != 0) {
		d2_ClearBackdropResource();
		if (d2_RunChooseCityDialog(1, 1) != 0) {
			sprintf(g_7e21a0, g_6a3a28, g_6a3778, g_7e1d00);
			strcpy(g_7e2000, "127.0.0.1");
			(*(int*)&g_7747b0) |= 0x10;
			g_7e2520.mode = *(char*) &(*(int*)&g_6a375c);
			g_7e2520.size = 0x6a;
			g_7e2520.a = 1;
			g_7e2520.b = 1;
			g_7e2520.port = g_7e2510;
			strcpy(g_7e2520.name, g_7e1d00);
			g_9baa70.info = g_7e2520;
			g_9baa70.x = 0x3f;
			d3_SetViewport((float) (g_6a376c - g_6a3764), (float) (g_6a3770 - g_6a3768), (float) g_6a3764,
			    (float) g_6a3768, (*(int*)&g_10529c8), (*(int*)&g_10421a0), (*(int*)&g_10432a4), (*(struct shortpair*)&g_fb9070).hi, (*(struct shortpair*)&g_fb9070).lo);
			return 1;
		}
	}
	d2_ClearSurface(g_77250c);
	d2_SetBackdropResource(0x797);
	return 0;
}
