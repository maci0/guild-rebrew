


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

int __cdecl d3snd_SelectVoiceCode(int, int);
char* __cdecl d2_RunSeance(char*, char*);
unsigned short* __cdecl gm_FindMostWantedCrimeTarget(ENTITY_RECORD*, int, int*, int*);
float __cdecl gv_CalcSeanceBonus(char*);
float __cdecl gm_RandomFloat01(void);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl cm_RequestLinkEvidence(int, int);
void __cdecl gm_IncreaseEntityStat(ENTITY_RECORD*, int);
int __cdecl io_AppendText();
unsigned short __cdecl gm_RandomMod(int);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl evt_RequestScriptExit(char*);

/* ADDRESS: GOLDDE 0x005741d0 */
void __cdecl d2_RunSeanceDialog(char* e, char* res)
{
	char* m;
	int list[4];
	unsigned short* p;
	int b;
	int h;
	int t;
	int i;
	int v;
	int cnt;
	float f;

	d3snd_SelectVoiceCode(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	m = d2_RunSeance(e, res);
	p = gm_FindMostWantedCrimeTarget(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 4, list, &cnt);
	b = p == 0;
	f = gv_CalcSeanceBonus(e);
	if (gm_RandomFloat01() + f - 0.1f < 1.0f) {
		b = 2;
	}
	h = d2_LoadForm(0, 0, "Locations\\Friedhof\\Friedhof");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_DialogButtonAction = -1;
	d2_SetForm(h, 1);
	t = d3snd_SelectVoiceCode(*(int*) (res + 0x14), *(int*) (res + 0x4c));
	if (b == 0) {
		for (i = 0; i < cnt; i++) {
			cm_RequestLinkEvidence(list[i], ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id);
		}
		gm_IncreaseEntityStat(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), 1);
		io_AppendText(0x40ef, 0x40cc, *p);
		d3snd_QueueSound(t, 0, "GEIST_KOMMT", gm_RandomMod(8), 0xfa);
	} else if (b == 1) {
		v = (gm_RandomMod(0x200) + 0x200) << 5;
		cm_RequestMoveCredits(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -1, gm_ActiveTownIndex, v);
		io_AppendText(0x40f0, 0x40cc, v);
		d3snd_QueueSound(t, 0, "GEIST_KOMMT", gm_RandomMod(8), 0xfa);
	} else {
		io_AppendText(0x40d3, 0x40cc);
		d3snd_QueueSound(t, 0, "GEIST_KOMMT_NICHT", gm_RandomMod(8), 0xfa);
	}
	do {
		if (io_RightButtonReleased != 0) {
			d2_DialogCloseRequested = 1;
		}
	} while (main_RunFrameLoop(d2_RunSeanceDialog, 0x777c7) != 0);
	d2_DestroyForm(h);
	if (m != 0) {
		evt_RequestScriptExit(m);
	}
}
