#include "client_dialog_helpers.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* Auction house dialog. Opens the "Versteigerung" cutscene set, builds the
 * auctioneer and bidder actors, runs the bidding rounds and cleans the
 * scene up again. arg is the auction record: player at +0x30 (bidder
 * count), bidder ids at +0x34, +0x7c and +0x80 the auctioneer data. */

#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_772f3c;
extern char* gm_CityEntity;
extern unsigned char* lpGebaeudePROT;
typedef struct { unsigned char kind; unsigned char unknown01[0x24c]; } Building4e33a0;
extern unsigned short g_774970;

void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
int __cdecl cut_RandMod(int a);
void __cdecl msx_StartMusicIfAllowed(int a);
int __cdecl gm_LookupEntityRecordById(int id);
void* __cdecl fcn_004e4ae0(char* name, int a);
void __cdecl fcn_004e4730(char* name);
void* __cdecl d3_FindSceneObject(int a, int b, int c, char* name);
void __cdecl SelectTextureSet(int a, int b, int c, int d);
void __cdecl d3_TransformPoint(int a, int b, int* c);
void* __cdecl cut_CreateCharacterAtPosition(char* name, int* b);
void __cdecl ch_SetToDummy(int a, int b);
int __cdecl gm_SelectEntityHeadSet(unsigned short a);
void* __cdecl evt_StartGfxScript(char* name, int a);
void __cdecl d3snd_QueueSoundIfAllowed(int id, int bank, char* label, int a, int b);
void __cdecl d2_SetFormVisibility(int dlg, int a);
void __cdecl fcn_00471d80(int dlg, int a);
void __cdecl cut_WaitForScript(int a);
void __cdecl cut_RunTurnRound(int arg, int* ids);
void __cdecl cut_WaitTicks(int a);
int __cdecl gm_GetGuildHall(int a);
int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl cm_SendSetGebBesitzer(int a, int b, int c);
void __cdecl cut_FadeToBlack(void);
void __cdecl evt_StopScriptIfActive(int a);
void __cdecl cut_DestroyActiveCharacter(int a);
void __cdecl cut_CleanupCutscene(void);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl cut_UnloadSampleBank(int a);
void __cdecl fcn_004e4eb0(void);
int __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, unsigned char kind, int amount);

