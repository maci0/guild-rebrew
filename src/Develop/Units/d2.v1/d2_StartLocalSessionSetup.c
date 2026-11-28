

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

extern struct netinfo nt_LocalSessionInfo;
// SIZE 0x70
struct netslot {
	struct netinfo info;
	int x;
};

extern struct netslot g_9baa70;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a3a28[];
extern char g_6a3778[];
extern unsigned char gm_ClientModeFlags;
extern unsigned char gm_PlayerCount;
extern short nt_ServerPort;
extern float d3_ViewportZNear;
extern float d3_ViewportZFar;
extern float d3_ProjectionDist;
extern int g_1040494;
extern int d2_ScreenHeight;
extern int d2_ScreenSurface;

int __cdecl d2_ChoosePlayerCount(void);
void __cdecl d2_ClearBackdropResource(void);
int __cdecl d2_RunChooseCityDialog(int, int);
int __cdecl sprintf(char*, const char*, ...);
void __cdecl d3_SetViewport(float, float, float, float, int, int, int, int, int);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_SetBackdropResource(int);

int __cdecl d2_StartLocalSessionSetup(void)
{
	if (d2_ChoosePlayerCount() != 0) {
		d2_ClearBackdropResource();
		if (d2_RunChooseCityDialog(1, 1) != 0) {
			sprintf(g_7e21a0, g_6a3a28, g_6a3778, g_7e1d00);
			strcpy(g_7e2000, "127.0.0.1");
			(*(int*)&gm_ClientModeFlags) |= 0x10;
			nt_LocalSessionInfo.mode = *(char*) &(*(int*)&gm_PlayerCount);
			nt_LocalSessionInfo.size = 0x6a;
			nt_LocalSessionInfo.a = 1;
			nt_LocalSessionInfo.b = 1;
			nt_LocalSessionInfo.port = nt_ServerPort;
			strcpy(nt_LocalSessionInfo.name, g_7e1d00);
			g_9baa70.info = nt_LocalSessionInfo;
			g_9baa70.x = 0x3f;
			d3_SetViewport((float) (g_6a376c - g_6a3764), (float) (g_6a3770 - g_6a3768), (float) g_6a3764,
			    (float) g_6a3768, (*(int*)&d3_ViewportZNear), (*(int*)&d3_ViewportZFar), (*(int*)&d3_ProjectionDist), g_1040494, d2_ScreenHeight);
			return 1;
		}
	}
	d2_ClearSurface(d2_ScreenSurface);
	d2_SetBackdropResource(0x797);
	return 0;
}
