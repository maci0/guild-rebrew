/*
 * Production start for one building: probes the two crafting slots, resolves
 * the production goods record, then walks the building table in a random
 * order looking for a producer that can start.
 */
#include <string.h>

typedef struct {
	char pad0[0x16c];
	int x16c;          /* +0x16c: shared building state */
	char pad170[0x1b4 - 0x170];
	int f1b4;          /* +0x1b4: selection flags */
	int pad1b8;
	unsigned short id; /* +0x1bc: current goods record id */
} Bld;

typedef struct {
	int id;            /* +0x00 */
	int cand[4];       /* +0x04 */
	char pad14[0x1c - 0x14];
	int x1c;           /* +0x1c */
	int x20;           /* +0x20 */
	char pad24[0x3c - 0x24];
	int f3c;           /* +0x3c */
	int f40;           /* +0x40 */
	char pad44[0x54 - 0x44];
	int f54;           /* +0x54: state flags */
} BldRec; /* 0x58 */

typedef struct {
	char pad0[0x1c];
	unsigned char x1c;
	unsigned char x1d;
} Craft;

extern char lpObjektePROT[];     /* +0x41 stride goods records: type byte, name */
extern char g_100d0c0[];    /* +0x58 stride building records */
extern int g_100b0ac;       /* building count */
extern int g_100dc20;
extern int g_100dc34;
extern int g_100dc38;
extern int g_100dc3c;
extern char g_100dc40[];
extern char g_100dc60[];
extern char g_100ddc0[];
extern char g_100df20[];
extern char g_100b0c0[];
extern unsigned short g_7f4c04;
extern char g_7f4ca0[];

