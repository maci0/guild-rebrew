#include "client_dialog_helpers.h"

/* Auction house dialog. Opens the "Versteigerung" cutscene set, builds the
 * auctioneer and bidder actors, runs the bidding rounds and cleans the
 * scene up again. arg is the auction record: player at +0x30 (bidder
 * count), bidder ids at +0x34, +0x7c and +0x80 the auctioneer data. */

extern short g_774970;
extern int g_772f3c;
extern int g_772d28;
extern int g_772d1c;
extern int g_772d24;
extern int g_774930;
extern int g_773da8;
extern unsigned char g_772d10;
extern unsigned char g_772d14;

void* __cdecl gm_StartFilteredEntitySearch(int a);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
int __cdecl _ftol(void);
int __cdecl fcn_004e6cb0(int a, ...);
void __cdecl fcn_004e4e90(int a);
int __cdecl gm_LookupEntityRecordById(int id);
void* __cdecl fcn_004e4ae0(char* name, int a);
void __cdecl fcn_004e4730(char* name);
void* __cdecl fcn_00445600(int a, int b, int c, char* name);
void __cdecl SelectTextureSet(int a, int b, int c, int d);
void __cdecl fcn_00455350(int a, int b, int* c);
void* __cdecl fcn_004e4a80(char* name, int* b);
void __cdecl fcn_00402b00(int a, int b);
int __cdecl fcn_004fda30(short a);
void* __cdecl fcn_004e44b0(char* name, int a);
void __cdecl fcn_004e4b40(int id, int bank, char* label, int a, int b);
void __cdecl fcn_00471af0(int dlg, int a);
void __cdecl fcn_00471d80(int dlg, int a);
void __cdecl fcn_004e44f0(int a);
void __cdecl fcn_004e51d0(int arg, int* ids);
void __cdecl fcn_004e4c90(int a);
int __cdecl fcn_0050e4a0(int a);
int __cdecl fcn_00502cd0(int a, int b, int c, int d);
void __cdecl fcn_004c5f60(int a, int b, int c);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(int a);
void __cdecl fcn_004e4aa0(int a);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_004e4b00(int a);
void __cdecl fcn_004c24c0(void);

