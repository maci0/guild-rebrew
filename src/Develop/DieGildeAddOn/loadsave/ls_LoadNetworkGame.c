


#include <stdio.h>

// SIZE 0x7c
typedef struct {
	int who;
	char pad4[0x7c - 4];
} Msg;

extern char g_6a1ea4[];
extern char g_6a1e8c[];
extern char* g_14ac600;
extern unsigned char gm_PlayerCount;
extern int nt_NetSyncFlags;
extern char* g_14ac5f0;
extern char* g_14ac5fc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ShowNetworkLoadStatus(char* s);
void __cdecl main_PumpWindowMessages(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl ls_SendGame(char* s);
void __cdecl cm_RequestSysMessage(int kind, Msg* m);
void __cdecl ls_LoadSavegame(char* s, int n);
void __cdecl sv_WaitForNetworkSync(int v);
void __cdecl init_LocalData(void);

/* ADDRESS: GOLDDE 0x004ff4c0 */
int __cdecl ls_LoadNetworkGame(char* name)
{
	Msg msg;
	char save[260];
	char path[260];
	char text[512];

	sprintf(path, g_6a1ea4, name);
	sprintf(text, g_14ac600, gm_PlayerCount);
	d2_ShowNetworkLoadStatus(text);
	nt_NetSyncFlags = 0;
	do {
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	} while (nt_NetSyncFlags == 0);
	if (nt_NetSyncFlags & 1) {
		sprintf(save, g_6a1e8c, name);
		d2_ShowNetworkLoadStatus(g_14ac5f0);
		if (ls_SendGame(save) == 0) {
			return 1;
		}
		if (nt_NetSyncFlags & 1) {
			msg.who = gm_PlayerCount;
			cm_RequestSysMessage(6, &msg);
		}
	}
	while (!(nt_NetSyncFlags & 4)) {
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	}
	ls_LoadSavegame(path, 5);
	sv_WaitForNetworkSync(0x24087);
	d2_ShowNetworkLoadStatus(g_14ac5fc);
	init_LocalData();
	d2_SuppressOverlay = 0;
	return 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_774800[332];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_774810[8];
unsigned char _dpad_774828[264];
#endif