int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004849b0(Bld*, int, int);
void __cdecl fcn_00487000(Bld*);
void __cdecl fcn_00487970(int, Bld*, int);
void __cdecl fcn_00487c00(int, Bld*, int);
void __cdecl fcn_00487470(Bld*);
int __cdecl fcn_00486640(Bld*, BldRec*, int);
void __cdecl fcn_004868d0(Bld*, BldRec*);
int __cdecl fcn_005b1e40(int);
int __cdecl fcn_00503d10(int);
int __cdecl gm_eval_SlotVoll(int, int, int);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0047e220(int);
void __cdecl fcn_0047e0e0(Bld*, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_00487e60(Bld*, int);
void __cdecl fcn_00487f90(int*);
void __cdecl ai_MeisterCollectTrans(Bld*);
void __cdecl ai_MeisterTrade(Bld*, int);


/* Starts the production of the current goods if any producer in the building
 * table can run it in the current town. */
/* ADDRESS: GOLDTL 0x0047e270 */
void __cdecl fcn_0047e270(Bld* bld)
{
	char name[0x100];
	int order[0x21];
	int craft;
	int prod;
	int hit;
	int i;
	int n;
	int r;
	int id;
	int val;
	int count;
	int slot;
	char* goods;
	BldRec* rec;
	Craft* cr;

	prod = fcn_00502cd0(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0xff);
	if (prod == 0)
		return;
	craft = fcn_00502cd0(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0x2a);
	if (craft == 0)
		return;
	fcn_004849b0(bld, prod, craft);
	fcn_00487000(bld);
	fcn_00487970(craft, bld, 0x4b);
	fcn_00487c00(craft, bld, 0x19);
	fcn_00487470(bld);
	cr = (Craft*) craft;
	hit = 0;
	if (g_7f4c04 != 8 && g_7f4c04 != 0xd) {
		for (i = 0; i < g_100b0ac; i++) {
			rec = (BldRec*) (g_100d0c0 + i * 0x58);
			if (rec->id != (int) bld->id)
				continue;
			goods = lpObjektePROT + rec->id * 0x41;
			if ((int) *(unsigned short*) (goods + 0x36) <= rec->f40 &&
			    fcn_00486640(bld, rec, 1)) {
				rec->f54 = rec->f54 | 8;
				fcn_004868d0(bld, rec);
				bld->id = (unsigned short) rec->id;
				hit = 1;
			}
			break;
		}
		bld->f1b4 = bld->f1b4 & 0xfffffeff;
		if (hit)
			goto done;
	}
	else if (bld->f1b4 & 0x100) {
		if (bld->id != 0) {
			for (i = 0; i < g_100b0ac; i++) {
				rec = (BldRec*) (g_100d0c0 + i * 0x58);
				if (rec->id != (int) bld->id)
					continue;
				goods = lpObjektePROT + rec->id * 0x41;
				if ((int) *(unsigned short*) (goods + 0x36) <= rec->f40 &&
				    fcn_00486640(bld, rec, 1)) {
					rec->f54 = rec->f54 | 8;
					fcn_004868d0(bld, rec);
					bld->id = (unsigned short) rec->id;
					goto done;
				}
				goto pick;
			}
		}
	}
	else {
		bld->id = 0;
		bld->f1b4 = bld->f1b4 | 0x100;
	}
pick:
	if (*(unsigned char*) (g_7f4ca0 + *(unsigned short*) (bld->x16c + 0x27) * 0x21c + 2) == 6) {
		n = fcn_005b1e40(bld->x16c);
		if (n != 0) {
			for (rec = (BldRec*) g_100d0c0; (char*) rec < g_100d0c0 + 0x5900; rec = (BldRec*) ((char*) rec + 0x58)) {
				if (rec->id != n)
					continue;
				goods = lpObjektePROT + rec->id * 0x41;
				if ((int) cr->x1c < rec->x1c)
					break;
				if ((int) cr->x1d < rec->x20)
					break;
				if (rec->f40 < (int) *(unsigned short*) (goods + 0x36))
					break;
				id = fcn_00503d10(rec->id);
				if (id == 0)
					break;
				if ((int) ((unsigned short) *(unsigned short*) (goods + 0x36) + rec->f3c) <= gm_eval_SlotVoll(id, rec->id, 1000000)) {
					if (fcn_00486640(bld, rec, 1)) {
						rec->f54 = rec->f54 | 8;
						fcn_004868d0(bld, rec);
						bld->id = (unsigned short) rec->id;
						fcn_0064d41a(name, "Produktion von %s starten, da Humanplayer es so will.", goods + 1);
						goto done;
					}
					if (fcn_00486640(bld, rec, 0)) {
						fcn_004868d0(bld, rec);
						bld->id = (unsigned short) rec->id;
						fcn_0064d41a(name, "Produktion von %s starten obwohl Rohstoffe fehlen, da der spieler es so will", goods + 1);
						goto done;
					}
				}
				break;
			}
		}
	}
	for (i = 0; i < 0x20; i++)
		order[i] = i;
	for (i = 0; i < 0x20; i++) {
		r = gm_RandomMod(0x20) & 0xffff;
		val = order[r];
		order[i] = order[r];
		order[r] = order[i + 1];
	}
	for (i = 0; i < g_100b0ac; i++) {
		rec = (BldRec*) (g_100d0c0 + order[i] * 0x58);
		id = rec->id;
		goods = lpObjektePROT + id * 0x41;
		if ((*(unsigned char*) goods == 0x17 || *(unsigned char*) goods == 0x25) && rec->f3c >= 5)
			continue;
		if ((int) cr->x1c < rec->x1c)
			continue;
		if ((int) cr->x1d < rec->x20)
			continue;
		if (rec->f40 < (int) *(unsigned short*) (goods + 0x36))
			continue;
		n = fcn_00503d10(rec->id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) *(unsigned short*) (goods + 0x36) + rec->f3c) > gm_eval_SlotVoll(n, rec->id, 1000000))
			continue;
		if (!fcn_00486640(bld, rec, 1))
			continue;
		rec->f54 = rec->f54 | 8;
		fcn_004868d0(bld, rec);
		bld->id = (unsigned short) rec->id;
		fcn_0064d41a(name, "Produktion von %s starten", goods + 1);
		goto done;
	}
	for (i = 0; i < g_100b0ac; i++) {
		rec = (BldRec*) (g_100d0c0 + order[i] * 0x58);
		id = rec->id;
		goods = lpObjektePROT + id * 0x41;
		if ((*(unsigned char*) goods == 0x17 || *(unsigned char*) goods == 0x25) && rec->f3c >= 5)
			continue;
		if ((int) cr->x1c < rec->x1c)
			continue;
		if ((int) cr->x1d < rec->x20)
			continue;
		if (rec->f40 < (int) *(unsigned short*) (goods + 0x36))
			continue;
		n = fcn_00503d10(rec->id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) *(unsigned short*) (goods + 0x36) + rec->f3c) > gm_eval_SlotVoll(n, rec->id, 1000000))
			continue;
		if (!fcn_00486640(bld, rec, 0))
			continue;
		fcn_004868d0(bld, rec);
		bld->id = (unsigned short) rec->id;
		fcn_0064d41a(name, "Produktion von %s starten obwohl Rohstoffe fehlen", goods + 1);
		goto done;
	}
	bld->id = 0;