/* ADDRESS: GOLDTL 0x004e33a0 */
void __cdecl fcn_004e33a0(int* arg)
{
	char kind;
	char name[0x3c];
	char line[0x3c];
	char label[0x3c];
	int bidders[8];
	short ids[8];
	int states[8];
	void* objs[8];
	void* actors[8];
	int bank_intro;
	int bank_bids;
	int bank_comments;
	void* dlg;
	void* auctioneer;
	int i;
	int n;
	int best;
	int besti;
	int bid;
	int round;
	int start;
	int result;
	int price;
	void* npc;
	int anim;
	int model;
	int cand;
	short* other;

	bank_intro = 0;
	bank_bids = 0;
	bank_comments = 0;
	dlg = 0;
	auctioneer = 0;
	best = -1;
	besti = -1;
	bid = 0;
	start = 10;
	price = 0;
	round = 0;
	anim = 0;
	result = 0;
	for (i = 0; i < 8; i++) {
		bidders[i] = 0;
		ids[i] = 0;
		states[i] = 0;
		objs[i] = 0;
		actors[i] = 0;
	}
	npc = gm_StartFilteredEntitySearch(1);
	model = fcn_004e6cb0(3, 1, 1, arg[0x7c / 4]);
	fcn_004e4e90(0);
	if (npc == 0)
		return;
	kind = *(char*) ((*(int*) 0x868050 + *(unsigned char*) npc)
	    + *(unsigned char*) npc * 0x24c);
	if (kind == 0x0b) {
		strcpy(label, "WALDSTUECK");
	} else if (kind == 0x0d) {
		strcpy(label, "MINE");
	} else if (kind == 0x0c) {
		strcpy(label, "STEINBRUCH");
	} else {
		return;
	}
	fcn_0064d41a(name, (char*) 0x679060, label);
	n = *(unsigned char*) (((char*) arg) + 0x30);
	for (i = 0; i < n && i < 8; i++) {
		bidders[i] = gm_LookupEntityRecordById(arg[8 + i]);
		ids[i] = (short) arg[8 + i];
		states[i] = bidders[i] != 0 ? -1 : 0;
	}
	bank_intro = (int) fcn_004e4ae0("VERSTEIGERUNG_INTRO.sbf", 0);
	bank_bids = (int) fcn_004e4ae0("VERSTEIGERUNG_GEBOTE.sbf", 0);
	bank_comments = (int) fcn_004e4ae0("VERSTEIGERUNG_KOMMENTARE.sbf", 0);
	fcn_004e4730("Versteigerung.ed3");
	npc = fcn_00445600(0, 0x40, 0, "ub_STAFELEI");
	anim = 0;
	if (npc != 0) {
		if (kind == 0x0b)
			anim = 0;
		else if (kind == 0x0c)
			anim = 1;
		else if (kind == 0x0d)
			anim = 2;
		else
			return;
		SelectTextureSet((int) npc, 0, anim, 1);
	}
	if (model == 0) {
		fcn_0064d41a(line, (char*) 0x679060,
		    (void*) 0x67fa28);
		result = -5;
	} else if (model == 1) {
		fcn_0064d41a(line, (char*) 0x679060,
		    (void*) 0x68d470);
		result = -4;
	} else {
		fcn_0064d41a(line, (char*) 0x679060,
		    (void*) 0x68d45c);
		result = -2;
	}
	if (model == 0)
		fcn_0064d41a(label, (char*) 0x679060, (void*) 0x68d480);
	else if (model == 1)
		fcn_0064d41a(label, (char*) 0x679060, (void*) 0x68d46c);
	else
		fcn_0064d41a(label, (char*) 0x679060, (void*) 0x68d458);
	auctioneer = fcn_00445600(0, 0x100, 0, "dummy_AUKTIONATOR");
	if (auctioneer != 0)
		fcn_00455350((int) auctioneer, (int) auctioneer + 0x4c, &bid);
	auctioneer = fcn_004e4a80(line, &bid);
	if (auctioneer != 0) {
		fcn_00402b00((int) auctioneer, (int) npc);
		*(int*) ((char*) auctioneer + 8) = 0x746b7541;
		*(int*) ((char*) auctioneer + 0x0c) = 0x616e6f69;
		*(int*) ((char*) auctioneer + 0x10) = 0x726f74;
		*(int*) ((char*) auctioneer + 0x34) = 0x746b7541;
	}
	for (i = 0; i < n && i < 8; i++) {
		fcn_0064d41a(line, (char*) 0x68d428, i);
		npc = fcn_00445600(0, 0x100, 0, line);
		if (npc != 0)
			fcn_00455350((int) npc, (int) npc + 0x4c, &bid);
		if (bidders[i] == 0 || fcn_004fda30(ids[i]) == 0) {
			fcn_0064d41a(line, (char*) 0x679060,
			    (void*) 0x68bfe4);
			objs[i] = 0;
		} else {
			fcn_0064d41a(line, (char*) 0x679060, bidders[i] + 4);
			objs[i] = fcn_004e4a80(line, &bid);
			fcn_00402b00((int) objs[i], (int) npc);
		}
	}
	anim = (int) fcn_004e44b0("cutscenes\\auktion\\behavior_auktionator.esc", 0x6b5c60);
	cand = (int) fcn_004e44b0("cutscenes\\auktion\\Enterfly_auktion.esc",
	    0x6b5c60);
	fcn_0064d41a(line, (char*) 0x68d3b8, label);
	fcn_004e4b40(-7, bank_intro, line, -1, 0);
	fcn_0064d41a(line, (char*) 0x68d3a0, name);
	fcn_004e4b40(result, bank_intro, line, fcn_004e6cb0(3), 500);
	dlg = fcn_00470820(0, 0, "cutscenes\\pacht_main");
	if (g_772f3c != 0)
		fcn_00471af0((int) dlg, 0);
	fcn_00471d80((int) dlg, 3);
	d2_SetForm((int) dlg, 0);
	io_AppendText((void*) 0x1aa2, npc, (void*) arg[0x80 / 4]);
	fcn_004e44f0(cand);
	round = 0;
	while (start > 5) {
		if (round != 0)
			break;
		best = start;
		besti = -1;
		fcn_004e51d0((int) arg, states);
		if (start > 6 && fcn_004e6cb0(3) != 0)
			fcn_004e4b40(result, bank_comments,
			    "_VERSTEIGERUNG_KOMMENTARE", 0, 0);
		bid = 0;
		n = *(unsigned char*) (((char*) arg) + 0x30);
		for (i = 0; i < n && i < 8; i++) {
			if (bidders[i] == 0 || states[i] < 0) {
				bidders[i] = -1;
			} else {
				bid++;
				if (best < bidders[i]) {
					best = bidders[i];
					besti = i;
				}
			}
		}
		if (bid < 2) {
			round = 1;
		} else if (start > 6) {
			price = bid < (n >> 1) ? 2 : 0;
			fcn_004e4b40(result, bank_bids,
			    "_VERSTEIGERUNG_GEBOTE", price, 0);
			d2_SetForm((int) dlg, 0);
			io_AppendText((void*) 0x1aa3, npc, (void*) (bid + 2),
			    (void*) 5, (void*) (n - bid), (void*) best);
		}
		fcn_004e4c90(5);
		round++;
		start--;
	}
	if (besti < 0) {
		fcn_004e4b40(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 8, 500);
		d2_SetForm((int) dlg, 0);
		io_AppendText((void*) 0x1aa5, npc);
	} else {
		fcn_004e4b40(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 6, 200);
		d2_SetForm((int) dlg, 0);
		io_AppendText((void*) 0x1aa4, (void*) ids[besti],
		    (void*) best);
		if (arg[3] == *(int*) ((unsigned short) g_774970 * 0x21c
		    + 0x7f4ca4)) {
			fcn_004c4510((char*) npc, (int) npc, 0, 0);
			fcn_004c4570(4, 1, 0x69, &states[besti]);
			fcn_004c4570(4, 1, 0x6d, &round, &states[besti]);
			fcn_004c5360();
			fcn_004c5f60((int) npc, g_773da8, 0);
			cand = fcn_0050e4a0(1);
			other = (short*) fcn_00502cd0(cand, 2, 6, 0);
			if (other != 0 && bidders[besti] != 0) {
				anim = _ftol();
				fcn_004c51a0((int) other[1], bidders[besti], 0,
				    anim);
			}
		}
	}
	fcn_004e4b40(result, bank_bids, "_VERSTEIGERUNG_GEBOTE", 8, 500);
	cand = (int) fcn_004e44b0("cutscenes\\auktion\\Auktion_Outro.esc",
	    0x6b5c60);
	fcn_004e44f0(cand);
	fcn_00471e30((int) dlg);
	fcn_004e48b0();
	fcn_004e4610(anim);
	fcn_004e44f0(anim);
	for (i = 0; i < n && i < 8; i++) {
		if (objs[i] != 0)
			fcn_004e4aa0((int) objs[i]);
	}
	if (auctioneer != 0)
		fcn_004e4aa0((int) auctioneer);
	fcn_004e4910();
	fcn_004c09b0();
	fcn_004e4b00(bank_intro);
	fcn_004e4b00(bank_bids);
	fcn_004e4b00(bank_comments);
	if (g_772f3c == 0) {
		g_772d28 = 0;
		g_772d10 = g_772d14;
		if (g_774930 != 0 && g_772d1c != g_772d24)
			fcn_004c24c0();
	}
}
