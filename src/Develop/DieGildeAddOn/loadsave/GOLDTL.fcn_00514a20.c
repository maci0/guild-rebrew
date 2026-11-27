


#include <stdio.h>

// SIZE 0x7c
typedef struct {
	int who;
	char pad4[0x7c - 4];
} Msg;

extern char g_6a1ea4[];
extern char g_6a1e8c[];
extern char* g_14ac600;
extern unsigned char g_6a375c;
extern int g_77494c;
extern char* g_14ac5f0;
extern char* g_14ac5fc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00514570(char* s);
void __cdecl main_PumpWindowMessages(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl ls_SendGame(char* s);
void __cdecl cm_RequestSysMessage(int kind, Msg* m);
void __cdecl ls_LoadSavegame(char* s, int n);
void __cdecl sv_WaitForNetworkSync(int v);
void __cdecl init_LocalData(void);

int __cdecl ls_LoadNetworkGame(char* name)
{
	Msg msg;
	char save[260];
	char path[260];
	char text[512];

	sprintf(path, g_6a1ea4, name);
	sprintf(text, g_14ac600, g_6a375c);
	fcn_00514570(text);
	g_77494c = 0;
	do {
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	} while (g_77494c == 0);
	if (g_77494c & 1) {
		sprintf(save, g_6a1e8c, name);
		fcn_00514570(g_14ac5f0);
		if (ls_SendGame(save) == 0) {
			return 1;
		}
		if (g_77494c & 1) {
			msg.who = g_6a375c;
			cm_RequestSysMessage(6, &msg);
		}
	}
	while (!(g_77494c & 4)) {
		main_PumpWindowMessages();
		cm_StepCommandQueue();
	}
	ls_LoadSavegame(path, 5);
	sv_WaitForNetworkSync(0x24087);
	fcn_00514570(g_14ac5fc);
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