done:
	fcn_0047e220(craft);
	fcn_0047e0e0(bld, craft);
	if (g_100dc20 == bld->x16c && g_100dc38 < 4) {
		slot = 0;
		while (slot < g_100b0ac && g_100dc38 < 4) {
			rec = (BldRec*) (g_100d0c0 + slot * 0x58);
			memcpy(g_100dc60 + g_100dc38 * 0x58, rec, 0x58);
			for (i = 0; i < 4; i++) {
				id = rec->cand[i];
				if (id >= 0) {
					memcpy(g_100df20 + (*(int*) (g_100dc40 + g_100dc38 * 4) + g_100dc38) * 0x40, g_100b0c0 + id * 0x40, 0x40);
					*(int*) (g_100dc40 + g_100dc38 * 4) = *(int*) (g_100dc40 + g_100dc38 * 4) + 1;
				}
			}
			g_100dc38 = g_100dc38 + 1;
			slot = slot + 1;
		}
	}
	fcn_00487e60(bld, 4);
	count = 0;
	for (n = 0x7f4ca2; n < 0x85a0a2; n += 0x21c) {
		if (*(unsigned char*) (n + 6) == 0)
			continue;
		if (*(short*) (n - 2) == -1)
			continue;
		if (*(unsigned char*) n == 0xa)
			continue;
		if (*(int*) (n + 0x16a) != bld->x16c)
			continue;
		if (*(unsigned char*) (n + 0x163) == 0)
			continue;
		if (*(int*) (n + 0x182) == 0)
			continue;
		if (*(int*) (*(int*) (n + 0x182) + 0x2c) != *(int*) (*(int*) (n + 0x16a) + 1))
			continue;
		fcn_00529160(bld->x16c, 0, (int) *(short*) (n - 2), 0);
		count = count + 1;
	}
	if (g_100dc20 == bld->x16c)
		g_100dc34 = count;
	n = 0;
	if (g_100b0ac > 0) {
		for (i = 0; i < g_100b0ac; i++) {
			rec = (BldRec*) (g_100d0c0 + i * 0x58);
			if (rec->f54 & 8)
				n = n + 1;
			if (rec->f54 & 0x10)
				n = n + 1;
		}
	}
	if (count >= n)
		count = n;
	if (n != 0 && count != 0) {
		for (i = 0; i < g_100b0ac; i++) {
			rec = (BldRec*) (g_100d0c0 + i * 0x58);
			if (rec->f54 & 8) {
				val = 4;
				fcn_00487f90(&val);
				if (g_100dc20 == bld->x16c && g_100dc3c < 4) {
					memcpy(g_100ddc0 + g_100dc3c * 0x58, rec, 0x58);
					g_100dc3c = g_100dc3c + 1;
				}
			}
		}
	}
	ai_MeisterCollectTrans(bld);
	ai_MeisterTrade(bld, craft);
}
unsigned char _dpad_100dc40[736];