/* ADDRESS: GOLDTL 0x004e33a0 */
void __cdecl cut_RunAuction(int* arg)
{
	char temp[0x200];
	char line[0x40];
	char name[0x40];
	int objs[8];
	int bidders[8];
	int bestFrom;
	int n;
	int argRec;
	int ids[8];
	int price;
	int states[8];
	int escBehavior;
	int bid[4];
	int auctioneer;
	int bank_comments;
	int bank_intro;
	int dlg;
	int npc;
	int building;
	int done;
	int start;
	int besti;
	char label[4];
	int round;
	int bank_bids;
	int result;
	int best;
	int cand;
	int bidCount;
	int i;
	Building4e33a0* proto;
	int* table;
	int other;
	int found;
	int foundName;
	int cur;
	int j;
	void* npc2;

	auctioneer = arg[0x7c / 4];
	npc = (int) gm_StartFilteredEntitySearch(1, 1, auctioneer);
	building = npc;
	besti = -1;
	bid[0] = 0;
	bid[1] = 0;
	bid[2] = 0;
	bid[3] = 0;
	result = cut_RandMod(3);
	msx_StartMusicIfAllowed(0);
	if (npc == 0)
		return;
	proto = &((Building4e33a0*) lpGebaeudePROT)[*(unsigned char*) npc];
	if (proto->kind == 0x0b) {
		fcn_0064d41a(name, (char*) 0x679060, "WALDSTUECK");
	} else if (proto->kind == 0x0d) {
		fcn_0064d41a(name, (char*) 0x679060, "MINE");
	} else if (proto->kind == 0x0c) {
		fcn_0064d41a(name, (char*) 0x679060, "STEINBRUCH");
	} else {
		return;
	}
	n = *(unsigned char*) (((char*) arg) + 0x30);
	argRec = arg[0x7c / 4];
	price = arg[0x80 / 4];
	for (i = 0; i < n; i++) {
		states[i] = 0;
		ids[i] = arg[0x34 / 4 + i];
		bidders[i] = gm_LookupEntityRecordById(ids[i]);
		states[i] = bidders[i] != 0 ? 0 : -1;
	}
	for (; i < 8; i++) {
		bidders[i] = 0;
		states[i] = 0;
		ids[i] = -1;
	}
	bank_intro = (int) fcn_004e4ae0("VERSTEIGERUNG_INTRO.sbf", 0);
	bank_bids = (int) fcn_004e4ae0("VERSTEIGERUNG_GEBOTE.sbf", 0);
	bank_comments = (int) fcn_004e4ae0("VERSTEIGERUNG_KOMMENTARE.sbf", 0);
	fcn_004e4730("Versteigerung.ed3");
	npc = (int) d3_FindSceneObject(0, 0x40, 0, "ub_STAFELEI");
	if (npc != 0) {
		if (proto->kind == 0x0b)
			i = 0;
		else if (proto->kind == 0x0c)
			i = 1;
		else if (proto->kind == 0x0d)
			i = 2;
		else
			return;
		SelectTextureSet(npc, *(int*) ((char*) npc + 0x1cc), i, 1);
	}
	if (result == 0) {
		fcn_0064d41a(line, (char*) 0x679060, "buerger3_DICKER");
		result = -5;
		fcn_0064d41a(label, (char*) 0x679060, "M1");
	} else if (result == 1) {
		fcn_0064d41a(line, (char*) 0x679060, "wirt2_DICKER");
		result = -4;
		fcn_0064d41a(label, (char*) 0x679060, "M2");
	} else {
		fcn_0064d41a(line, (char*) 0x679060, "buergerin2_FRAU");
		result = -2;
		fcn_0064d41a(label, (char*) 0x679060, "W1");
	}
	auctioneer = (int) d3_FindSceneObject(0, 0x100, 0, "dummy_AUKTIONATOR");
	if (auctioneer != 0)
		d3_TransformPoint(auctioneer, auctioneer + 0x4c, bid);
	auctioneer = (int) cut_CreateCharacterAtPosition(line, bid);
	if (auctioneer != 0) {
		ch_SetToDummy(auctioneer, npc);
		strcpy((char*) auctioneer + 8, "Auktionator");
		strcpy(*(char**) ((char*) auctioneer + 0x34), "Auktionator");
	}
	for (i = 0; i < n; i++) {
		fcn_0064d41a(temp, (char*) 0x68d428, i);
		npc2 = d3_FindSceneObject(0, 0x100, 0, temp);
		if (npc2 != 0)
			d3_TransformPoint((int) npc2, (int) npc2 + 0x4c, bid);
		foundName = bidders[i] != 0 ? gm_SelectEntityHeadSet(*(unsigned short*) (char*) bidders[i]) : 0;
		if (bidders[i] != 0 && foundName != 0) {
			fcn_0064d41a(temp, (char*) 0x679060,
			    (char*) (foundName + 4));
		} else {
			switch (cut_RandMod(3)) {
			case 1:
				strcpy(temp, "buerger_MANN");
				break;
			case 2:
				strcpy(temp, "buerger2_MANN");
				break;
			default:
				strcpy(temp, "handwerker3_MANN");
				break;
			}
		}
		if (bidders[i] != 0) {
			objs[i] = (int) cut_CreateCharacterAtPosition(temp, bid);
			ch_SetToDummy(objs[i], (int) npc2);
		} else {
			objs[i] = 0;
		}
	}
	escBehavior = (int) evt_StartGfxScript(
	    "cutscenes\\auktion\\behavior_auktionator.esc", 0x6b5c60);
	cand = (int) evt_StartGfxScript("cutscenes\\auktion\\Enterfly_auktion.esc",
	    0x6b5c60);
	fcn_0064d41a(temp, (char*) 0x68d3b8, label);
	d3snd_QueueSoundIfAllowed(-7, bank_intro, temp, -1, 0);
	fcn_0064d41a(temp, (char*) 0x68d3a0, name);
	d3snd_QueueSoundIfAllowed(result, bank_intro, temp, cut_RandMod(3), 500);
	dlg = (int) d2_LoadForm(0, 0, "cutscenes\\pacht_main");
	if (g_772f3c != 0)
		d2_SetFormVisibility(dlg, 0);
	fcn_00471d80(dlg, 3);
	d2_SetForm(dlg, 0);
	io_AppendText((void*) 0x1aa2, (void*) building, (void*) price);
	cut_WaitForScript(cand);
	round = 0;
	done = 0;
	start = 10;
	while (start > 5) {
		if (done != 0)
			break;
		best = 0;
		bestFrom = start;
		cut_RunTurnRound((int) arg, states);
		if (start > 6 && cut_RandMod(3) != 0)
			d3snd_QueueSoundIfAllowed(cut_RandMod(4) != 0 ? -4 : -2,
			    bank_comments, "_VERSTEIGERUNG_KOMMENTARE",
			    cut_RandMod(6), cut_RandMod(0x200) + 0x32);
		bidCount = 0;
		n = *(unsigned char*) (((char*) arg) + 0x30);
		table = (int*) 0x9b0eb4;
		for (i = 0; i < n; i++) {
			if (table[1] != 0 && bidders[i] != 0) {
				states[i] = table[0];
				if (table[0] > best) {
					best = table[0];
					besti = i;
					price = table[0];
				}
				bidCount++;
			} else {
				states[i] = -1;
			}
			table = (int*) ((char*) table + 0x35c);
		}
		if (bidCount < 2) {
			done = 1;
		} else if (start > 6) {
			n = (int) ((unsigned) n >> 1);
			if (bidCount < n) {
				d3snd_QueueSoundIfAllowed(result, bank_bids,
				    "_VERSTEIGERUNG_GEBOTE",
				    cut_RandMod(4) + 2, 500);
			} else {
				d3snd_QueueSoundIfAllowed(result, bank_bids,
				    "_VERSTEIGERUNG_GEBOTE",
				    cut_RandMod(2), 500);
			}
			price += 0x20;
			d2_SetForm(dlg, 0);
			io_AppendText((void*) 0x1aa3, (void*) building,
			    (void*) (round + 2), (void*) 5,
			    (void*) bidCount, (void*) states[besti]);
		}
		cut_WaitTicks(5);
		round++;
		start--;
	}
	if (besti < 0) {
		d3snd_QueueSoundIfAllowed(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 7,
		    200);
		d2_SetForm(dlg, 0);
		io_AppendText((void*) 0x1aa5, (void*) building);
		if (arg[3] == *(int*) (&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short)g_774970]
		    .entity_id)) {
			cm_SendSetGebBesitzer(*(int*) ((char*) building + 1),
			    *(int*) (gm_CityEntity + 4),
			    *(int*) (gm_CityEntity + 4));
		}
	} else {
		d3snd_QueueSoundIfAllowed(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 6,
		    200);
		d2_SetForm(dlg, 0);
		io_AppendText((void*) 0x1aa4,
		    (void*) (*(unsigned short*) (char*) bidders[besti]),
		    (void*) price);
		if (arg[3] == *(int*) (&((ENTITY_RECORD*)g_7f4ca0)[(unsigned short)g_774970]
		    .entity_id)) {
						found = 0;
			for (j = 0; j < 0x300; j++) {
				if (((char*)&((ENTITY_RECORD*)g_7f4ca0)[j])[0x166] == 0x0b) {
					found = (int) (((char*)&((ENTITY_RECORD*)g_7f4ca0)[j]));
					break;
				}
			}
			cur = *(int*) 0x7f4c00;
			cm_BeginPacketFieldDelta((char*) building, *(int*) ((char*) building + 1));
			cm_AppendPacketFieldDelta(4, 1, 0x69, &done);
			cm_AppendPacketFieldDelta(4, 1, 0x6d, &cur);
			cm_RequestChangeAttribute();
			cm_SendSetGebBesitzer(*(int*) ((char*) building + 1),
			    *(int*) (gm_CityEntity + 4),
			    *(int*) ((char*) bidders[besti] + 4));
			other = (int) gm_GetGuildHall(1);
			other = fcn_00502cd0(*(int*) ((char*) other + 0x5d), 2, 6, 0, 0x115);
			if (found == bidders[besti]) {
				cm_RequestTransferCurrencyNoKill(*(int*) ((char*) other + 2),
				    *(int*) ((char*) bidders[besti] + 4), 0,
				    (int) (states[besti]
				    * *(float*) 0x664090));
			} else if (found != 0) {
				cm_RequestTransferCurrencyNoKill(*(int*) ((char*) other + 2),
				    *(int*) ((char*) bidders[besti] + 4), 0,
				    (int) (states[besti]
				    * *(float*) 0x664090));
				cm_RequestTransferCurrencyNoKill(*(int*) (found + 4),
				    *(int*) ((char*) bidders[besti] + 4), 0,
				    (int) (states[besti]
				    * *(float*) 0x662a3c));
			} else {
				cm_RequestTransferCurrencyNoKill(*(int*) ((char*) other + 2),
				    *(int*) ((char*) bidders[besti] + 4), 0,
				    states[besti]);
			}
		}
	}
	d3snd_QueueSoundIfAllowed(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 8, 500);
	cand = (int) evt_StartGfxScript("cutscenes\\auktion\\Auktion_Outro.esc",
	    0x6b5c60);
	cut_WaitForScript(cand);
	d2_DestroyForm(dlg);
	cut_FadeToBlack();
	evt_StopScriptIfActive(escBehavior);
	cut_WaitForScript(escBehavior);
	for (i = 0; i < *(unsigned char*) ((char*) arg + 0x30); i++) {
		if (objs[i] != 0)
			cut_DestroyActiveCharacter(objs[i]);
	}
	if (auctioneer != 0)
		cut_DestroyActiveCharacter(auctioneer);
	cut_CleanupCutscene();
	d3snd_StopTrackedVoices();
	cut_UnloadSampleBank(bank_intro);
	cut_UnloadSampleBank(bank_bids);
	cut_UnloadSampleBank(bank_comments);
	fcn_004e4eb0();
}
