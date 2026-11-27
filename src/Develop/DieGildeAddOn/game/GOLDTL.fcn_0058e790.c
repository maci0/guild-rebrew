


#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
extern int d2_CurrentWindowId;
extern int g_100f1dc;
extern int g_14ce8e0;
#include "client_dialog_state.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_6a96d8[];
extern char g_6a9828[];
extern char g_6a9814[];
extern float g_6628d8;
extern float g_6628a0;
extern float g_6628bc;

int __cdecl d3snd_SelectVoiceCode(int, int);
char* __cdecl d2_RunSeance(char*, char*);
float __cdecl gv_CalcSeanceBonus(char*);
float __cdecl gm_RandomFloat01(void);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl gm_IncreaseEntityStat(struct house*, int);
int __cdecl io_AppendText();
unsigned short __cdecl gm_RandomMod(int);
int __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
void __cdecl cm_SendCopyEntityData(char* msg);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl evt_RequestScriptExit(char*);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl d2_RunSeanceTreasureDialog(char* e, char* res)
{
	float f;
	int t;
	char* m;
	int mode;
	int amt;
	int h;

	amt = 0;
	mode = 0;
	t = d3snd_SelectVoiceCode(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = d2_RunSeance(e, res);
	f = gv_CalcSeanceBonus(e);
	if (gm_RandomFloat01() + f - 0.4f < 1.0f) {
		mode = 2;
	}
	else {
		char ev[0xf8];

		amt = MIN(MAX((int) (gm_WalkEntityChain(g_774970) * 0.25f), 0x27100), 0xc3500);
		cm_RequestMoveCredits(((struct house*)g_7f4ca0)[g_774970].handle, -1, g_773d75, amt);
		memset(ev, 0, sizeof(ev));
		ev[4] = (char) 0x8e;
		*(int*) (ev + 8) = ((struct house*)g_7f4ca0)[g_774970].handle;
		*(int*) (ev + 0xc) = *(int*) (e + 1);
		*(int*) (ev + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (ev + 0x2c) = (*(int*)&g_7f4c04);
		*(int*) (ev + 0x30) = g_7f4c08;
		*(short*) (ev + 0x34) = g_7f4c0c;
		ev[0x36] = 1;
		*(int*) (ev + 0x58) = amt;
		cm_SendCopyEntityData(ev);
		gm_IncreaseEntityStat(&((struct house*)g_7f4ca0)[g_774970], 3);
	}
	h = d2_LoadForm(0, 0, g_6a96d8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	g_100f1dc = -1;
	d2_SetForm(h, 1);
	if (mode == 0) {
		d3snd_QueueSound(t, 0, g_6a9828, gm_RandomMod(8), 0xfa);
		io_AppendText(0x40f1, 0x40cc, amt);
	}
	else {
		d3snd_QueueSound(t, 0, g_6a9814, gm_RandomMod(8), 0xfa);
		io_AppendText(0x40d3, 0x40cc);
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_RunSeanceTreasureDialog, 0x777c7) != 0);
	d2_DestroyForm(h);
	if (m != 0) {
		evt_RequestScriptExit(m);
	}
}
