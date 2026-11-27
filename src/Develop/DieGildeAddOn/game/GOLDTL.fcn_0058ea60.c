


#include <string.h>

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x10
struct offer {
	int id;
	int taken;
	int pad8;
	int padc;
};

// SIZE 0xc
struct level {
	int n;
	int total;
	int x;
};


#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"

int __cdecl d3snd_SelectVoiceCode(int, int);
char* __cdecl d2_RunSeance(char*, char*);
void __cdecl gm_CheckEntityObjectSlots(ENTITY_RECORD*, int, struct offer*, struct level*);
float __cdecl gv_CalcSeanceBonus(char*);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl gm_IncreaseEntityStat(ENTITY_RECORD*, int);
int __cdecl io_AppendText();
unsigned short __cdecl gm_RandomMod(int);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl evt_RequestScriptExit(char*);

void __cdecl d2_RunSeanceItemsDialog(char* e, char* res)
{
	char* m;
	float f;
	struct level lv;
	struct offer list[15];
	int mode;
	int id;
	int t;
	int h;
	int i;
	int v;

	id = 0;
	t = d3snd_SelectVoiceCode(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = d2_RunSeance(e, res);
	memset(list, 0, sizeof(list));
	list[0].id = 0x2b8;
	list[1].id = 0x2bb;
	list[2].id = 0x2bc;
	list[3].id = 0x2bf;
	list[4].id = 0x2c2;
	list[5].id = 0x2c3;
	list[6].id = 0x2bd;
	list[7].id = 0x2c1;
	list[8].id = 0x2c4;
	list[9].id = 0x2c5;
	list[10].id = 0x2c6;
	list[11].id = 0x2ba;
	list[12].id = 0x2c0;
	list[13].id = 0x2be;
	list[14].id = 0x2b9;
	gm_CheckEntityObjectSlots(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), 0xf, list, &lv);
	if ((lv.n == 6 && lv.x == 0) || lv.total == 0xf) {
		mode = 1;
	} else {
		i = gm_RandomMod(0xf);
		while (list[i].taken != 0) {
			i = (i + 1) % 0xf;
		}
		id = list[i].id;
		mode = 0;
	}
	f = gv_CalcSeanceBonus(e);
	if (gm_RandomFloat01() + f - 0.2f < 1.0f) {
		mode = 2;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	fcn_005340f0(d2_CurrentWindowId);
	g_100f1dc = -1;
	d2_SetForm(h, 1);
	if (mode == 0) {
		cm_SendSellObjekt(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, -1, id, 1, g_773d75, 0);
		gm_IncreaseEntityStat(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), 2);
		io_AppendText(0x40f2, 0x40cc, id * 2 + 0x9a8);
		d3snd_PlaySoundEffect(t, 0, "GEIST_KOMMT", gm_RandomMod(8));
	} else if (mode == 1) {
		v = (gm_RandomMod(0x400) + 1000) << 5;
		cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id, -1, g_773d75, v);
		io_AppendText(0x40f3, 0x40cc, v);
		d3snd_PlaySoundEffect(t, 0, "GEIST_KOMMT", gm_RandomMod(8));
	} else {
		io_AppendText(0x40d3, 0x40cc);
		d3snd_PlaySoundEffect(t, 0, "GEIST_KOMMT_NICHT", gm_RandomMod(8));
	}
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (main_RunFrameLoop(d2_RunSeanceItemsDialog, 0x777c7) != 0);
	d2_DestroyForm(h);
	if (m != 0) {
		evt_RequestScriptExit(m);
	}
}
