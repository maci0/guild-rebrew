


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

extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char g_6a96d8[];
extern char g_6a9828[];
extern char g_6a9814[];
extern float g_6628d8;
extern float flt_1_0;
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

		amt = MIN(MAX((int) (gm_WalkEntityChain(gm_LocalPlayerSlot) * 0.25f), 0x27100), 0xc3500);
		cm_RequestMoveCredits(((struct house*)gm_EntitySlotTable)[gm_LocalPlayerSlot].handle, -1, gm_ActiveTownIndex, amt);
		memset(ev, 0, sizeof(ev));
		ev[4] = (char) 0x8e;
		*(int*) (ev + 8) = ((struct house*)gm_EntitySlotTable)[gm_LocalPlayerSlot].handle;
		*(int*) (ev + 0xc) = *(int*) (e + 1);
		*(int*) (ev + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (ev + 0x2c) = (*(int*)&gm_GameTimeHour);
		*(int*) (ev + 0x30) = gm_GameTimeSliceDword;
		*(short*) (ev + 0x34) = gm_GameTimeTailWord;
		ev[0x36] = 1;
		*(int*) (ev + 0x58) = amt;
		cm_SendCopyEntityData(ev);
		gm_IncreaseEntityStat(&((struct house*)gm_EntitySlotTable)[gm_LocalPlayerSlot], 3);
	}
	h = d2_LoadForm(0, 0, g_6a96d8);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_DialogButtonAction = -1;
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
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_RunSeanceTreasureDialog, 0x777c7) != 0);
	d2_DestroyForm(h);
	if (m != 0) {
		evt_RequestScriptExit(m);
	}
}
